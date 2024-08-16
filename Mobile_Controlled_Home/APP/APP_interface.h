
#ifndef HAL_APP_APP_INTERFACE_H_
#define HAL_APP_APP_INTERFACE_H_

/*#include "APP_config.h"
// Structure to store user data (username and password)
typedef struct {
    u8 username[USERNAME_SIZE];
    u8 password[PASSWORD_SIZE];
} User_t;*/


ES_t APP_enuInit(void);

ES_t APP_enuStart(void);

ES_t AddUserInEEPRROM(void);





/*Function to update the password for a user
void updateUserPassword(u8 userIndex, u8 *newPassword);

u8* CheckUserNumber(u8 *User_u8Num);*/




//void Change_Password();

//ES_t APP_enuCheckUserPassword(void);

#endif
