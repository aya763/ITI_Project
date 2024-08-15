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




ES_t ret ,ret2 ;
volatile u8 check=0;


int main()
{

	APP_enuInit();

	ret = LCD_enuGoToPosition(1,1);
	ret = LCD_enuDisplayString("Door Closed");
	ret =LCD_enuGoToPosition(2,1);
	ret =LCD_enuDisplayString("LED1:OFF,LED2:OFF");




	while (1) {
        /*User Password Check*/
		if(check == 0){
			ret2=CheckUserPassword();
			if(ret2 == ES_OK){
				check=1;
			}
		}



	}








	return 0;
}



