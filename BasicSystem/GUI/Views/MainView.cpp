/*
 * MainView.cpp
 *
 *  Created on: Aug 27, 2024
 *      Author: Stefan Seyer
 */

#include "MainView.hpp"

// C++-Schnittstelle
MainView::MainView(uint8_t* headerString) : ScreenBase(headerString)
{
	Button* button1 = new Button(60, 40, 100, 25, LCD_COLOR_ST_GREEN, LCD_COLOR_WHITE, nullptr, (uint8_t*)"text1");
	Button* button2 = new Button(60, 80, 100, 25, LCD_COLOR_ST_GREEN, LCD_COLOR_WHITE, nullptr, (uint8_t*)"text2");

	AddControlItem(button1);
	AddControlItem(button2);
	RefreshScreen();
}

MainView::~MainView()
{
}

