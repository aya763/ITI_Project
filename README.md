# Mobile Controlled Home

![alt text](Smart_Home-1.png)
## Overview

The **Mobile Controlled Home** system allows users to control their home environment through a mobile phone application using Bluetooth communication. The system is designed to manage a safety door and light control with the following functionalities:

- **Safety Door**: Operate the door by entering a username and password through the mobile application.
- **Light Control**: Turn lights on and off via the mobile phone.

The system supports up to 10 users, each with a unique username and password. An alarm is triggered after three consecutive failed login attempts.

## Features

### MASTER Mode

- **ADD USER**: Add a new user to the system.
- **DELETE USER**: Remove an existing user.
- **CHANGE PASSWORD**: Update the master password.
- **SHOW USERS**: Display a list of all registered users.
- **SHOW HOME STATUS**: Display the current status of the home system.
- **CONTROL ROOM**: Access room control functionalities.
- **RETURN HOME PAGE**: Exit Master Mode and return to the home page.

### User Mode

- **OPEN DOOR**: Send an open command using the Bluetooth module.
- **CLOSE DOOR**: Send a close command using the Bluetooth module.
- **CHANGE PASSWORD**: Change the user password stored in EEPROM.
- **SHOW HOME STATUS**: Display system status (e.g., door status, alarm status) in the mobile interface.
- **RETURN HOME PAGE**: Exit User Mode and return to the home page of the system.

## Components

- **Microcontrollers**: Manage various tasks and interfaces.
- **HC-05 Bluetooth Module**: Facilitates Bluetooth communication with the system.
- **Servo Motor**: Controls the safety door.
- **LEDs**: Indicate different system statuses.
- **EEPROM**: Stores user data and configurations.
- **LCD Display**: Shows status information.
- **Buzzer**: Provides audible alerts.

## Functional Flow

1. **Initialization**: The system initializes, connects to the Bluetooth module, and checks the EEPROM for existing user data and configurations.
   ![Password Management GIF](EEPROM_Store.gif)  
      *Store Users in EEPROM* 


2. **Master Mode**:
   - **User Management**: The master can add or delete users and change the master password. User information is stored and managed in the EEPROM.
    
   ![User Management GIF](User_Mangment.gif)
   *Master Mode User Management*

   - **Home Status**: The master can view the status of the home system including door status, light status, and alarm status.
   
   ![Home Status GIF](<Home Status.gif>)  
   *Viewing Home Status*

   - **Room Control**: Provides functionalities to control the room.

   ![Room Control](<Control Room.gif>)
   *Control Room*

   3. **User Mode**:
      - **Door Control**: Users can open or close the door through Bluetooth commands.
      ![Door Control GIF](Door_Control.gif)
      *Controlling the Door*
   
      - **Password Management**: Users can change their passwords, which are updated in the EEPROM.
      
      ![Change_User_Password GIF](Change_User_Password.gif)
      *Changing User Password*
   
      - **Status Display**: Users can view the status of the home system including door and alarm status.
   
     
      ![Status Display GIF](Show_HomeStatus.gif)
      *Displaying System Status*
   
   4. **Alarm System**: An alarm is triggered after three consecutive failed login attempts to alert potential unauthorized access.
      ![alt text](Wrong_Password.gif)
      *Alarm Triggered*
      

## Security Measures

- **Password Protection**: Ensures only authorized users can control the home system.
- **Alarm Trigger**: Alerts when multiple failed login attempts occur.

## User Interface

- **Mobile Application**: Provides an intuitive interface for users to interact with the system, manage passwords, control the door, and check system status.

## Final Overview

You can see the video for the final output in this link [Video Project](https://drive.google.com/drive/folders/1ZNkKKI_RAHSwVl2SVzZfby3KmlPxgrgB)

## Team Members

- **[Nehal Nabil]**
- **[Aya Elsayed]**
- **[Samar Ibrahim]**

## Instructors

- **[Eng: Abdalla Ragab]**
- **[Eng: Mohamed Mansour]**
