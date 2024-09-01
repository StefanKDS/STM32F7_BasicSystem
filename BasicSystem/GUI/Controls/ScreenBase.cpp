/*
 * ScreenBase.cpp
 *
 *  Created on: Aug 27, 2024
 *      Author: Stefan Seyer
 */

#include "ScreenBase.h"
#include "stm32746g_discovery_lcd.h"
#include "ScreenManager.hpp"


ScreenBase::ScreenBase(uint8_t* HeaderString, ScreenManager& manager)
: screenManager(manager)
{
	stopCppTask = false;
	headerString = HeaderString;
    StartCppTask();
}

void ScreenBase::Show()
{
	BSP_LCD_Clear(LCD_COLOR_BLACK);

	DrawHeader(headerString, LCD_COLOR_ST_ORANGE);
	DrawLeftMenu();
	DrawBottomMenu();

	for (ControlBase* control : controls)
	{
	    control->Draw();
	}
}

void ScreenBase::DrawHeader(uint8_t* headerString, uint32_t Color)
{
    uint32_t oldColor = BSP_LCD_GetTextColor();
    BSP_LCD_SetTextColor(Color);
    BSP_LCD_FillCircle(21, 18, 18);
    BSP_LCD_FillRect(20, 0, BSP_LCD_GetXSize() - 31, 20);
    BSP_LCD_FillRect(2, 18, 60, 19);
    BSP_LCD_FillCircle(BSP_LCD_GetXSize() - 12, 9, 9);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_FillCircle(62, 33, 12);

    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
    BSP_LCD_SetTextColor(Color);
    BSP_LCD_SetFont(&Font20);
    BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize() - 180, 0, headerString, LEFT_MODE);

    BSP_LCD_SetTextColor(oldColor);
}

void ScreenBase::DrawLeftMenu()
{
    uint32_t oldColor = BSP_LCD_GetTextColor();
    BSP_LCD_SetTextColor(LCD_COLOR_ST_SKIN);
    BSP_LCD_FillRect(2, 39, 48, 80);

    BSP_LCD_SetTextColor(LCD_COLOR_ST_GREEN);
    BSP_LCD_FillRect(2, 121, 48, 30);
    BSP_LCD_FillRect(2, 153, 48, 30);

    BSP_LCD_SetTextColor(LCD_COLOR_ST_MAGENTA);
    BSP_LCD_FillRect(2, 186, 48, 30);

    BSP_LCD_SetTextColor(LCD_COLOR_ST_MAGENTA2);
    BSP_LCD_FillRect(2, 218, 48, 28);

    BSP_LCD_SetTextColor(oldColor);
}

void ScreenBase::DrawBottomMenu()
{
    uint32_t oldColor = BSP_LCD_GetTextColor();

    BSP_LCD_SetTextColor(LCD_COLOR_ST_LIGHTBLUE);
    BSP_LCD_FillCircle(BSP_LCD_GetXSize() - 12, BSP_LCD_GetYSize() - 6, 5);
    BSP_LCD_FillRect(11, BSP_LCD_GetYSize() - 11, BSP_LCD_GetXSize() - 25, 11);
    BSP_LCD_FillCircle(12, BSP_LCD_GetYSize() - 11, 10);
    BSP_LCD_FillRect(2, BSP_LCD_GetYSize() - 24, 60, 14);

    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_FillCircle(61, BSP_LCD_GetYSize() - 24, 11);
    BSP_LCD_FillRect(BSP_LCD_GetXSize() - 20, BSP_LCD_GetYSize() - 11, 2, 11);
    BSP_LCD_FillRect(BSP_LCD_GetXSize() - 30, BSP_LCD_GetYSize() - 11, 6, 11);

    BSP_LCD_SetTextColor(oldColor);
}

void ScreenBase::AddControlItem(ControlBase* control)
{
    controls.push_back(control);
}

void ScreenBase::CppTask(void* pvParameters)
{
	ScreenBase* instance = static_cast<ScreenBase*>(pvParameters);

    TSDataStruct data;

    for (;;)
    {
    	if(instance->stopCppTask)
    	{
    		break;
    	}

        if (xQueueReceive(tsQueue, &data, portMAX_DELAY))
        {
        	for (ControlBase* control : instance->controls)
        		{
        		    if (control->Click(data.x, data.y))
        		    {
        		        break;
        		   }
        		}
        }
    }
}

void ScreenBase::StartCppTask()
{
    xTaskCreate(CppTask, "CppTask", configMINIMAL_STACK_SIZE, this, 1, &taskHandle);
}

ScreenBase::~ScreenBase()
{
	stopCppTask = true;

	// Task löschen, wenn er existiert
	if (taskHandle != NULL)
	{
	    vTaskDelete(taskHandle);
	}

	for (ControlBase* control : controls)
	{
		delete control;
	}
}
