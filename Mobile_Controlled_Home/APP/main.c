/*
 * main.c
 *
 *  Created on: Jul 25, 2024
 *      Author: aya
 */

#include <util/delay.h>
#include <string.h>

#include "../LIB/STD_Types.h"
#include "../LIB/errorState.h"

#include "APP_Types.h"

//#include "APP_config.h"
//#include "APP_private.h"
#include"APP_interface.h"

#include "../HAL/HC-05/HC-05_interface.h"


ES_t ret ,ret2 ;
volatile u8 check=0;


int main()
{
	HC_05_enuInit();
	LCD_enuInit();

/*	User_t users[MAX_USERS] = {
		     {"a123", "1234"},
		     {"b123", "189"},
		     {"c124", "298"}
		 };

		 for(u8 i = 0; i <3; i++) {
		        storeUserInEEPROM(&users[i], i);

	}*/
	/*application_intialize();

	ret = LCD_enuGoToPosition(1,1);
	ret = LCD_enuDisplayString("Door Closed");
	ret =LCD_enuGoToPosition(2,1);
	ret =LCD_enuDisplayString("LED1:OFF,LED2:OFF");




	while (1) {
        /*User Password Check*/
	/*	if(check == 0){
			ret2=CheckUserPassword();
			if(ret2 == ES_OK){
				check=1;
			}
		}*/
User_t inputUser = {0}; // Initialize inputUser structure with zeros
		        User_t *ps_inputuser = &inputUser;
		   	 for(u8 i = 0; i < MAX_USERS; i++) {
		    readUserFromEEPROM(ps_inputuser,i);
		    LCD_enuDisplayString(ps_inputuser->username);


HC_05_enuSendString(ps_inputuser->username);

		    LCD_enuDisplayString(ps_inputuser->password);
		    HC_05_enuSendString(ps_inputuser->password);


		    _delay_ms(1000);
		    }




	}











