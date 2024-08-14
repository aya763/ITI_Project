/*
 * APP_interface.h
 *
 *  Created on: Aug 14, 2024
 *      Author: [Samar ibrahim]
 */

#ifndef APP_APP_INTERFACE_H_
#define APP_APP_INTERFACE_H_


#include "../LIB/STD_Types.h"

// Structure to store user data (username and password)
typedef struct {
    u8 username[USERNAME_SIZE];
    u8 password[PASSWORD_SIZE];
} User_t;

/*Function to store user data in EEPROM*/
void storeUserInEEPROM(User_t *user, u8 userIndex);

/* Function to read user data from EEPROM*/
void readUserFromEEPROM(User_t *user, u8 userIndex);

/* Function to find user by username in EEPROM*/
s8 findUser(User_t *inputUser);



/*Function to update the password for a user*/
void updateUserPassword(u8 userIndex, u8 *newPassword);


#endif /* APP_APP_INTERFACE_H_ */
