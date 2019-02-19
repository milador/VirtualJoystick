/*-----------------------------------------------------------------------------------------*/
// __      __ _        _                  _        _                     _    _        _    
// \ \    / /(_)      | |                | |      | |                   | |  (_)      | |   
//  \ \  / /  _  _ __ | |_  _   _   __ _ | |      | |  ___   _   _  ___ | |_  _   ___ | | __
//   \ \/ /  | || '__|| __|| | | | / _` || |  _   | | / _ \ | | | |/ __|| __|| | / __|| |/ /
//    \  /   | || |   | |_ | |_| || (_| || | | |__| || (_) || |_| |\__ \| |_ | || (__ |   < 
//     \/    |_||_|    \__| \__,_| \__,_||_|  \____/  \___/  \__, ||___/ \__||_| \___||_|\_\
//                                                            __/ |                         
//                                                           |___/ 
/*-----------------------------------------------------------------------------------------*/

//VirtualJoystick Firmware
//VirtualJoystick_Firmware.ino
//Written by: Milad Hajihassan (Based on Adafruit_BluefruitLE examples)
//Version 1.0 (18/2/2019)
//Github Link: https://github.com/milador/VirtualJoystick


#include "Joystick.h"
#include <math.h>
#include <string.h>
#include <Arduino.h>
#include <SPI.h>
#include <EEPROM.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"
#include "BluefruitConfig.h"

#if SOFTWARE_Serial1_AVAILABLE
  #include <SoftwareSerial1.h>
#endif

/*-----------------------------------------------------------------------*/
#define FACTORYRESET_ENABLE         0
#define MINIMUM_FIRMWARE_VERSION    "0.6.6"
#define MODE_LED_BEHAVIOUR          "MODE"
/*-----------------------------------------------------------------------*/

//Hardware SPI Setup
Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

//Error helper
void error(const __FlashStringHelper*err) {
  Serial1.println(err);
  while (1);
}

//Functions from packetparser.cpp
uint8_t readPacket(Adafruit_BLE *ble, uint16_t timeout);
float parsefloat(uint8_t *buffer);
void printHex(const uint8_t * data, const uint32_t numBytes);

//Buffer of packets
extern uint8_t packetbuffer[];

//Defining the joystick REPORT_ID and profile type
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
  JOYSTICK_TYPE_JOYSTICK, 8, 0,
  true, true, false, 
  false, false, false,
  false, false, 
  false, false, false);     

//Declare variable for factory reset
int factoryResetDone = 1;             

//Setup function

void setup(void)
{
  while (!Serial1);
  
  delay(500);

  Serial1.begin(115200);
  Serial1.println(F("VirtualJoystick"));
  Serial1.println(F("---------------------------"));
  

  bluetoothSetup();

  //Setup joystick library 
  Joystick.begin(); 
  
  //Set joystick x,y range
  Joystick.setXAxisRange(-127, 127);
  Joystick.setYAxisRange(-127, 127);

  //Set joystick x,y default value 
  Joystick.setXAxis(0); 
  Joystick.setYAxis(0); 
  
}

/**************************************************************************/
/**    Loop function which polls to get response data
/**************************************************************************/
void loop(void)
{
  // Wait for new data to arrive
  uint8_t len = readPacket(&ble, BLE_READPACKET_TIMEOUT);
  if (len == 0) return;

  // Button actions 
  if (packetbuffer[1] == 'B') {
    uint8_t buttnum = packetbuffer[2] - '0';
    boolean pressed = packetbuffer[3] - '0';

    if (buttnum==0 && pressed) {
      Serial1.println("Pressed x1/View");
      Joystick.pressButton(0); 
    } else {
      Serial1.println("Released x1/View");
      Joystick.releaseButton(0);
    }    

    if (buttnum==1 && pressed) {
      Serial1.println("Pressed x2/Menu");
      Joystick.pressButton(1);
    } else {
      Serial1.println("Released x2/Menu");
      Joystick.releaseButton(1);
    }  


    if (buttnum==2 && pressed) {
      Serial1.println("Pressed ls/rs");
      Joystick.pressButton(2);
    } else {
      Serial1.println("Released ls/rs");
      Joystick.releaseButton(2);
    }

    if (buttnum==3 && pressed) {
      Serial1.println("Pressed lb/rb");
      Joystick.pressButton(3);
    } else {
      Serial1.println("Released lb/rb");
      Joystick.releaseButton(3);
    }    

    if (buttnum==4 && pressed) {
      Serial1.println("Pressed a/x");
      Joystick.pressButton(4);
    } else {
      Serial1.println("Released a/x");
      Joystick.releaseButton(4);
    }    

    if (buttnum==5 && pressed) {
      Serial1.println("Pressed b/y");
      Joystick.pressButton(5);
    } else {
      Serial1.println("Released b/y");
      Joystick.releaseButton(5);
    }
    
    if (buttnum==6 && pressed) {
      Serial1.println("Pressed Up");
      Joystick.setYAxis(-127); 
      delay(50);
    } else {
      Serial1.println("Released Up");
      Joystick.setYAxis(0); 
    }    

    if (buttnum==7 && pressed) {
      Serial1.println("Pressed Down");
      Joystick.setYAxis(127); 
      delay(50);
    } else {
      Serial1.println("Released Down");
      Joystick.setYAxis(0); 
    }  

    if (buttnum==8 && pressed) {
      Serial1.println("Pressed Left");
      Joystick.setXAxis(-127); 
      delay(50);
    } else {
      Serial1.println("Released Left");
      Joystick.setXAxis(0); 
    }  

    if (buttnum==9 && pressed) {
      Serial1.println("Pressed Right");
      Joystick.setXAxis(127); 
      delay(50);
    } else {
      Serial1.println("Released Right");
      Joystick.setXAxis(0); 
    }  
    
  }

}

/**************************************************************************/
/**    Setup Bluetooth function 
/**************************************************************************/

void bluetoothSetup() {

  //Initialize the module
  Serial1.print(F("Initializing the BLE module: "));

  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find BLE module, make sure it's in CMD mode."));
  }
  Serial1.println( F("OK!") );

  if ( FACTORYRESET_ENABLE )
  {
    //Perform a factory reset
    Serial1.println(F("Performing a factory reset: "));
    if ( ! ble.factoryReset() ){
      error(F("Couldn't factory reset"));
    }
  } else {
    int var;
    EEPROM.get(2, var);
    delay(5);
    if(var>0){
      factoryResetDone = var;
    } 
    else {
      //Perform a factory reset
      Serial1.println(F("Performing a factory reset: "));
      if ( ! ble.factoryReset() ){
        error(F("Couldn't factory reset"));
      }
      delay(5);
      EEPROM.put(2, factoryResetDone);
      delay(5);
    }
  }

  //Disable command echo
  ble.echo(false);

  Serial1.println("Requesting Ble module:");
  //Print Ble module information
  ble.info();

  //Turn off debug info mode
  ble.verbose(false);  

  // Wait for connection
  while (! ble.isConnected()) {
      delay(500);
  }

  Serial1.println(F("******************************"));

  // LED Activity command is only supported from 0.6.6
  if ( ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) )
  {
    // Change Mode LED Activity
    Serial1.println(F("Change LED activity to " MODE_LED_BEHAVIOUR));
    ble.sendCommandCheckOK("AT+HWModeLED=" MODE_LED_BEHAVIOUR);
    ble.sendCommandCheckOK(F( "AT+GAPDEVNAME=VirtualJoystick" ));
  }

  // Set Bluefruit to DATA mode
  Serial1.println( F("Switching to DATA mode!") );
  ble.setMode(BLUEFRUIT_MODE_DATA);

  Serial1.println(F("******************************"));
}
