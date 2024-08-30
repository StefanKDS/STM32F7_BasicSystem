/*
 * ScreenBase.h
 *
 *  Created on: Aug 27, 2024
 *      Author: Stefan Seyer
 */

#ifndef CONTROLS_SCREENBASE_H_
#define CONTROLS_SCREENBASE_H_

#include "stdint.h"
#include "ControlBase.h"
#include <vector>
#include "Button.h"
#include "Label.h"

extern "C" {
    #include "FreeRTOS.h"
    #include "queue.h"
	#include "main.h"
    extern QueueHandle_t xQueue; // Deklariere die Queue als extern
}

class ScreenBase {
public:
    ScreenBase(uint8_t* headerString);
    virtual ~ScreenBase();

public:
    void AddControlItem(ControlBase* control);
    void RefreshScreen();
    void Show();

private:
    void DrawHeader(uint8_t* headerString, uint32_t Color);
    void DrawLeftMenu();
    void DrawBottomMenu();
    static void CppTask(void* pvParameters);
    void StartCppTask();

private:
    std::vector<ControlBase*> controls;
    TaskHandle_t taskHandle;
    bool stopCppTask;
};

#endif /* CONTROLS_SCREENBASE_H_ */
