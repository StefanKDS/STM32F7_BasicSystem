/*
 * ScreenManager.hpp
 *
 *  Created on: Aug 31, 2024
 *      Author: Lenovo
 */

#ifndef CONTROLS_SCREENMANAGER_HPP_
#define CONTROLS_SCREENMANAGER_HPP_

#include "ScreenBase.h"

class ScreenManager {
public:
	ScreenManager();
	virtual ~ScreenManager();

	template<typename T>
	void OpenView(uint8_t* name);

private:
	ScreenBase* view;
	ScreenBase* oldView;
};

template<typename T>
void ScreenManager::OpenView(uint8_t* name)
{
    // Überprüfen, ob T von ScreenBase abgeleitet ist
    static_assert(std::is_base_of<ScreenBase, T>::value, "T must be derived from ScreenBase");

    view = new T(name, *this);
    view->Show();
}


#endif /* CONTROLS_SCREENMANAGER_HPP_ */
