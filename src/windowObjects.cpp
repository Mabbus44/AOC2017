#include "windowObjects.h"

WNDPROC oldEditProc;

LRESULT CALLBACK subEditProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
   switch (msg)
   {
    case WM_CHAR:
         switch (wParam)
         {
          case VK_RETURN:
            day3(GetParent(hwnd));
            return 0;
            break;
         }
    default:
         return CallWindowProc(oldEditProc, hwnd, msg, wParam, lParam);
   }
   return 0;
}

void defineWindowObjects(HWND hwnd)
{
  CreateWindow("BUTTON", "Load file", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 120, 10, 100, 20, hwnd, (HMENU)T000_OPEN_FILE, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
  CreateWindow("STATIC", "Calculation not started", WS_TABSTOP | WS_VISIBLE | WS_CHILD, 230, 10, 250, 160, hwnd, (HMENU)T000_ANS, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
  HWND hwndCB = CreateWindow("COMBOBOX", "", CBS_HASSTRINGS | WS_OVERLAPPED | CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE, 10, 10, 100, 600, hwnd, (HMENU)T000_DAY_SELECTION, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
  SendMessage(hwndCB, CB_ADDSTRING, 0, (LPARAM)"Day 1");
  SendMessage(hwndCB, CB_ADDSTRING, 0, (LPARAM)"Day 2");
  SendMessage(hwndCB, CB_ADDSTRING, 0, (LPARAM)"Day 3");
  SendMessage(hwndCB, CB_ADDSTRING, 0, (LPARAM)"Day 4");
  SendMessage(hwndCB, CB_ADDSTRING, 0, (LPARAM)"Day 5");
  SendMessage(hwndCB, CB_ADDSTRING, 0, (LPARAM)"Day 6");
  SendMessage(hwndCB, CB_ADDSTRING, 0, (LPARAM)"Day 7");
  SendMessage(hwndCB, CB_ADDSTRING, 0, (LPARAM)"Day 8");
  SendMessage(hwndCB, CB_ADDSTRING, 0, (LPARAM)"Day 9");
  SendMessage(hwndCB, CB_ADDSTRING, 0, (LPARAM)"Day 10");
  SendMessage(hwndCB, CB_ADDSTRING, 0, (LPARAM)"Day 11");
  SendMessage(hwndCB, CB_SETCURSEL, 0, 0);
  HWND hwndEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_BORDER | ES_LEFT, 120, 10, 100, 20, hwnd, (HMENU)T030_INPUT, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
  oldEditProc = (WNDPROC)SetWindowLongPtr(hwndEdit, GWLP_WNDPROC, (LONG_PTR)subEditProc);
}



