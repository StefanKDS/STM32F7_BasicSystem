/*
 * SDView.c
 *
 *  Created on: 29.09.2020
 *      Author: Stefan
 */

#include "NetworkView.h"

#include "stm32746g_discovery_lcd.h"
#include "BaseView.h"
#include "lwip.h"
#include <stdlib.h>

void ClearViewArea();
void ShowNetViewMenuPoints();
void InitDisplayItems(uint8_t nbrOfItems);
void AddLabel(uint16_t Xpos, uint16_t Ypos, uint8_t* text);
void AddTextInput(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height, uint8_t* text, uint16_t maxTextLength);
void AddButton(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height, uint32_t Color, void (*func)(), uint8_t* text);
void CloseView();
void MainMenu();
void DisplayItemTouchDetected(uint16_t x, uint16_t y);
void InitMenuScreen(uint8_t* headerString);


// Methods

void ShowNetViewMenuPoints()
{
	uint32_t oldColor = BSP_LCD_GetTextColor();
	BSP_LCD_SetTextColor(LCD_COLOR_ST_GREEN);

	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_SetBackColor(LCD_COLOR_ST_GREEN);

	BSP_LCD_SetBackColor(LCD_COLOR_ST_SKIN);
	BSP_LCD_DisplayStringAt(18, 70, (uint8_t *)"H", LEFT_MODE);
	BSP_LCD_SetBackColor(LCD_COLOR_ST_GREEN);
	BSP_LCD_SetTextColor(oldColor);
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
}

void Func1()
{

}

void Func2()
{

}

void OpenFile()
{

}

void ShowNetView(uint8_t* headerString)
{
	DrawBaseScreen(headerString, LCD_COLOR_ST_ORANGE);
	ClearViewArea();
	ShowNetViewMenuPoints();

	extern struct netif gnetif;
	char buffer[19];

	// DisplayItems
    InitDisplayItems(3);
	int local_IP = gnetif.ip_addr.addr;

	sprintf(buffer,"IP: %d.%d.%d.%d",(local_IP & 0xff), ((local_IP >> 8) & 0xff), ((local_IP >> 16) & 0xff), (local_IP >> 24));
	AddLabel(65, 50, (uint8_t *)buffer);
}

void ClearViewArea()
{
	uint32_t oldColor = BSP_LCD_GetTextColor();
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_FillRect(59,39,BSP_LCD_GetXSize()-60,BSP_LCD_GetYSize()-60);
	BSP_LCD_SetTextColor(oldColor);
}

void NetViewTouchDetected(uint16_t x, uint16_t y)
{
	uint32_t oldColor = BSP_LCD_GetTextColor();
	BSP_LCD_SetTextColor(LCD_COLOR_ST_GREEN);

	// Menu click
	if(x < 60)
	{
		// Zurück
		if((y > 120) && (y < 152))
		{
			//ShowFileList(lastDir);
		}

		// Home
		if((y > 38) && (y < 119))
		{
			CloseView();
			InitMenuScreen((uint8_t *)"SEYERSOFT");
		//	MainMenu();
		}
	}
	else
	{
		// View click
		DisplayItemTouchDetected(x,y);
	}

	BSP_LCD_SetTextColor(oldColor);
}



