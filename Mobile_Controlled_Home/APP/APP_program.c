

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


/************************************************
 *Function used to initialization
 ************************************************/
ES_t APP_enuInit(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	Local_enuErrorState = EEPROM_enuInit();
	Local_enuErrorState = HC_05_enuInit();
	Local_enuErrorState = SERVO_enudInit();
	Local_enuErrorState = LCD_enuInit();
	Local_enuErrorState = LED_enuInit(LED_AstrLedConfig);


	// SAVE USERS IN EEPROM

	for(u8 i=0;i<MAX_USERS;i++)
	{

		storeUserInEEPROM(&APP_AstUsers[i],i);
	}

	return Local_enuErrorState;

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


ES_t APP_enuStart(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	HC_05_enuSendString("***********Welcome To Your Smart Home**********\r\t");

	APP_enuCheckUserPassword();



	return Local_enuErrorState;
}







/******************************************************************
 * Function to check user password and make actions according to it
 ******************************************************************/
ES_t APP_enuCheckUserPassword(void)
{

	ES_t Local_enuErrorState=ES_OK;
	User_t InputUser, check;
	u8 check_find=0;

	LED_enuTurnOFF(&LED_AstrLedConfig[0]);
    LED_enuTurnOFF(&LED_AstrLedConfig[1]);
    GREENLED_State=0;
    REDLED_State=0;


	Local_enuErrorState =HC_05_enuSendString("\r\tUser name: ");
	Local_enuErrorState= HC_05_enuRecieveString(InputUser.username);
	Local_enuErrorState =HC_05_enuSendString(InputUser.username);

	Local_enuErrorState =HC_05_enuSendString("\r\tPassword : ");
	Local_enuErrorState =HC_05_enuRecieveString(InputUser.password);
	Local_enuErrorState =HC_05_enuSendString(InputUser.password);
	Local_enuErrorState =HC_05_enuSendString("\r\t");

	//ReadUserFromEEPROM(&check,0);
	//Local_enuErrorState =HC_05_enuSendString(check.password);


	check_find=APP_FindUser(&InputUser);

	if(check_find==LOG_MASTER)
    {
		Local_enuErrorState =HC_05_enuSendString("\r\tCorrect\r\t");

		/*Turn On green Led */
	   LED_enuTurnON(&LED_AstrLedConfig[0]);
	   LED_enuTurnOFF(&LED_AstrLedConfig[1]);
	   GREENLED_State=1;
	   REDLED_State=0;
		LCD_enuGoToPosition(2,1);
		/*Display LED Green ON On LCD*/
		LCD_enuDisplayString("LED1:ON,LED2:OFF");

		Master_Mode();

		/*Open the Door
		Local_enuErrorState= SERVO_enuSetAngle(90);
		Display Door Open On LCD
		Local_enuErrorState =LCD_enuGoToPosition(1,1);
		Local_enuErrorState =LCD_enuDisplayString("Door Open");*/
		Local_enuErrorState = ES_OK;
	}

	else if(check_find==LOG_SUCCESS)
    {
	   Local_enuErrorState =HC_05_enuSendString("\r\tCorrect\r\t");
	    /*Turn On green Led */
	   LED_enuTurnON(&LED_AstrLedConfig[0]);
	   LED_enuTurnOFF(&LED_AstrLedConfig[1]);
	   GREENLED_State=1;
	   REDLED_State=0;

	   LCD_enuGoToPosition(2,1);
	   /*Display LED Green ON On LCD*/
	   LCD_enuDisplayString("LED1:ON,LED2:OFF");
	   USER_Mode();

    	/*Open the Door
    	Local_enuErrorState= SERVO_enuSetAngle(90);
    	Display Door Open On LCD
    	Local_enuErrorState =LCD_enuGoToPosition(1,1);
    	Local_enuErrorState =LCD_enuDisplayString("Door Open");
    	LCD_enuGoToPosition(2,1);
    	Display LED Green ON On LCD
    	LCD_enuDisplayString("LED1:ON,LED2:OFF");*/
    	Local_enuErrorState = ES_OK;
	}
	else if(check_find==LOG_PASS_INCORRECT)
	{
		/*Turn On red Led */

    	Local_enuErrorState =HC_05_enuSendString("\r\tWrong password\r\t");
   	    LED_enuTurnON(&LED_AstrLedConfig[1]);
   	    LED_enuTurnOFF(&LED_AstrLedConfig[0]);
	    GREENLED_State=0;
	    REDLED_State=1;
    	LCD_enuGoToPosition(2,1);
    	/*Display LED red ON On LCD*/
    	LCD_enuDisplayString("LED1:OFF,LED2:ON");
    	Local_enuErrorState= SERVO_enuSetAngle(-90);
    	Local_enuErrorState =LCD_enuGoToPosition(1,1);
    	Local_enuErrorState =LCD_enuDisplayString("Door Closed");

        Local_enuErrorState = ES_NOK;
	}
	else if(check_find==LOG_USER_NOTFOUND)
	{

	    	Local_enuErrorState =HC_05_enuSendString("\r\tWrong User\r\t");
			/*Turn On red Led */
	   	    LED_enuTurnON(&LED_AstrLedConfig[1]);
	   	    LED_enuTurnOFF(&LED_AstrLedConfig[0]);
	   	    GREENLED_State=0;
	   	 	REDLED_State=1;
	    	LCD_enuGoToPosition(2,1);
	    	/*Display LED red ON On LCD*/
	    	LCD_enuDisplayString("LED1:OFF,LED2:ON");
	    	Local_enuErrorState= SERVO_enuSetAngle(-90);
	    	Local_enuErrorState =LCD_enuGoToPosition(1,1);
	    	Local_enuErrorState =LCD_enuDisplayString("Door Closed");

	       Local_enuErrorState = ES_NOK;
		}

   return Local_enuErrorState;

}


void Master_Mode(void)
{
	u8 Option;
	HC_05_enuSendString("*******Welcome to MASTER MODE*******\r\t");

	while(1)
	{
		HC_05_enuSendString("\r\t1-ADD USER\r\t2-Delete USER\r\t3-CHANGE PASSWORD\r\t4-SHOW USERS\r\t5-SHOW HOME STATUES\r\t6-RETURN HOME PAGE\r\t");
		HC_05_enuSendString("YOUR OPTION NUMBER:");
		HC_05_enuRecieveChar(&Option);
		switch(Option)
		{
		case '1':

			break;
		case '2':
			DELETE_User();
			break;
		case '3':
			Change_Password();
			return;
			break;
		case '4':
			Show_Users();
			break;
		case '5':
			Show_Home_State();
			break;
		case '6':
			return;
			break;
		default:
			HC_05_enuSendString("WRONG CHOICE OPTION\r\t\r\t");
			break;
		}
	}
}

void DELETE_User(void)
{
	u8 Index=0;
	Show_Users();

	HC_05_enuSendString("\r\tEnter Number of user you want Delete:");
	HC_05_enuRecieveChar(&Index);
	HC_05_enuSendChar(Index);
	if(Index<10)
	{
		HC_05_enuSendString("WRONG User Index\r\t");
		return;
	}
	HC_05_enuSendString("\r\t");

	User_t FREE[1]={{"FREE","FREE"}};
	//strcpy(FREE.username,"FREE");
	//strcpy(FREE.password,"FREE");
	/*FREE.username="FREE";
	FREE.password="FREE";*/

	//storeUserInEEPROM(&FREE[0],Index);
	u8 DELETE[USERNAME_SIZE]={0};

	u16 address = EEPROM_START_ADDRESS + Index * (USERNAME_SIZE + PASSWORD_SIZE);//example:address=0x000+1*(5+4)=9

	for(u8 i = 0; i < USERNAME_SIZE; i++)
	{
		EEPROM_enuWriteData(address + i, DELETE[i]);
		_delay_ms(10);
	}
	address += USERNAME_SIZE; // after store username address is change

	// Store password in EEPROM
	for(u8 i = 0; i < PASSWORD_SIZE; i++)
	{
		EEPROM_enuWriteData(address + i, DELETE[i]);
		_delay_ms(10);
	}


}

void Show_Users(void)
{
	User_t storedUser;
	HC_05_enuSendString("\r\t************************USERS****************************");
	for(u8 i = 0; i < MAX_USERS; i++) //i is index of user
	{
		readUserFromEEPROM(&storedUser, i);
		HC_05_enuSendChar(i+'0');
		HC_05_enuSendChar(')');
		HC_05_enuSendString(storedUser.username);
		HC_05_enuSendString("\r\t");

	}
	HC_05_enuSendString("*********************************************\r\t");
}


void USER_Mode(void)
{
	u8 Option;
	HC_05_enuSendString("*******Welcome to USER MODE*******\r\t");

	while(1)
	{
		HC_05_enuSendString("\r\t1-OPEN DOOR\r\t2-CLOSE DOOR\r\t3-CHANGE PASSWORD\r\t4-SHOW HOME STATUES\r\t5-RETURN HOME PAGE\r\t");
		HC_05_enuSendString("YOUR OPTION NUMBER:");
		HC_05_enuRecieveChar(&Option);
		HC_05_enuSendChar(Option);
		HC_05_enuSendString("\r\t");
		switch(Option)
		{
		case '1':
			SERVO_enuSetAngle(90);
			/*Display Door Open On LCD*/
			LCD_enuGoToPosition(1,1);
			LCD_enuDisplayString("Door Open");
			DOOR_State=1;
			break;
		case '2':
			SERVO_enuSetAngle(-90);
			/*Display Door Open On LCD*/
			LCD_enuGoToPosition(1,1);
			LCD_enuDisplayString("Door Closed");
			DOOR_State=0;
			break;
		case '3':
			Change_Password();
			return;
			break;
		case '4':
			Show_Home_State();
			break;
		case '5':
			return;
			break;
		/*case '6':

			break;
		case '7':

			break;*/
		default:
			HC_05_enuSendString("WRONG CHOICE OPTION\r\t\r\t");
			break;
		}
	}
}



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


void Show_Home_State(void)
{
	HC_05_enuSendString("\r\t**************STATEUS*****************\r\t");
	if(DOOR_State)
	{
		HC_05_enuSendString("DOOR OPEN\r\t");
	}
	else
	{
		HC_05_enuSendString("DOOR Close\r\t");
	}
	if(GREENLED_State)
	{
		HC_05_enuSendString("GREEN LED ON\r\t");
	}
	else
	{
		HC_05_enuSendString("GREEN LED OFF\r\t");
	}
	if(REDLED_State)
	{
		HC_05_enuSendString("RED LED ON\r\t");
	}
	else
	{
		HC_05_enuSendString("RED LED OFF\r\t");
	}
	HC_05_enuSendString("\r\t*******************************\r\t");
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






