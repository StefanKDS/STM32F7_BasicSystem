/*
 * MainGUI.h
 *
 *  Created on: Aug 27, 2024
 *      Author: Stefan Seyer
 */

#ifndef VIEWS_MAINGUI_H_
#define VIEWS_MAINGUI_H_

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MainGUI MainGUI;

MainGUI* create_MainGUI(uint8_t* headerString);
void destroy_MainGUI(MainGUI* obj);

#ifdef __cplusplus
}
#endif

#endif /* VIEWS_MAINGUI_H_ */
