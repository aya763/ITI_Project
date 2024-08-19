

#include "../LIB/STD_Types.h"
#include "../LIB/errorState.h"

#include "../MCAL/DIO/DIO_interface.h"

#include "../HAL/LCD/LCD_int.h"

#include "../HAL/LED/LED_config.h"
#include "../HAL/LED/LED_interface.h"

#include "../HAL/HC-05/HC-05_interface.h"

#include "../HAL/Servo_Motor/Servo_int.h"

#include "../HAL/EEPROM/EEPROM_int.h"
#include "../MCAL/I2C_TWI/TWI_int.h"

//#include "APP_Types.h"

#include "APP_config.h"
//#include "APP_interface.h"
#include "APP_private.h"

#include <string.h>
#include <util/delay.h>
#include "../HAL/BUZZER/BUZZER_config.h"
#include "../HAL/BUZZER/BUZZER_int.h"
ES_t error ;
extern LED_t LED_AstrLedConfig[LED_NUM];

extern User_t APP_AstUsers[MAX_USERS];

extern BUZZER_t BUZZER_AstrBuzzerConfig[BUZZER_NUM];

static u16 APP_u16EEPROMAddress=EEPROM_START_ADDRESS;

#define Room_Address 0x16
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

	Local_enuErrorState = LED_enuInit(LED_AstrLedConfig);
	Local_enuErrorState= IIC_enuInit();

	Local_enuErrorState= BUZZER_enuInit(BUZZER_AstrBuzzerConfig);
	Local_enuErrorState = LCD_enuInit();


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
	LCD_enuClearLcd();
	LCD_enuGoToPosition (1,1);
	LCD_enuDisplayString("Welcome Home");
	HC_05_enuSendString("\r\n****Welcome To Your Smart Home****\r\n");

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
	u8 check_find=0 , attempts=0;

	LED_enuTurnOFF(&LED_AstrLedConfig[0]);
    LED_enuTurnOFF(&LED_AstrLedConfig[1]);
    GREENLED_State=0;
    REDLED_State=0;


	Local_enuErrorState =HC_05_enuSendString("\r\nUser name: ");
	Local_enuErrorState= HC_05_enuRecieveString(InputUser.username);
	Local_enuErrorState =HC_05_enuSendString(InputUser.username);
	while(attempts != 3){
		Local_enuErrorState =HC_05_enuSendString("\r\nPassword : ");
		Local_enuErrorState =HC_05_enuRecieveString(InputUser.password);
		Local_enuErrorState =HC_05_enuSendString(InputUser.password);
		Local_enuErrorState =HC_05_enuSendString("\r\n");
		check_find=APP_FindUser(&InputUser);

		if(check_find==LOG_PASS_INCORRECT){
	   	    LED_enuTurnON(&LED_AstrLedConfig[1]);
	   	    LED_enuTurnOFF(&LED_AstrLedConfig[0]);
		    GREENLED_State=0;
		    REDLED_State=1;
	    	LCD_enuGoToPosition(1,1);
	    	/*Display LED red ON On LCD*/
	    	LCD_enuDisplayString("LED1:OFF,LED2:ON");
	    	Local_enuErrorState= SERVO_enuSetAngle(-90);
	    	Local_enuErrorState =LCD_enuGoToPosition(2,1);
	    	Local_enuErrorState =LCD_enuDisplayString("Door Closed");

			if(attempts != 2){
				Local_enuErrorState =HC_05_enuSendString("\r\nTry Again !");
			}
			attempts++;
		}
		else{
			break;
		}

	}
	if(attempts == 3){

BUZZER_enuTurnON(BUZZER_1);
		_delay_ms(2000);
BUZZER_enuTurnOFF(BUZZER_1);

	}



	//ReadUserFromEEPROM(&check,0);
	//Local_enuErrorState =HC_05_enuSendString(check.password);




	if(check_find==LOG_MASTER)
    {
		Local_enuErrorState =HC_05_enuSendString("\r\nCorrect\r\n");

		/*Turn On green Led */
	   LED_enuTurnON(&LED_AstrLedConfig[0]);
	   LED_enuTurnOFF(&LED_AstrLedConfig[1]);
	    GREENLED_State=1;
	    REDLED_State=0;
		LCD_enuGoToPosition(1,1);
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
	   Local_enuErrorState =HC_05_enuSendString("\r\nCorrect\r\n");
	    /*Turn On green Led */


  	   LED_enuTurnON(&LED_AstrLedConfig[0]);
  	   LED_enuTurnOFF(&LED_AstrLedConfig[1]);
 	   GREENLED_State=1;
 	   REDLED_State=0;
	   LCD_enuGoToPosition(1,1);
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

    	Local_enuErrorState =HC_05_enuSendString("\r\nWrong password\r\n");
   	    LED_enuTurnON(&LED_AstrLedConfig[1]);
   	    LED_enuTurnOFF(&LED_AstrLedConfig[0]);
	    GREENLED_State=0;
	    REDLED_State=1;
    	LCD_enuGoToPosition(1,1);
    	/*Display LED red ON On LCD*/
    	LCD_enuDisplayString("LED1:OFF,LED2:ON");
    	Local_enuErrorState= SERVO_enuSetAngle(-90);
    	Local_enuErrorState =LCD_enuGoToPosition(2,1);
    	Local_enuErrorState =LCD_enuDisplayString("Door Closed");

        Local_enuErrorState = ES_NOK;
	}
	else if(check_find==LOG_USER_NOTFOUND)
	{

	    	Local_enuErrorState =HC_05_enuSendString("\r\nWrong User\r\n");
			/*Turn On red Led */
	   	    LED_enuTurnON(&LED_AstrLedConfig[1]);
	   	    LED_enuTurnOFF(&LED_AstrLedConfig[0]);
	   	    GREENLED_State=0;
	   	 	REDLED_State=1;
	    	LCD_enuGoToPosition(1,1);
	    	/*Display LED red ON On LCD*/
	    	LCD_enuDisplayString("LED1:OFF,LED2:ON");
	    	Local_enuErrorState= SERVO_enuSetAngle(-90);
	    	Local_enuErrorState =LCD_enuGoToPosition(2,1);
	    	Local_enuErrorState =LCD_enuDisplayString("Door Closed");

	       Local_enuErrorState = ES_NOK;
		}

   return Local_enuErrorState;

}


void Master_Mode(void)
{
	u8 Option;
	HC_05_enuSendString("\r\n*******Welcome to MASTER MODE*******\r\n");

	while(1)
	{
		HC_05_enuSendString("1-ADD USER\r\n2-Delete USER\r\n3-CHANGE PASSWORD\r\n4-SHOW USERS\r\n5-SHOW HOME STATUES\r\n6-Control Room\r\n7-RETURN HOME PAGE\r\nYOUR OPTION NUMBER: ");
		HC_05_enuRecieveChar(&Option);
		HC_05_enuSendChar(Option);
		switch(Option)
		{
		case '1':
			Add_User();
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
			Control_Room();
			break;
		case '7':
			return;
			break;
		default:
			//HC_05_enuSendString("WRONG CHOICE OPTION\r\n\r\n");
			break;
		}
	}
}

/****************************************
 *  Function to Add New user in EEPROM
 * ***************************************/
void Add_User(void)
 {

	u8 Index=0;
	User_t InputUser;
	Show_Users();

	HC_05_enuSendString("\r\nEnter INDEX of FREE Space:");
	HC_05_enuRecieveChar(&Index);
	HC_05_enuSendChar(Index);
	readUserFromEEPROM(&InputUser,(Index-'0'));
	if(strcmp(InputUser.username, "FREE") != 0)
	{
		HC_05_enuSendString("\r\nWRONG User Index. Choose FREE Space");
		return;
	}
	HC_05_enuSendString("\r\n");



	// Get username from the user
	 HC_05_enuSendString("\r\nEnter Username: ");
	 HC_05_enuRecieveString(InputUser.username);
	 HC_05_enuSendString(InputUser.username);
	// HC_05_enuSendString("\r\t");


	 // Get password from the user
	 HC_05_enuSendString("\r\nEnter Password: ");
	 HC_05_enuRecieveString(InputUser.password);
	 HC_05_enuSendString(InputUser.password);
	// HC_05_enuSendString("\r\t");

	 // Store the new user in EEPROM
	 storeUserInEEPROM(&InputUser, (Index-'0'));

	 HC_05_enuSendString("User added successfully!");


}

void DELETE_User(void)
{
	u8 Index=0;
	Show_Users();

	HC_05_enuSendString("Enter Number of user you want Delete:");
	HC_05_enuRecieveChar(&Index);
	HC_05_enuSendChar(Index);
	if(Index >30 && Index<40)
	{
		HC_05_enuSendString("WRONG User Index");
		return;
	}
	HC_05_enuSendString("\r\n");

	User_t FREE[1]={{"FREE","FREE"}};

	storeUserInEEPROM(&FREE[0],(Index-'0'));

	HC_05_enuSendString("User Deleted successfully!");

}

void Show_Users(void)
{
	User_t storedUser;
	HC_05_enuSendString("\r\n***********USERS***********\r\n");
	for(u8 i = 1; i < MAX_USERS; i++) //i is index of user
	{
		readUserFromEEPROM(&storedUser, i);
		HC_05_enuSendChar(i+'0');
		HC_05_enuSendChar(')');
		HC_05_enuSendString(storedUser.username);
		HC_05_enuSendString("\r\n");

	}
	//HC_05_enuSendString("\r\n*********************************************\r\n");
}


void USER_Mode(void)
{
	u8 Option;
	HC_05_enuSendString("\r\n*******Welcome to USER MODE*******\r\n");

	while(1)
	{
		HC_05_enuSendString("1-OPEN DOOR\r\n2-CLOSE DOOR\r\n3-CHANGE LEDs STATUES\r\n4-CHANGE PASSWORD\r\n5-SHOW HOME STATUES\r\n6-RETURN HOME PAGE\r\n");
		HC_05_enuSendString("YOUR OPTION NUMBER:\r\n");
		HC_05_enuRecieveChar(&Option);
		HC_05_enuSendChar(Option);
		HC_05_enuSendString("\n");
		switch(Option)
		{
		case '1':
			SERVO_enuSetAngle(90);
			/*Display Door Open On LCD*/
			LCD_enuGoToPosition(2,1);
			LCD_enuDisplayString("Door Open ");
			DOOR_State=1;
			break;
		case '2':
			SERVO_enuSetAngle(-90);
			/*Display Door Close On LCD*/
			LCD_enuGoToPosition(2,1);
			LCD_enuDisplayString("Door Closed");
			DOOR_State=0;
			break;
		case '3':
			Change_LED_State();
			break;
		case '4':
			Change_Password();
			return;
			break;
		case '5':
			Show_Home_State();
			break;
		case '6':
			return;
			break;
		/*case '6':

			break;
		case '7':

			break;*/
		default:
			//HC_05_enuSendString("WRONG CHOICE OPTION");
			break;
		}
	}
}



void Change_Password(void)
{

	u8 InputPASS[PASSWORD_SIZE]={0};

	HC_05_enuSendString("\r\nEnter new Password:");
	HC_05_enuRecieveString(InputPASS);
	HC_05_enuSendString(InputPASS);
	//HC_05_enuSendString("\r\n");


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
	HC_05_enuSendString("\r\n*****STATEUS*****\r\n");
	if(DOOR_State)
	{
		HC_05_enuSendString("DOOR OPEN \r\n");
	}
	else
	{
		HC_05_enuSendString("DOOR Close\r\n");
	}
	if(GREENLED_State)
	{
		HC_05_enuSendString("GREEN LED ON\r\n");
	}
	else
	{
		HC_05_enuSendString("GREEN LED OFF\r\n");
	}
	if(REDLED_State)
	{
		HC_05_enuSendString("RED LED ON\r\n");
	}
	else
	{
		HC_05_enuSendString("RED LED OFF\r\n");
	}
	HC_05_enuSendString("\r\n*******************************\r\n");
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
/************************************
 * Function To change LED Status
 ***********************************/
void Change_LED_State(void){
	 u8 Option ;
	 ES_t Local_enuErrorState =ES_NOK;
	 HC_05_enuSendString("\r\n1-Turn ON Green LED\r\n2-Turn OFF Green LED\r\n3-Turn ON red LED\r\n4-Turn OFF red LED\r\n");
	 HC_05_enuRecieveChar(&Option);
	 HC_05_enuSendChar(Option);
	 HC_05_enuSendString("\r\n");
	 switch(Option)
	 {
	 case '1':
		  LED_enuTurnON(&LED_AstrLedConfig[0]);
		  Local_enuErrorState =LCD_enuGoToPosition(1,1);
		  GREENLED_State=1;
		  if(REDLED_State == 1){
			  LCD_enuDisplayString("LED1 ON,LED2 ON");
		  }
		  else{
			  LCD_enuDisplayString("LED1 ON,LED2 OFF");
		  }

	  break;
	 case '2':
		  LED_enuTurnOFF(&LED_AstrLedConfig[0]);
		  Local_enuErrorState =LCD_enuGoToPosition(1,1);
		  GREENLED_State=0;
		  if(REDLED_State == 1){
			  LCD_enuDisplayString("LED1 OFF,LED2 ON");
		  }
		  else{
			  LCD_enuDisplayString("LED1 OFF,LED2 OFF");
		  }

	  break;
	 case '3':
		  LED_enuTurnON(&LED_AstrLedConfig[1]);
		  Local_enuErrorState =LCD_enuGoToPosition(1,1);
		  REDLED_State=1;
		  if(GREENLED_State == 1){
			  LCD_enuDisplayString("LED1 ON,LED2 ON ");
		  }
		  else{
			  LCD_enuDisplayString("LED1 OFF,LED2 ON ");
		  }
	  break;
	 case '4':
		  LED_enuTurnOFF(&LED_AstrLedConfig[1]);
		  Local_enuErrorState =LCD_enuGoToPosition(1,1);
		  REDLED_State=0;
		  if(GREENLED_State == 1){
			  LCD_enuDisplayString("LED1 ON,LED2 OFF");
		  }
		  else{
			  LCD_enuDisplayString("LED1 OFF,LED2 OFF");
		  }


	 default:
	     // HC_05_enuSendString("WRONG CHOICE OPTION\r\n\r\n");
	  break;
	 }
}
/**************************************************
 * Function to control Room
 **************************************************/
void Control_Room(void){
	 u8 Option ,Copy_u8Data ;
	 ES_t Local_enuErrorState =ES_NOK;
	 HC_05_enuSendString("\r\n1-Open the Door\r\n2-Close The Door\r\n3-Turn ON red LED\r\n4-Turn OFF red LED\r\n5-Turn ON Green LED\r\n6-Turn OFF Green LED\r\n");
	 HC_05_enuRecieveChar(&Option);

	 HC_05_enuSendString("\r\n");


		if(ES_OK==IIC_enuStartCondition())
		{

			if(ES_OK==IIC_enuWriteSlaveAddress(0x16,0))
			{


					if(ES_OK==IIC_enuWriteData(Option))
					{

						Local_enuErrorState=IIC_enuStopCondition();


				}
			}
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






