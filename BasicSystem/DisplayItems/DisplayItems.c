/*
 * Menu.c
 *
 *  Created on: 07.01.2021
 *      Author: Stefan
 */

#include "DisplayItems.h"

#include "stm32746g_discovery_lcd.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

uint8_t m_nbrOfItems = 0;
uint8_t m_addedItems = 0;
uint8_t m_activeItem = -1;

void MarkItem(int itemNbr);
void UnMarkActualItem();
void AddLabel(uint16_t Xpos, uint16_t Ypos, uint8_t* text);
void AddTextInput(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height, uint8_t* text, uint16_t inputSize);
void DisplayItemTouchDetected(uint16_t x, uint16_t y);
void ViewKeyInput(uint8_t key);
void CloseView();
void InitDisplayItems(uint8_t nbrOfItems);



// Methods
void RegisterItem(Items* item)
{
	m_displayItems[m_addedItems] = *item;
	m_addedItems++;
}

void InitDisplayItems(uint8_t nbrOfItems)
{
	m_nbrOfItems = nbrOfItems;
	m_displayItems = malloc(nbrOfItems * sizeof(Items));
}

void CloseView()
{
	m_nbrOfItems = 0;
	m_addedItems = 0;

	for(int i=0; i < m_addedItems; i++)
	{
		if (m_displayItems[i].type == INPUTBOX)
		{
			free(m_displayItems[i].text);
		}
	}

	free(m_displayItems);

}

void AddLabel(uint16_t Xpos, uint16_t Ypos, uint8_t* text)
{
	if (m_nbrOfItems <= 0)
		return;

	if (m_addedItems >= m_nbrOfItems)
		return;

	Items item;

	item.type = LABEL;
	item.x = Xpos;
	item.y = Ypos;
	item.height = 0;
	item.width = 0;
	text = text;

	RegisterItem(&item);

	uint32_t oldColor = BSP_LCD_GetTextColor();
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);

	BSP_LCD_DisplayStringAt(Xpos, Ypos, text, LEFT_MODE );
	BSP_LCD_SetTextColor(oldColor);

}

void DisplayItemTouchDetected(uint16_t x, uint16_t y)
{
	UnMarkActualItem();

	for(int i=0; i < m_addedItems; i++)
	{
		if ( x > m_displayItems[i].x && x < ( m_displayItems[i].x + m_displayItems[i].width ))
		{
			if ( y > m_displayItems[i].y && y < ( m_displayItems[i].y + m_displayItems[i].height ))
			{
				// DisplayItemn found
				if(m_displayItems[i].type == INPUTBOX)
				{
					// Mark
					MarkItem(i);
					break;
				}

				if(m_displayItems[i].type == BUTTON)
				{
					m_displayItems[i].func();
					break;
				}

			}
		}
	}
}

void UnMarkActualItem()
{
	uint32_t oldColor = BSP_LCD_GetTextColor();
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DrawRect(m_displayItems[m_activeItem].x - 5, m_displayItems[m_activeItem].y-5, m_displayItems[m_activeItem].width + 10, m_displayItems[m_activeItem].height+10);
	BSP_LCD_SetTextColor(oldColor);

	m_activeItem = -1;
}

void MarkItem(int itemNbr)
{
	if(m_activeItem > -1)
	{
		UnMarkActualItem();
	}

	m_activeItem = itemNbr;

	uint32_t oldColor = BSP_LCD_GetTextColor();
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	BSP_LCD_SetTextColor(LCD_COLOR_ST_ORANGE);
	BSP_LCD_DrawRect(m_displayItems[m_activeItem].x - 5, m_displayItems[m_activeItem].y-5, m_displayItems[m_activeItem].width + 10, m_displayItems[m_activeItem].height+10);
	BSP_LCD_SetTextColor(oldColor);
}

void DrawText(uint8_t x, uint8_t y, uint8_t* text)
{
	// Block über alten string
	uint32_t oldColor = BSP_LCD_GetTextColor();
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_DisplayStringAt(x, y, text, LEFT_MODE );
	BSP_LCD_SetTextColor(oldColor);
}

void ViewKeyInput(uint8_t key)
{
	if(m_activeItem == -1)
		return;

	if(m_displayItems[m_activeItem].type == INPUTBOX)
	{
		if((isalpha(key) || isdigit(key)) &&
		   (strlen((char*)m_displayItems[m_activeItem].text) < m_displayItems[m_activeItem].maxTextLength))
		{
			strncat((char*)m_displayItems[m_activeItem].text,(char*)&key,1);
			strncat((char*)m_displayItems[m_activeItem].text,(char*)"\0",1);
			DrawText(m_displayItems[m_activeItem].x, m_displayItems[m_activeItem].y, m_displayItems[m_activeItem].text);
		}
		else if((key == '\r') && (strlen((char*)m_displayItems[m_activeItem].text) > 0))
		{
			uint32_t oldColor = BSP_LCD_GetTextColor();
			BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
			BSP_LCD_FillRect(m_displayItems[m_activeItem].x, m_displayItems[m_activeItem].y, m_displayItems[m_activeItem].width - 1, m_displayItems[m_activeItem].height-1);
			BSP_LCD_SetTextColor(oldColor);
			m_displayItems[m_activeItem].text[strlen((char*)m_displayItems[m_activeItem].text)-1] = '\0';
			DrawText(m_displayItems[m_activeItem].x, m_displayItems[m_activeItem].y, m_displayItems[m_activeItem].text);
		}

	}
}

void AddTextInput(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height, uint8_t* text, uint16_t maxTextLength)
{
	if (m_nbrOfItems <= 0)
		return;

	if (m_addedItems >= m_nbrOfItems)
		return;

	Items item;

	item.type = INPUTBOX;
	item.x = Xpos;
	item.y = Ypos;
	item.height = Height;
	item.width = Width;
	item.text = malloc(maxTextLength * sizeof(uint8_t));;
	sprintf((char*)item.text, "%s", text);
	item.maxTextLength = maxTextLength;

	RegisterItem(&item);

	BSP_LCD_DrawLine(Xpos,Ypos + Height,Xpos + Width,Ypos + Height);
}

void FuncDummy(void)
{
}

void AddButton(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height, uint32_t Color, void (*func)(), uint8_t* text)
{
	if (m_nbrOfItems <= 0)
		return;

	if (m_addedItems >= m_nbrOfItems)
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

	Items item;

	item.type = BUTTON;
	item.x = Xpos;
	item.y = Ypos;
	item.height = Height;
	item.width = Width;

	if(func == NULL)
		item.func = &FuncDummy;
	else
		item.func = func;

	RegisterItem(&item);
}


