/*
 * Menu.c
 *
 *  Created on: 29.09.2020
 *      Author: Stefan
 */

#include "Menu.h"
#include "stm32746g_discovery_lcd.h"
#include <stdlib.h>

uint8_t m_nbrOfPoints;
uint8_t m_addedMenuPoints;
MenuPointLocation* m_menuPointLocations;

// Methods

void DrawBottomMenu()
{
	uint32_t oldColor = BSP_LCD_GetTextColor();

	BSP_LCD_SetTextColor(LCD_COLOR_ST_LIGHTBLUE);
	BSP_LCD_FillCircle(BSP_LCD_GetXSize()-12,BSP_LCD_GetYSize()-6,5);
	BSP_LCD_FillRect(11, BSP_LCD_GetYSize()-11, BSP_LCD_GetXSize()-25, 11);
	BSP_LCD_FillCircle(12,BSP_LCD_GetYSize()-11, 10);
	BSP_LCD_FillRect(2, BSP_LCD_GetYSize()-24, 60, 14);

	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_FillCircle(61,BSP_LCD_GetYSize()-24,11);
	BSP_LCD_FillRect(BSP_LCD_GetXSize()-20, BSP_LCD_GetYSize()-11, 2, 11);
	BSP_LCD_FillRect(BSP_LCD_GetXSize()-30, BSP_LCD_GetYSize()-11, 6, 11);

	BSP_LCD_SetTextColor(oldColor);
}

void DrawHeader(uint8_t* headerString, uint32_t Color )
{
	uint32_t oldColor = BSP_LCD_GetTextColor();
	BSP_LCD_SetTextColor(Color);
	BSP_LCD_FillCircle(21,18,18);
	BSP_LCD_FillRect(20, 0, BSP_LCD_GetXSize()-31, 20);
	BSP_LCD_FillRect(2, 18, 60, 19);
	BSP_LCD_FillCircle(BSP_LCD_GetXSize()-12,9,9);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_FillCircle(62,33,12);


	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	BSP_LCD_SetTextColor(Color);
	BSP_LCD_SetFont(&Font20);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize()-180, 0 , headerString, LEFT_MODE );

	BSP_LCD_SetTextColor(oldColor);
}

void DrawLeftMenu()
{
	uint32_t oldColor = BSP_LCD_GetTextColor();
	BSP_LCD_SetTextColor(LCD_COLOR_ST_SKIN);
	BSP_LCD_FillRect(2, 39, 48, 80);

	BSP_LCD_SetTextColor(LCD_COLOR_ST_GREEN);
	BSP_LCD_FillRect(2, 121, 48, 30);
	BSP_LCD_FillRect(2, 153, 48, 30);

	BSP_LCD_SetTextColor(LCD_COLOR_ST_MAGENTA);
	BSP_LCD_FillRect(2, 186, 48, 30);

	BSP_LCD_SetTextColor(LCD_COLOR_ST_MAGENTA2);
	BSP_LCD_FillRect(2, 218, 48, 28);

	BSP_LCD_SetTextColor(oldColor);
}

void InitMenuScreen(uint8_t* headerString)
{
	BSP_LCD_Clear(LCD_COLOR_BLACK);

	DrawHeader(headerString, LCD_COLOR_ST_ORANGE);
	DrawLeftMenu();
	DrawBottomMenu();
}

void InitMenuPoints(uint8_t nbrOfPoints)
{
	m_nbrOfPoints = nbrOfPoints;
		m_menuPointLocations = malloc(nbrOfPoints * sizeof(MenuPointLocation));
}

void MenuTouchDetected(uint16_t x, uint16_t y)
{
	for(int i=0; i < m_addedMenuPoints; i++)
	{
		if ( x > m_menuPointLocations[i].x && x < ( m_menuPointLocations[i].x + m_menuPointLocations[i].width ))
		{
			if ( y > m_menuPointLocations[i].y && y < ( m_menuPointLocations[i].y + m_menuPointLocations[i].height ))
			{
				// MenuPoint found
					m_menuPointLocations[i].ptr();
			}
		}
	}
}

void Dummy()
{

}

void AddMenuPoint(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height, uint32_t Color, void (*ptr)(), uint8_t* text)
{
	if (m_nbrOfPoints <= 0)
		return;

	if (m_addedMenuPoints >= m_nbrOfPoints)
		return;

	uint32_t oldColor = BSP_LCD_GetTextColor();
	uint32_t oldBckColor = BSP_LCD_GetBackColor();

	BSP_LCD_SetTextColor(Color);

	BSP_LCD_FillCircle(Xpos + (Height/2),Ypos+(Height/2),Height/2);
	BSP_LCD_FillRect(Xpos + (Height/2), Ypos, Width, Height+1);
	BSP_LCD_FillCircle(Xpos + Width + (Height/2),Ypos+(Height/2),Height/2);

	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_SetBackColor(Color);
	BSP_LCD_SetFont(&Font16);
	BSP_LCD_DisplayStringAt(Xpos + 25, Ypos + Height - 23 , text, LEFT_MODE );
	BSP_LCD_SetTextColor(oldColor);
	BSP_LCD_SetBackColor(oldBckColor);

	m_menuPointLocations[m_addedMenuPoints].x = Xpos;
	m_menuPointLocations[m_addedMenuPoints].y = Ypos;
	m_menuPointLocations[m_addedMenuPoints].height = Height;
	m_menuPointLocations[m_addedMenuPoints].width = Width;

	if(ptr == NULL)
		m_menuPointLocations[m_addedMenuPoints].ptr = &Dummy;
	else
		m_menuPointLocations[m_addedMenuPoints].ptr = ptr;

	m_addedMenuPoints++;
}

void RemoveAllMenuPoints()
{
	uint32_t oldColor = BSP_LCD_GetTextColor();

	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);

	BSP_LCD_FillRect(55,50,BSP_LCD_GetXSize()-55, BSP_LCD_GetYSize()-80);

	m_nbrOfPoints = 0;
	m_addedMenuPoints = 0;
	free(m_menuPointLocations);

	BSP_LCD_SetTextColor(oldColor);
}


