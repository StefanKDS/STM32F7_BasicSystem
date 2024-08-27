/*
 * MainMenu.hpp
 *
 *  Created on: Aug 27, 2024
 *      Author: Stefan Seyer
 */

#ifndef VIEWS_MAINMENUVIEW_HPP_
#define VIEWS_MAINMENUVIEW_HPP_

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


#endif /* VIEWS_MAINMENUVIEW_HPP_ */
