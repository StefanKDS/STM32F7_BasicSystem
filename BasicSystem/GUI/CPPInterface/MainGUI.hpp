/*
 * MainMenu.hpp
 *
 *  Created on: Aug 27, 2024
 *      Author: Stefan Seyer
 */

#ifndef CPPINTERFACE_MAINGUI_HPP_
#define CPPINTERFACE_MAINGUI_HPP_

#include "stdint.h"
#include "MainView.hpp"

class MainGUI{
public:
	MainGUI(uint8_t* headerString);
    virtual ~MainGUI();

public:
    MainView MainScreen;
    void DisplayTouched(uint16_t x, uint16_t y);
};


#endif /* CPPINTERFACE_MAINGUI_HPP_ */
