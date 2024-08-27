/*
 * Menu.h
 *
 *  Created on: 29.09.2020
 *      Author: Stefan
 */

#ifndef DISPLAYITEMS_H_
#define DISPLAYITEMS_H_

#include "stdint.h"

#define LABEL 1
#define INPUTBOX 2
#define BUTTON 3

typedef struct
{
	uint16_t x;
	uint16_t y;
	uint16_t width;
	uint16_t height;
	uint8_t* text;
	char type;
	uint16_t maxTextLength;
	void (*func)();
}Items;

void     AddLabel(uint16_t Xpos, uint16_t Ypos, uint8_t* text);
void     AddTextInput(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height, uint8_t* text, uint16_t inputSize);
void 	 DisplayItemTouchDetected(uint16_t x, uint16_t y);
void     ViewKeyInput(uint8_t key);
void     CloseView();
void     InitDisplayItems(uint8_t nbrOfItems);
void     AddButton(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height, uint32_t Color, void (*func)(), uint8_t* text);

#endif /* DISPLAYITEMS_H_ */
