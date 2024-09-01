/*
 * ScreenManager.cpp
 *
 *  Created on: Aug 31, 2024
 *      Author: Lenovo
 */

#include <ScreenManager.h>
#include "MainView.hpp"
#include "ScreenManager.hpp"

ScreenManager::ScreenManager()
{
	view = nullptr;
	OpenView<MainView>((uint8_t*)"Main");
}

ScreenManager::~ScreenManager()
{

}

// C-Schnittstelle ////////////////////////////////////////////////////////////////////////
extern "C" {
ScreenManager* create_ScreenManager()
{
    return new ScreenManager();
}

void destroy_ScreenManager(ScreenManager* obj)
{
    delete obj;
}

}
