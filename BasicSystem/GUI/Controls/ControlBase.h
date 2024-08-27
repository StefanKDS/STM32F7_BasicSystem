/*
 * ControlBase.h
 *
 *  Created on: Aug 27, 2024
 *      Author: Stefan Seyer
 */

#ifndef CONTROLS_CONTROLBASE_H_
#define CONTROLS_CONTROLBASE_H_

#include "stdint.h"
#include "stm32746g_discovery_lcd.h"

class ControlBase {
public:
	ControlBase();
	virtual ~ControlBase();

	virtual void Draw(){};
	bool Click(uint16_t x, uint16_t y) const;

public:
	uint16_t x;
	uint16_t y;
	uint16_t width;
	uint16_t height;
	void (*OnClick)();

};

#endif /* CONTROLS_CONTROLBASE_H_ */
