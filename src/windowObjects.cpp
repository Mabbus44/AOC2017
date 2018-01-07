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
        {
          HWND selectedDayCB = GetDlgItem(GetParent(hwnd), T000_DAY_SELECTION);
          int selectedDay = SendMessage(selectedDayCB, CB_GETCURSEL, 0, 0) + 1;
          std::string ans;
          switch (selectedDay)
          {
            case 3:
            {
              day3(GetParent(hwnd));
              break;
            }
            case 14:
            {
              char inputText[1000];
              GetWindowText(hwnd, inputText, sizeof(inputText));
              std::string intputStr = inputText;
              ans = day14(intputStr);
              SetWindowText(GetDlgItem(GetParent(hwnd), T000_ANS), ans.c_str());
              break;
            }
            case 17:
            {
              char inputText[1000];
              GetWindowText(hwnd, inputText, sizeof(inputText));
              std::string intputStr = inputText;
              ans = day17(intputStr);
              SetWindowText(GetDlgItem(GetParent(hwnd), T000_ANS), ans.c_str());
              break;
            }
          }
          return 0;
          break;
        }
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
  SendMessage(hwndCB, CB_ADDSTRING, 0, (LPARAM)"Day 12");
  SendMessage(hwndCB, CB_ADDSTRING, 0, (LPARAM)"Day 13");
  SendMessage(hwndCB, CB_ADDSTRING, 0, (LPARAM)"Day 14");
  SendMessage(hwndCB, CB_ADDSTRING, 0, (LPARAM)"Day 15");
  SendMessage(hwndCB, CB_ADDSTRING, 0, (LPARAM)"Day 16");
  SendMessage(hwndCB, CB_ADDSTRING, 0, (LPARAM)"Day 17");
  SendMessage(hwndCB, CB_SETCURSEL, 0, 0);
  HWND hwndEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_BORDER | ES_LEFT, 120, 10, 100, 20, hwnd, (HMENU)T030_INPUT, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
  oldEditProc = (WNDPROC)SetWindowLongPtr(hwndEdit, GWLP_WNDPROC, (LONG_PTR)subEditProc);
}




