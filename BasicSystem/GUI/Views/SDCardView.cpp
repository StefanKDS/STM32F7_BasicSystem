/*
 * SDCardView.cpp
 *
 *  Created on: Aug 29, 2024
 *      Author: Lenovo
 */

#include <SDCardView.hpp>

SDCardView::SDCardView(uint8_t* headerString, ScreenManager& manager)
    : ScreenBase(headerString, manager)
{
	Button* button1 = new Button(60, 40, 100, 25, LCD_COLOR_ST_GREEN, LCD_COLOR_BLACK, std::bind(&SDCardView::ReturnToPrevView, this), (uint8_t*)"SD Card");

	AddControlItem(button1);
}

SDCardView::~SDCardView()
{

}

void SDCardView::ReturnToPrevView()
{
    // Hier wird die View geschlossen, und die MainView wieder angezeigt
    delete this;  // Gibt den Speicher der SDCardView frei
}
