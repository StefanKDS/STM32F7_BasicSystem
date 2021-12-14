/*
 * BaseView.h
 *
 *  Created on: 29.09.2020
 *      Author: Stefan
 */

#ifndef BASEVIEW_H_
#define BASEVIEW_H_

#include "stdint.h"

void DrawBaseScreen(uint8_t* headerString, uint32_t Color);
void ViewTouchDetected(uint16_t x, uint16_t y);

#endif /* SDVIEW_H_ */
