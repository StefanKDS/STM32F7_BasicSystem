/*
 * MainGUI.cpp
 *
 *  Created on: Aug 27, 2024
 *      Author: Stefan Seyer
 */

#include <MainGUI.hpp>
#include "Button.h"

MainGUI::MainGUI(uint8_t* headerString) : MainScreen(headerString)
{

}

MainGUI::~MainGUI() {
	// TODO Auto-generated destructor stub
}

void MainGUI::DisplayTouched(uint16_t x, uint16_t y)
{
	MainScreen.DisplayTouched(x, y);
}


// C-Schnittstelle
extern "C" {
MainGUI* create_MainGUI(uint8_t* headerString)
{
    return new MainGUI(headerString);
}

void destroy_MainGUI(MainGUI* obj)
{
    delete obj;
}

void displayTouched_MainGUI(MainGUI* obj, uint16_t x, uint16_t y)
{
    if (obj != nullptr) {
        obj->DisplayTouched(x, y);
    }
}


}
