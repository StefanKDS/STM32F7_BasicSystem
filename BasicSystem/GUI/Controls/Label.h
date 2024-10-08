/*
 * Label.h
 *
 *  Created on: Aug 27, 2024
 *      Author: Lenovo
 */

#ifndef CONTROLS_LABEL_H_
#define CONTROLS_LABEL_H_

#include "stdint.h"
#include "ControlBase.h"

class Label : public ControlBase{
public:
	Label(uint16_t Xpos, uint16_t Ypos, uint32_t TextColor, std::function<void()> OnClickFunc, uint8_t* Text);
	virtual ~Label();
	virtual void Draw() override;
};

#endif /* CONTROLS_LABEL_H_ */
