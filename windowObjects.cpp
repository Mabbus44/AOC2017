#include "windowObjects.h"

void defineWindowObjects(HWND hwnd)
{
  HWND hwndButton = CreateWindow("BUTTON", "OK", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 10, 100, 100, hwnd, (HMENU)T011_OPEN_FILE, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
}
