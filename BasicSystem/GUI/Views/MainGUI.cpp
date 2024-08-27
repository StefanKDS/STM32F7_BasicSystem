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


}
