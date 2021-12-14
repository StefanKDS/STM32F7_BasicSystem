/*
 * SDView.h
 *
 *  Created on: 29.09.2020
 *      Author: Stefan
 */

#ifndef SDVIEW_H_
#define SDVIEW_H_

#include "stdint.h"

void     ShowSDDirectories(uint8_t* headerString);
void     SDCardTouchDetected(uint16_t x, uint16_t y);

#endif /* SDVIEW_H_ */
