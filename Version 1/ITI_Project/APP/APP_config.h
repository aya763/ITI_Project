
#ifndef HAL_APP_CONFIG_H_
#define HAL_APP_CONFIG_H_

#define USERNAME_SIZE 8              // Maximum username size
#define PASSWORD_SIZE 8              // Maximum password size
#define MAX_USERS 10                // Maximum number of users
#define EEPROM_START_ADDRESS 0x0000   // Starting address in EEPROM for storing user data



typedef struct {
    u8 username[USERNAME_SIZE];
    u8 password[PASSWORD_SIZE];
} User_t;


/*typedef enum
{
	LOG_MASTER,
	LOG_SUCCESS,
	LOG_PASS_INCORRECT,
	LOG_USER_NOTFOUND
}LOG_t;*/





#endif
