#include "windowObjects.h"

void defineWindowObjects(HWND hwnd)
{
  CreateWindow("BUTTON", "Load file", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 10, 100, 20, hwnd, (HMENU)T000_OPEN_FILE, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
  CreateWindow("STATIC", "Calculation not started", WS_TABSTOP | WS_VISIBLE | WS_CHILD, 120, 10, 150, 40, hwnd, (HMENU)T000_ANS, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
}
