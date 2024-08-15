
#ifndef HAL_APP_APP_INTERFACE_H_
#define HAL_APP_APP_INTERFACE_H_

#include "APP_config.h"
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
LOG_t APP_FindUser(User_t *inputUser);



/*Function to update the password for a user*/
void updateUserPassword(u8 userIndex, u8 *newPassword);

ES_t application_intialize(void);

u8* CheckUserNumber(u8 *User_u8Num);

ES_t CheckUserPassword(void);

#endif
