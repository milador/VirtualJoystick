# VirtualJoystick

VirtualJoystick turns your Andoid device into an accessible and user-friendly game controller for your game console or computer. The application uses an Adafruit Feather 32u4 Bluefruit LE board to simulate the functions of a USB HID Joystick. It offers four different controller pad options which gives the users multiple input options to select in order to interact with the host device.

VirtualJoystick supports following controller options:

* XAC Controller Left Pad
* XAC Controller Right Pad
* Controller Direction Pad
* Controller Button Pad

VirtualJoystick can be used to operate Xbox Adaptive Controller through the USB ports.

# Downloads 

These are all the files and documentation associated with the VirtualJoystick project.

 <table style="width:100%">
  <tr>
    <th>Resource</th>
    <th>Version</th>
    <th>Format</th>
    <th>Link</th>
  </tr>
    <tr>
    <td>VirtualJoystick All</td>
    <td>1.0</td>
    <td>ZIP</td>
    <td><a href="https://github.com/milador/VirtualJoystick/archive/master.zip">VirtualJoystick-master.zip</a></td>
  </tr>
  <tr>
    <td>VirtualJoystick Manual</td>
    <td></td>
    <td>PDF</td>
    <td><a href=""> </a></td>
  </tr>
  <tr>
    <td>VirtualJoystick BOM (csv)</td>
    <td>June 1, 2019</td>
    <td>CSV</td>
    <td><a href="https://github.com/milador/VirtualJoystick/blob/master/Components/VirtualJoystickr_BOM.csv">VirtualJoystickr_BOM.csv</a></td>
  </tr>
  <tr>
    <td>VirtualJoystick Firmware</td>
    <td>1.0</td>
    <td>Ino</td>
    <td><a href="https://github.com/milador/VirtualJoystick/raw/master/Software/VirtualJoystick_Firmware/VirtualJoystick_Firmware.ino">VirtualJoystick_Firmware.ino</a></td>
  </tr>
  <tr>
    <td>VirtualJoystick Application</td>
    <td>1.0</td>
    <td>APK</td>
    <td><a href="https://play.google.com/store/apps/details?id=com.milador.virtualjoystick">VirtualJoystick Application</a></td>
  </tr>
</table> 

# Usage

VirtualJoystick can turn your Android Smartphone or Tablet to a touch base game controller pad. You will need to connect your Adafruit Feather 32u4 Bluefruit LE board to your host device through a USB cable and send the joystick actions from your Android device to host device via bluetooth.


## Components List

  1. Adafruit Feather 32u4 Bluefruit LE X 1 : https://www.adafruit.com/product/2829
  
  2. USB cable - USB A to Micro-B X 1 : https://www.adafruit.com/product/592


## Software Setup Instructions

1. Install the required libraries 
  
1.1. Install Joystick library: https://github.com/MHeironimus/ArduinoJoystickLibrary
  
1.2. Install Adafruit_BluefruitLE_nRF51 library: https://github.com/adafruit/Adafruit_BluefruitLE_nRF51
  
2. Download the firmware 
  
  2.1. VirtualJoystick Firmware : https://github.com/milador/VirtualJoystick/raw/master/Software/VirtualJoystick_Firmware/VirtualJoystick_Firmware.ino
  
  2.2. Bluefruit Configuration : https://github.com/milador/VirtualJoystick/raw/master/Software/VirtualJoystick_Firmware/BluefruitConfig.h
  
  2.3. packetParser File: https://github.com/milador/VirtualJoystick/raw/master/Software/VirtualJoystick_Firmware/packetParser.cpp
  
3. Setup Arduino IDE for your feather board according to the instructions on Adafruit website
  
4. Verify and upload firmware code to your Feather Board

5. Install <a href="https://play.google.com/store/apps/details?id=com.milador.virtualjoysticko">VirtualJoystick Android Application</a> in your Android Smartphone or Tablet 

6. Enable Bluetooth in your Android Device

7. Enable Geo Location in your Android Device if you are using the application for the first time. Note: Android SDK 22 and above requires to enable Geolocation to use bluetooth features. You can disable Geolocation permission for the application after the first usage.



## Hardware Setup Instructions

1. Connect Adafruit Feather 32u4 Bluefruit LE to the Micro-B port of USB cable

2. Connect USB A port of USB cable to your host device ( XAC or Computer )
