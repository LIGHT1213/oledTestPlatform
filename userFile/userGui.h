#ifndef __USER_GUI_H
#define __USER_GUI_H
#include "u8g2.h"
#include "icon.h"
#include "main.h"
u8g2_t* getUserScreen();
void userGuiInit();
void userGuiTask();
#endif