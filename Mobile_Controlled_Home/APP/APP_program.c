

#include "../LIB/STD_Types.h"
#include "../LIB/errorState.h"

#include "../MCAL/DIO/DIO_interface.h"

#include "../HAL/LCD/LCD_int.h"

#include "../HAL/LED/LED_config.h"
#include "../HAL/LED/LED_interface.h"

#include "../HAL/HC-05/HC-05_interface.h"

#include "../HAL/Servo_Motor/Servo_int.h"

#include "../HAL/EEPROM/EEPROM_int.h"

//#include "APP_Types.h"

#include "APP_config.h"
//#include "APP_interface.h"
#include "APP_private.h"

#include <string.h>
#include <util/delay.h>

ES_t error ;
extern LED_t LED_AstrLedConfig[LED_NUM];

extern User_t APP_AstUsers[MAX_USERS];

static u16 APP_u16EEPROMAddress=EEPROM_START_ADDRESS;


static volatile u8 DOOR_State=0,GREENLED_State=0,REDLED_State=0,Current_Index=0;

User_t Current_User;


/******************************************************************
 * Function to check user password and make actions according to it
 ******************************************************************/
ES_t CheckUserPassword(void){
User_t InputUser;
	ES_t L_Error=ES_OK;
	s32 check1=90;

	LED_enuInit(LED_AstrLedConfig);
	L_Error =HC_05_enuSendString("User name: ");
	L_Error= HC_05_enuRecieveString(InputUser.username);

	L_Error =HC_05_enuSendString("Password : ");
	L_Error =HC_05_enuRecieveString(InputUser.password);


   check1=findUser(&InputUser);
   LCD_enuDisplayNum(check1);
   if(check1>=0){
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
	else{
		/*Turn On red Led */

   	    LED_enuTurnON(&LED_AstrLedConfig[0]);
   	    LED_enuTurnOFF(&LED_AstrLedConfig[1]);
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

/************************************************
 *Function used to initialization
 ************************************************/
ES_t application_intialize(void){
	ES_t error=ES_NOK;
	error=LCD_enuInit();
	error = LED_enuInit(LED_AstrLedConfig);
	error=EEPROM_enuInit();
	//error = LED_enuInit(&LED2_red);
	error = HC_05_enuInit();
	error = SERVO_enudInit();
	//LCD_enuDisplayString("WELCOME");

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
        _delay_ms(10);
    }
    address += USERNAME_SIZE; // after store username address is change

    // Store password in EEPROM
    for(u8 i = 0; i < PASSWORD_SIZE; i++)
    {
        EEPROM_enuWriteData(address + i, user->password[i]);
        _delay_ms(10);
    }
}

/****************************************
 *  Function to Add New user in EEPROM
 * ***************************************/
 ES_t AddUserInEEPRROM(void)
 {
	 ES_t Local_enuErrorState=ES_NOK;
	 u8 CheckValid=0;
	 u8 EmptyIndex=0xff;
	 User_t newUser;
	  for(u8 i = 0; i < MAX_USERS; i++)
	    {
	        if(APP_AstUsers[i].username[0] == 0) // Check if the username is empty
	        {
	            EmptyIndex = i;
	            CheckValid = 1;
	            break;
	        }
	    }
	  if(CheckValid!=1){
		  HC_05_enuSendString("\r\tNo available Place to add new user.\r\t");

	  }
	  else{


		     // Get username from the user
		     HC_05_enuSendString("\r\tEnter Username: ");
		     HC_05_enuRecieveString(newUser.username);
		     HC_05_enuSendString(newUser.username);
		     HC_05_enuSendString("\r\t");

		     // Get password from the user
		     HC_05_enuSendString("\r\tEnter Password: ");
		     HC_05_enuRecieveString(newUser.password);
		     HC_05_enuSendString(newUser.password);
		     HC_05_enuSendString("\r\t");

		     // Store the new user in EEPROM
		     storeUserInEEPROM(&newUser, EmptyIndex);

		     // Update the local array
		     APP_AstUsers[EmptyIndex] = newUser;

		     HC_05_enuSendString("\r\tUser added successfully!\r\t");
		     Local_enuErrorState=ES_OK;
	  }
	  return Local_enuErrorState;
 }

/****************************************
 *  Function to Delete user in EEPROM
 * ***************************************/


void DELETE_User(void)
{
	u8 Index=0;
	Show_Users();

	HC_05_enuSendString("\r\tEnter Number of user you want Delete:");
	HC_05_enuRecieveChar(&Index);
	HC_05_enuSendChar(Index);
	if(Index >=30 && Index<40)
	{
		HC_05_enuSendString("WRONG User Index\r\t");
		return;
	}
	HC_05_enuSendString("\r\t");

	User_t FREE={0};

	storeUserInEEPROM(&FREE,(Index-'0'));



}

/****************************************
 *  Function to Show user in EEPROM
 * ***************************************/
void Show_Users(void)
{
	User_t storedUser;
	HC_05_enuSendString("\r\t************************USERS****************************\r\t");
	for(u8 i = 1; i < MAX_USERS; i++) //i is index of user
	{
		readUserFromEEPROM(&storedUser, i);
		HC_05_enuSendChar(i+'0');
		HC_05_enuSendChar(')');
		HC_05_enuSendString(storedUser.username);
		HC_05_enuSendString("\r\t");

	}
	HC_05_enuSendString("*********************************************\r\t");
}

/****************************************
 *  Function to Change password in EEPROM
 * ***************************************/

void Change_Password()
{

	u8 InputPASS[PASSWORD_SIZE]={0};

	HC_05_enuSendString("\r\tEnter new Password:");
	HC_05_enuRecieveString(InputPASS);
	HC_05_enuSendString(InputPASS);
	HC_05_enuSendString("\r\t");


	u16 address = EEPROM_START_ADDRESS + Current_Index * (USERNAME_SIZE + PASSWORD_SIZE);

	address += USERNAME_SIZE; // after store username address is change

	// Store password in EEPROM
	for(u8 i = 0; i < PASSWORD_SIZE; i++)
	{
		EEPROM_enuWriteData(address + i,InputPASS[i]);
		_delay_ms(10);
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
        EEPROM_enuReadData(address + i, &(user->username[i]));
      //  HC_05_enuSendChar(user->username[i]);

    }
    address += USERNAME_SIZE;
   // HC_05_enuSendString("GG\r\t");

    // Read password from EEPROM
    for(u8 i = 0; i < PASSWORD_SIZE; i++)
    {
        EEPROM_enuReadData(address + i, &(user->password[i]));
       // HC_05_enuSendChar(user->password[i]);

    }
   // HC_05_enuSendString("GG\r\t");
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
        /*HC_05_enuSendString(storedUser.username);
        HC_05_enuSendString("\r\t");
        HC_05_enuSendString(storedUser.password);*/
        if(strcmp(inputUser->username, storedUser.username) == 0)
        {
            if(strcmp(inputUser->password, storedUser.password) == 0)
            {
            	Current_User=*inputUser;
            	Current_Index=i;
            	if(strcmp(inputUser->username, "MASTER") == 0)
            	{
            		return LOG_MASTER;
            	}
            	else
            	{
					return LOG_SUCCESS;  // Authentication successful, return user index
            	}
            }
            else
            {
                return LOG_PASS_INCORRECT;  // User found, but password incorrect
            }
        }
    }
    return LOG_USER_NOTFOUND;  // User not found
}






