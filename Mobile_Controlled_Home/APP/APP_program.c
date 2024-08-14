/*
 * APP_program.c
 *
 *  Created on: Aug 14, 2024
 *      Author: [Samar ibrahim]
 */
#include "../LIB/STD_Types.h"
#include "../LIB/errorState.h"

#include "APP_Config.h"
#include "APP_Interface.h"
#include "APP_Private.h"

#include "../MCAL/DIO/DIO_interface.h"

#include "../HAL/EEPROM/EEPROM_int.h"
#include <string.h>


/* Function to store user data in EEPROM*/
void storeUserInEEPROM(User_t *user, u8 userIndex)
{
    u16 address = EEPROM_START_ADDRESS + userIndex * (USERNAME_SIZE + PASSWORD_SIZE);//example:address=0x000+1*(5+4)=9

    for(u8 i = 0; i < USERNAME_SIZE; i++)
    {
        EEPROM_enuWriteData(address + i, user->username[i]);
    }
    address += USERNAME_SIZE; // after store username address is change

    // Store password in EEPROM
    for(u8 i = 0; i < PASSWORD_SIZE; i++)
    {
        EEPROM_enuWriteData(address + i, user->password[i]);
    }
}

// Function to read user data from EEPROM
void readUserFromEEPROM(User_t *user, u8 userIndex)
{
    u16 address = EEPROM_START_ADDRESS + userIndex * (USERNAME_SIZE + PASSWORD_SIZE);

    // Read username from EEPROM
    for(u8 i = 0; i < USERNAME_SIZE; i++)
    {
        EEPROM_enuReadData(address + i, &user->username[i]);
    }
    address += USERNAME_SIZE;

    // Read password from EEPROM
    for(u8 i = 0; i < PASSWORD_SIZE; i++)
    {
        EEPROM_enuReadData(address + i, &user->password[i]);
    }
}

/*Function to find user by username in EEPROM  this is use in main to find username*/
s8 findUser(User_t *inputUser)
{
    User_t storedUser;
    for(u8 i = 0; i < MAX_USERS; i++) //i is index of user
    {
        readUserFromEEPROM(&storedUser, i);
        if(strcmp(inputUser->username, storedUser.username) == 0)
        {
            if(strcmp(inputUser->password, storedUser.password) == 0)
            {
                return i;  // Authentication successful, return user index
            }
            else
            {
                return -2;  // User found, but password incorrect
            }
        }
    }
    return -1;  // User not found
}
