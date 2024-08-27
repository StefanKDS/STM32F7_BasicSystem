/*
 * MainView.hpp
 *
 *  Created on: Aug 27, 2024
 *      Author: Stefan Seyer
 */

#ifndef VIEWS_MAINVIEW_HPP_
#define VIEWS_MAINVIEW_HPP_

#include "ScreenBase.h"
#include "stdint.h"

class MainView : public ScreenBase {
public:
	MainView(uint8_t* headerString);
    virtual ~MainView();
};

#endif /* VIEWS_MAINVIEW_HPP_ */
