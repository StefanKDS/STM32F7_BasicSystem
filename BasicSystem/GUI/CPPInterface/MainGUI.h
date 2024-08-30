/*
 * MainGUI.h
 *
 *  Created on: Aug 27, 2024
 *      Author: Stefan Seyer
 */

#ifndef CPPINTERFACE_MAINGUI_H_
#define CPPINTERFACE_MAINGUI_H_

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MainGUI MainGUI;

MainGUI* create_MainGUI(uint8_t* headerString);
void destroy_MainGUI(MainGUI* obj);
void displayTouched_MainGUI(MainGUI* obj, uint16_t x, uint16_t y);

#ifdef __cplusplus
}
#endif

#endif /* CPPINTERFACE_MAINGUI_H_ */