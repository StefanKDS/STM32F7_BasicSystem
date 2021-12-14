/*
 * Menu.h
 *
 *  Created on: 29.09.2020
 *      Author: Stefan
 */

#ifndef MENU_H_
#define MENU_H_

#include "stdint.h"

typedef struct
{
	uint16_t x;
	uint16_t y;
	uint16_t width;
	uint16_t height;
	void (*ptr)();
}MenuPointLocation;

uint8_t m_nbrOfPoints;
uint8_t m_addedMenuPoints;
MenuPointLocation* m_menuPointLocations;

void     InitMenuScreen(uint8_t* headerString);
void 	 InitMenuPoints(uint8_t nbrOfPoints);
void     AddMenuPoint(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height, uint32_t Color, void (*ptr)(), uint8_t* text);
void     MenuTouchDetected(uint16_t x, uint16_t y);
void 	 RemoveAllMenuPoints();

#endif /* MENU_H_ */
