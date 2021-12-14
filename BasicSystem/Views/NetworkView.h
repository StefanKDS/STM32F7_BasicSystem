/*
 * SDView.h
 *
 *  Created on: 29.09.2020
 *      Author: Stefan
 */

#ifndef NETWORKVIEW_H_
#define NETWORKVIEW_H_

#include "stdint.h"

void ShowNetView(uint8_t* headerString);
void NetViewTouchDetected(uint16_t x, uint16_t y);

#endif /* SDVIEW_H_ */
