/*
 * ScreenBase.h
 *
 *  Created on: Aug 27, 2024
 *      Author: Stefan Seyer
 */

#ifndef SCREENS_SCREENBASE_H_
#define SCREENS_SCREENBASE_H_

#include "stdint.h"
#include "ControlBase.h"
#include <vector>
#include "Button.h"

class ScreenBase {
public:
    ScreenBase(uint8_t* headerString);
    virtual ~ScreenBase();

public:
    void AddControlItem(ControlBase* control);
    void RefreshScreen();

private:
    void DrawHeader(uint8_t* headerString, uint32_t Color);
    void DrawLeftMenu();
    void DrawBottomMenu();

private:
    std::vector<ControlBase*> controls;
};

#endif /* SCREENS_SCREENBASE_H_ */
