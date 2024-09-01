/*
 * SDCardView.h
 *
 *  Created on: Aug 29, 2024
 *      Author: Lenovo
 */

#ifndef VIEWS_SDCARDVIEW_HPP_
#define VIEWS_SDCARDVIEW_HPP_

#include "ScreenBase.h"
#include "stdint.h"
#include "stm32746g_discovery_lcd.h"
#include "../FATFS/App/fatfs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

class SDCardView : public ScreenBase {
public:
    SDCardView(uint8_t* headerString, ScreenManager& manager);
    virtual ~SDCardView();

private:
    void ReturnToPrevView();
};

#endif /* VIEWS_SDCARDVIEW_HPP_ */
