/*
 * MainView.cpp
 *
 *  Created on: Aug 27, 2024
 *      Author: Stefan Seyer
 */

#include "MainView.hpp"
#include <functional>
#include "ScreenManager.hpp"

// C++-Schnittstelle
MainView::MainView(uint8_t* headerString, ScreenManager& manager) : ScreenBase(headerString, manager)
{

	Button* button1 = new Button(60, 40, 100, 25, LCD_COLOR_ST_GREEN, LCD_COLOR_BLACK, std::bind(&MainView::ShowSDCardView, this), (uint8_t*)"SD Card");
	Button* button2 = new Button(60, 80, 100, 25, LCD_COLOR_ST_GREEN, LCD_COLOR_BLACK, nullptr, (uint8_t*)"text2");
	Label* label1 = new Label(60, 120, LCD_COLOR_ST_GREEN, nullptr, (uint8_t*)"Label 1");

	AddControlItem(button1);
	AddControlItem(button2);
	AddControlItem(label1);
}

MainView::~MainView()
{
}

void MainView::ShowSDCardView()
{
	// Verstecken der MainView, z.B. indem Sie das Display löschen oder die Steuerungselemente ausblenden
	    BSP_LCD_Clear(LCD_COLOR_BLACK);

	    screenManager.OpenView<SDCardView>((uint8_t*)"SD Karte");
	    delete this;
}
