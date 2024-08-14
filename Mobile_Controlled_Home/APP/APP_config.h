
#ifndef HAL_APP_CONFIG_H_
#define HAL_APP_CONFIG_H_

#define USERNAME_SIZE 20              // Maximum username size
#define PASSWORD_SIZE 20              // Maximum password size
#define MAX_USERS 10                  // Maximum number of users
#define EEPROM_START_ADDRESS 0x0000   // Starting address in EEPROM for storing user data

LED_t LED1_green ={
		.LED_u8PinID= DIO_u8PIN2 ,
		.LED_u8PortID = DIO_u8PORTC,
		.LED_u8Connection = LED_SOURCE,
		.LED_u8InitState=LED_OFF

};

LED_t LED2_red ={
		.LED_u8PinID= DIO_u8PIN7 ,
		.LED_u8PortID = DIO_u8PORTC,
		.LED_u8Connection = LED_SOURCE,
		.LED_u8InitState=LED_OFF


};
#endif
