

#include "../LIB/STD_Types.h"
#include "../LIB/errorState.h"
#include "../MCAL/DIO/DIO_interface.h"
#include "../HAL/LCD/LCD_int.h"
#include "../HAL/LED/LED_config.h"
#include "../HAL/LED/LED_interface.h"

#include "../HAL/HC-05/HC-05_interface.h"
#include "../HAL/Servo_Motor/Servo_int.h"
#include "../HAL/EEPROM/EEPROM_int.h"

#include "APP_Types.h"

#include "APP_config.h"
#include "APP_interface.h"
#include "APP_private.h"

#include <string.h>
#include <util/delay.h>

ES_t error ;
extern LED_t LED_AstrLedConfig[LED_NUM];




/******************************************************************
 * Function to check user password and make actions according to it
 ******************************************************************/
ES_t CheckUserPassword(void){

	ES_t L_Error=ES_OK;
	User_t InputUser;
	u8 check_find=0;

	LED_enuInit(LED_AstrLedConfig);
	L_Error =HC_05_enuSendString("User number: ");
	L_Error= HC_05_enuRecieveString(InputUser.username);

	L_Error =HC_05_enuSendString("Password : ");
	L_Error =HC_05_enuRecieveString(InputUser.password);


	check_find=APP_FindUser(&InputUser);

   if(check_find==LOG_SUCCESS){
		/*Turn On green Led */
	   LED_enuTurnON(&LED_AstrLedConfig[1]);
	   LED_enuTurnOFF(&LED_AstrLedConfig[0]);

    	/*Open the Door*/
    	L_Error =LCD_enuDisplayString("Correct");
    	L_Error= SERVO_enuSetAngle(90);
    	/*Display Door Open On LCD*/
    	L_Error =LCD_enuGoToPosition(1,1);
    	L_Error =LCD_enuDisplayString("Door Open");
    	LCD_enuGoToPosition(2,1);
    	/*Display LED Green ON On LCD*/
    	LCD_enuDisplayString("LED1:ON,LED2:OFF");
    	L_Error = ES_OK;
	}
	else if(check_find==LOG_PASS_INCORRECT){
		/*Turn On red Led */

   	    LED_enuTurnON(&LED_AstrLedConfig[0]);
   	    LED_enuTurnOFF(&LED_AstrLedConfig[1]);
    	L_Error =HC_05_enuSendString("Wrong password ");
    	L_Error =LCD_enuGoToPosition(1,1);
    	L_Error =LCD_enuDisplayString("Door Closed");
    	LCD_enuGoToPosition(2,1);
    	/*Display LED red ON On LCD*/
    	LCD_enuDisplayString("LED1:OFF,LED2:ON");
        L_Error = ES_NOK;
	}
	else if(check_find==LOG_USER_NOTFOUND){
			/*Turn On red Led */

	   	    LED_enuTurnON(&LED_AstrLedConfig[0]);
	   	    LED_enuTurnOFF(&LED_AstrLedConfig[1]);
	    	L_Error =HC_05_enuSendString("Wrong User ");
	    	L_Error =LCD_enuGoToPosition(1,1);
	    	L_Error =LCD_enuDisplayString("Door Closed");
	    	LCD_enuGoToPosition(2,1);
	    	/*Display LED red ON On LCD*/
	    	LCD_enuDisplayString("LED1:OFF,LED2:ON");

	        L_Error = ES_NOK;
		}

 return L_Error;

}



/****************************************
 *  Function to store user data in EEPROM
 * ***************************************/
void storeUserInEEPROM(User_t *user, u8 userIndex)
{
    u16 address = EEPROM_START_ADDRESS + userIndex * (USERNAME_SIZE + PASSWORD_SIZE);//example:address=0x000+1*(5+4)=9

    for(u8 i = 0; i < USERNAME_SIZE; i++)
    {
        EEPROM_enuWriteData(address + i, user->username[i]);
        _delay_ms(20);
    }
    address += USERNAME_SIZE; // after store username address is change

    // Store password in EEPROM
    for(u8 i = 0; i < PASSWORD_SIZE; i++)
    {
        EEPROM_enuWriteData(address + i, user->password[i]);
        _delay_ms(20);
    }
}

/******************************************
 * Function to read user data from EEPROM
 * *****************************************/
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


/*******************************************************************************
Function to find user by username in EEPROM  this is use in main to find username
**********************************************************************************/
LOG_t APP_FindUser(User_t *inputUser)
{
    User_t storedUser;
    for(u8 i = 0; i < MAX_USERS; i++) //i is index of user
    {
        readUserFromEEPROM(&storedUser, i);
        if(strcmp(inputUser->username, storedUser.username) == 0)
        {
            if(strcmp(inputUser->password, storedUser.password) == 0)
            {
                return LOG_SUCCESS;  // Authentication successful, return user index
            }
            else
            {
                return LOG_PASS_INCORRECT;  // User found, but password incorrect
            }
        }
    }
    return LOG_USER_NOTFOUND;  // User not found
}

/************************************************
 *Function used to initialization
 ************************************************/
ES_t application_intialize(void){
	error = LCD_enuInit();
	error = LED_enuInit(LED_AstrLedConfig);
	error = HC_05_enuInit();
	//error = SERVO_enudInit();
return error;

}
