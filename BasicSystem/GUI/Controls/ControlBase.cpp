/*
 * ControlBase.cpp
 *
 *  Created on: Aug 27, 2024
 *      Author: Stefan Seyer
 */

#include "ControlBase.h"

ControlBase::ControlBase()
{
}

ControlBase::~ControlBase()
{
}

bool ControlBase::Click(uint16_t touchX, uint16_t touchY) const
{
    if (((touchX >= x && touchX < (x + width)) &&
        (touchY >= y && touchY < (y + height))) == true)
		{
			if(OnClick != nullptr)
			{
				OnClick();
				return true;
			}
		}

    return false;
}
