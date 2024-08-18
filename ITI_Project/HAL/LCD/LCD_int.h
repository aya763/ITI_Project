/*
 * LCD_int.h
 *
 *  Created on: Aug 8, 2023
 *      Author: aya
 */

#ifndef LCD_INT_H_
#define LCD_INT_H_

ES_t LCD_enuInit(void);

ES_t LCD_enuDisplayChar(u8 Copy_u8Data);

ES_t LCD_enuSendCommand(u8 Copy_u8Command);

ES_t LCD_enuDisplayString(u8 *Copy_pu8Data);

ES_t LCD_enuGoToPosition (u8 Copy_u8Row , u8 Copy_u8Col);

ES_t LCD_enuDisplayNum(u8 Copy_u8Num);


ES_t LCD_enuSendSpecialNumber(u32 Copy_u32Number);


ES_t LCD_enuClearLcd(void);


#define 	LCD_SHIFT_ENTRIE_DISPLAY_TO_LEFT	0x18
#define 	LCD_SHIFT_ENTRIE_DISPLAY_TO_RIGHT	0x1C

#define     LCD_GO_TO_CGRAM						0x40

#define 	LCD_FORCE_CURSOR_START_FIRST_LINE	0x80
#define 	LCD_FORCE_CURSOR_START_SECOND_LINE	0xC0

#define 	LCD_DECREMENT_CURSOR_TO_LEFT		0x04
#define 	LCD_INCREMENT_CURSOR_TO_RIGHT		0x06

#define 	LCD_SHIFT_DISPLAY_TO_RIGHT			0x05
#define 	LCD_SHIFT_DISPLAY_TO_LEFT			0x07

#endif /* LCD_INT_H_ */
