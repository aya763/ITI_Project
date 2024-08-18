

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
static volatile u8 Local_u8Address =0x16;



/************************************************
 *Function used to initialization
 ************************************************/
ES_t APP_ReceiveData(void){
	 u8 x=0xff;
	 u8 *choice=&x;
	ES_t Local_enuErrorState;
	IIC_enuReadData(choice);
	IIC_enuReadData(choice);

	LCD_enuGoToPosition(1,1);
	 //LCD_enuDisplayChar( *choice);
	// _delay_ms(1000);



	switch(*choice){
	case '1':
	case ('1'<<1):
		SERVO_enuSetAngle(90);
		/*Display Door Open On LCD*/
		LCD_enuGoToPosition(2,1);
		LCD_enuDisplayString("Door Open");
		DOOR_State=1;

		break;
	case '2':
	case ('2'<<1):
		SERVO_enuSetAngle(-90);
		/*Display Door Close On LCD*/
		LCD_enuGoToPosition(2,1);
		LCD_enuDisplayString("Door Closed");
		DOOR_State=0;
		break;
	case '3':
	case ('3'<<1):

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
	case ('4'<<1):

		  LED_enuTurnOFF(&LED_AstrLedConfig[1]);
		  Local_enuErrorState =LCD_enuGoToPosition(1,1);
		  REDLED_State=0;
		  if(GREENLED_State == 1){
			 LCD_enuDisplayString("LED1 ON,LED2 OFF");
		  }
		  else{
		 LCD_enuDisplayString("LED1 OFF,LED2 OFF");
		  }
		break;
	case '5':
	case ('5'<<1):
		  LED_enuTurnON(&LED_AstrLedConfig[0]);
		  Local_enuErrorState =LCD_enuGoToPosition(1,1);
		  GREENLED_State=1;
		  if(REDLED_State == 1){
			 LCD_enuDisplayString("LED1 ON,LED2 ON ");
		  }
		  else{
			  LCD_enuDisplayString("LED1 ON,LED2 OFF");
		  }
		break;
	case '6':
	case ('6'<<1):
		  LED_enuTurnOFF(&LED_AstrLedConfig[0]);
		  Local_enuErrorState =LCD_enuGoToPosition(1,1);
		  GREENLED_State=0;
		  if(REDLED_State == 1){
			  LCD_enuDisplayString("LED1 OFF,LED2 ON ");
		  }
		  else{
			  LCD_enuDisplayString("LED1 OFF,LED2 OFF");
		  }
		break;

	}
	return Local_enuErrorState;


}
ES_t APP_enuInit(void)
{
	ES_t Local_enuErrorState=ES_NOK;

	IIC_enuInit();
	Local_enuErrorState = SERVO_enudInit();
	Local_enuErrorState = LCD_enuInit();
	Local_enuErrorState = LED_enuInit(LED_AstrLedConfig);
	LCD_enuGoToPosition(1,1);
	LCD_enuDisplayString("Welcome Room");




	return Local_enuErrorState;

}








