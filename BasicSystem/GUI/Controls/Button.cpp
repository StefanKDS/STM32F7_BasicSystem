/*
 * Button.cpp
 *
 *  Created on: Aug 27, 2024
 *      Author: Stefan Seyer
 */

#include "Button.h"

Button::Button(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height, uint32_t Color, void (*OnClickFunc)(), uint8_t* Text)
{
	OnClick = NULL;
	x = Xpos;
	y = Ypos;
	height = Height;
	width = Width;
	color = Color;
	text = Text;

	if(OnClick == NULL)
		OnClick = NULL;
	else
		OnClick = OnClickFunc;
}

Button::~Button()
{
	// TODO Auto-generated destructor stub
}

void Button::Draw()
{
	uint32_t oldColor = BSP_LCD_GetTextColor();
	uint32_t oldBckColor = BSP_LCD_GetBackColor();

	BSP_LCD_SetTextColor(color);

	BSP_LCD_FillCircle(x + (height/2),y+(height/2),height/2);
	BSP_LCD_FillRect(x + (height/2), y, width, height+1);
	BSP_LCD_FillCircle(x + width + (height/2),y+(height/2),height/2);

	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_SetBackColor(color);
	BSP_LCD_SetFont(&Font16);
	BSP_LCD_DisplayStringAt(x + 25, y + height - 23 , text, LEFT_MODE );
	BSP_LCD_SetTextColor(oldColor);
	BSP_LCD_SetBackColor(oldBckColor);
}

