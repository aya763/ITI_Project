

#include "../LIB/STD_Types.h"
#include "../LIB/errorState.h"
#include "../MCAL/DIO/DIO_interface.h"
#include "../HAL/LCD/LCD_int.h"
#include "../HAL/LED/LED_interface.h"
#include "../MCAL/USART/USART_int.h"
#include "../HAL/HC-05/HC-05_interface.h"
#include "../HAL/Servo_Motor/Servo_int.h"
#include "../HAL/EEPROM/EEPROM_int.h"
#include "APP_config.h"
#include "APP_interface.h"
#include "APP_private.h"



ES_t error ;
extern LED_t LED1_green;
extern LED_t LED2_red;
/*************************************************************
 * Function to check user number and get password from EEBROM
 ************************************************************/
u8* CheckUserNumber(u8 *User_u8Num){
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
	    	L_Error =HC_05_enuSendString("User not found");

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
    	LED_enuTurnON(&LED1_green);
    	LED_enuTurnOFF(&LED2_red);
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

   	    LED_enuTurnON(&LED2_red);
   	    LED_enuTurnOFF(&LED1_green);
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

#include "../HAL/EEPROM/EEPROM_int.h"
#include <string.h>


/****************************************
 *  Function to store user data in EEPROM
 * ***************************************/
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

/************************************************
 *Function used to initialization
 ************************************************/
void application_intialize(void){

	error = LED_enuInit(&LED1_green);
	error = LED_enuInit(&LED2_red);
	error = HC_05_enuInit();
	error = SERVO_enudInit();
	LCD_enuInit();


}
