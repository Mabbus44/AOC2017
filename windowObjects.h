#ifndef WINDOWOBJECTS_H_INCLUDED
#define WINDOWOBJECTS_H_INCLUDED

#include "smallClasses.h"
#include <list>
#include <string.h>
#include <iostream>
#include <sstream>
#include <windows.h>

#define T000_OPEN_FILE      100
#define T000_ANS            101
#define T000_DAY_SELECTION  102
#define T030_INPUT           103


void defineWindowObjects(HWND hwnd);

#endif // WINDOWOBJECTS_H_INCLUDED
