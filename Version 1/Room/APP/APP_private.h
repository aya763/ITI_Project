

#ifndef HAL_APP_PRIVATE_H_
#define HAL_APP_PRIVATE_H_

typedef enum
{
	LOG_MASTER,
	LOG_SUCCESS,
	LOG_PASS_INCORRECT,
	LOG_USER_NOTFOUND
}LOG_t;



/*Function to store user data in EEPROM*/
void storeUserInEEPROM(User_t *user, u8 userIndex);


/* Function to read user data from EEPROM*/
void readUserFromEEPROM(User_t *user, u8 userIndex);


/* Function to find user by username in EEPROM*/
LOG_t APP_FindUser(User_t *inputUser);

ES_t APP_enuCheckUserPassword(void);

void Master_Mode(void);

void DELETE_User(void);

void Show_Users(void);

void USER_Mode(void);

void Change_Password();

void Show_Home_State(void);








#endif