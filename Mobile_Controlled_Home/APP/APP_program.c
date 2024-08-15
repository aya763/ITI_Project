

#include "../LIB/STD_Types.h"
#include "../LIB/errorState.h"

#include "../MCAL/DIO/DIO_interface.h"

#include "../HAL/LCD/LCD_int.h"

#include "../HAL/LED/LED_config.h"
#include "../HAL/LED/LED_interface.h"

#include "../MCAL/USART/USART_int.h"

#include "../HAL/HC-05/HC-05_interface.h"

#include "../HAL/Servo_Motor/Servo_int.h"

#include "../HAL/EEPROM/EEPROM_int.h"

#include <string.h>

#include "APP_config.h"
#include "APP_Types.h"
#include "APP_private.h"
#include "APP_interface.h"



ES_t error ;
extern LED_t LED_AstrLedConfig[LED_NUM];


/*************************************************************
 * Function to check user number and get password from EEBROM
 ************************************************************/
u8* CheckUserNumber(u8 *User_u8Num)
{
	ES_t L_Error=ES_OK;
	u8 User1_Password[6] ="00000";

	switch(*User_u8Num){
	    case '1':
	    	strcpy(User1_Password, "12345");

	    	break;
	    case '2':
	    	break;
	    case '3':
	    	break;
	    case '4':
	    	break;
	    case '5':
	    	break;
	    case '6':
	    	break;
	    case '7':
	    	break;
	    case '8':
	    	break;
	    case '9':
	    	break;
	    case '10':
	    	break;
	    default:
	    	L_Error =HC_05_enuSendString("User not found\r\t");

	}
	return User1_Password;
}

/******************************************************************
 * Function to check user password and make actions according to it
 ******************************************************************/
ES_t CheckUserPassword(void){

	ES_t L_Error=ES_OK;
	u8 check1=0;
	u8  Password_check[6] ;
	u8 User_Password[6] ;
	u8 User_u8Num[1];

	L_Error =HC_05_enuSendString("User number: ");
	L_Error= HC_05_enuRecieveChar(User_u8Num);


	strcpy(User_Password , CheckUserNumber(User_u8Num));
	L_Error =HC_05_enuSendString("Password : ");
	L_Error =HC_05_enuRecieveString(Password_check);


	if(strcmp( Password_check, User_Password) == 0  ){
		/*Turn On green Led */
    	LED_enuTurnON(&LED_AstrLedConfig[0]);
    	LED_enuTurnOFF(&LED_AstrLedConfig[1]);
    	L_Error =HC_05_enuSendString(" Correct password ");
    	/*Open the Door*/

    	L_Error= SERVO_enuSetAngle(90);
    	/*Display Door Open On LCD*/
    	L_Error =LCD_enuGoToPosition(1,1);
    	L_Error =LCD_enuDisplayString("Door Open");
    	LCD_enuGoToPosition(2,1);
    	/*Display LED Green ON On LCD*/
    	LCD_enuDisplayString("LED1:ON,LED2:OFF");
    	L_Error = ES_OK;
	}
	else{
		/*Turn On red Led */

   	    LED_enuTurnON(&LED_AstrLedConfig[1]);
   	    LED_enuTurnOFF(&LED_AstrLedConfig[0]);
    	L_Error =HC_05_enuSendString("Wrong password ");
    	L_Error =LCD_enuGoToPosition(1,1);
    	L_Error =LCD_enuDisplayString("Door Closed");
    	LCD_enuGoToPosition(2,1);
    	/*Display LED red ON On LCD*/
    	LCD_enuDisplayString("LED1:OFF,LED2:ON");
        check1=0;
        L_Error = ES_NOK;
	}

 return L_Error;

}




/****************************************
 *  Function to store user data in EEPROM
 * ***************************************/
void APP_StoreUserInEEPROM(User_t *user, u8 userIndex)
{
    u16 Local_u8Address = EEPROM_START_ADDRESS + userIndex * (USERNAME_SIZE + PASSWORD_SIZE);//example:address=0x000+1*(5+4)=9

    for(u8 i = 0; i < USERNAME_SIZE; i++)
    {
        EEPROM_enuWriteData(Local_u8Address + i, user->username[i]);
    }
    Local_u8Address += USERNAME_SIZE; // after store username address is change

    // Store password in EEPROM
    for(u8 i = 0; i < PASSWORD_SIZE; i++)
    {
        EEPROM_enuWriteData(Local_u8Address + i, user->password[i]);
    }
}

/******************************************
 * Function to read user data from EEPROM
 * *****************************************/
void APP_ReadUserFromEEPROM(User_t *user, u8 userIndex)
{
    u16 Local_u8Address = EEPROM_START_ADDRESS + userIndex * (USERNAME_SIZE + PASSWORD_SIZE);

    // Read username from EEPROM
    for(u8 i = 0; i < USERNAME_SIZE; i++)
    {
        EEPROM_enuReadData(Local_u8Address + i, &user->username[i]);
    }
    Local_u8Address += USERNAME_SIZE;

    // Read password from EEPROM
    for(u8 i = 0; i < PASSWORD_SIZE; i++)
    {
        EEPROM_enuReadData(Local_u8Address + i, &user->password[i]);
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
        APP_ReadUserFromEEPROM(&storedUser, i);
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
ES_t APP_enuInit(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	Local_enuErrorState= LED_enuInit(LED_AstrLedConfig);
	Local_enuErrorState= HC_05_enuInit();
	Local_enuErrorState= SERVO_enudInit();
	Local_enuErrorState= LCD_enuInit();

	return Local_enuErrorState;
}
