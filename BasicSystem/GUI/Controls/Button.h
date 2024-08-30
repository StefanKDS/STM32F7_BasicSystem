/*
 * Button.h
 *
 *  Created on: Aug 27, 2024
 *      Author: Stefan Seyer
 */

#ifndef CONTROLS_BUTTON_H_
#define CONTROLS_BUTTON_H_

#include "stdint.h"
#include "ControlBase.h"

class Button : public ControlBase {
public:
	Button(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height, uint32_t Color, uint32_t TextColor,std::function<void()> OnClickFunc, uint8_t* Text);
	virtual ~Button();
	virtual void Draw() override;
};

#endif /* CONTROLS_BUTTON_H_ */
