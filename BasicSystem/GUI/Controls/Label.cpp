/*
 * Label.cpp
 *
 *  Created on: Aug 27, 2024
 *      Author: Lenovo
 */

#include <Label.h>

Label::Label(uint16_t Xpos, uint16_t Ypos, uint32_t TextColor, std::function<void()> OnClickFunc, uint8_t* Text)
{
		x = Xpos;
		y = Ypos;
		height = 0;
		width = 0;
		text = Text;
		textcolor = TextColor;
}

Label::~Label()
{
}

void Label::Draw()
{
	uint32_t oldColor = BSP_LCD_GetTextColor();
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	BSP_LCD_SetTextColor(textcolor);

	BSP_LCD_DisplayStringAt(x, y, text, LEFT_MODE );
	BSP_LCD_SetTextColor(oldColor);
}
