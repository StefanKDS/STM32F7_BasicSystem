/*
 * ScreenManager.h
 *
 *  Created on: Aug 31, 2024
 *      Author: Lenovo
 */

#ifndef CONTROLS_SCREENMANAGER_H_
#define CONTROLS_SCREENMANAGER_H_

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ScreenManager ScreenManager;

ScreenManager* create_ScreenManager();
void destroy_ScreenManager(ScreenManager* obj);

#ifdef __cplusplus
}
#endif

#endif /* CONTROLS_SCREENMANAGER_H_ */
