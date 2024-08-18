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



//#include "APP_config.h"
#include"APP_interface.h"








int main()
{


	APP_enuInit();



	while(1)
	{
		APP_ReceiveData();
	}



}











