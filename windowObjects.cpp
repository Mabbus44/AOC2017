#include "windowObjects.h"

void day3(HWND hwnd);

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
  CreateWindow("STATIC", "Calculation not started", WS_TABSTOP | WS_VISIBLE | WS_CHILD, 230, 10, 150, 60, hwnd, (HMENU)T000_ANS, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
  HWND hwndCB = CreateWindow("COMBOBOX", "", CBS_HASSTRINGS | WS_OVERLAPPED | CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE, 10, 10, 100, 600, hwnd, (HMENU)T000_DAY_SELECTION, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
  SendMessage(hwndCB, CB_ADDSTRING, 0, (LPARAM)"Day 1");
  SendMessage(hwndCB, CB_ADDSTRING, 0, (LPARAM)"Day 2");
  SendMessage(hwndCB, CB_ADDSTRING, 0, (LPARAM)"Day 3");
  SendMessage(hwndCB, CB_ADDSTRING, 0, (LPARAM)"Day 4");
  SendMessage(hwndCB, CB_ADDSTRING, 0, (LPARAM)"Day 5");
  SendMessage(hwndCB, CB_SETCURSEL, 0, 0);
  HWND hwndEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_BORDER | ES_LEFT, 120, 10, 100, 20, hwnd, (HMENU)T030_INPUT, (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);
  oldEditProc = (WNDPROC)SetWindowLongPtr(hwndEdit, GWLP_WNDPROC, (LONG_PTR)subEditProc);
}

void day3(HWND hwnd)
{
  int vDist = 1, hDist = 1;
  int x = 0, y = 0;
  int i = 0;
  int num = 1;
  char inputText[1000];
  GetWindowText(GetDlgItem(hwnd, T030_INPUT), inputText, sizeof(inputText));
  int input = atoi(inputText);
  while(num < input)
  {
    i = 0;
    while(num < input && i != hDist)
    {
      num++;
      i++;
      x++;
    }
    i = 0;
    while(num < input && i != vDist)
    {
      num++;
      i++;
      y--;
    }
    i = 0;
    hDist++;
    vDist++;
    while(num < input && i != hDist)
    {
      num++;
      i++;
      x--;
    }
    i = 0;
    while(num < input && i != vDist)
    {
      num++;
      i++;
      y++;
    }
    hDist++;
    vDist++;
  }
  int ans1 = abs(x) + abs(y);
  std::list<Block> spiral;
  vDist = 1;
  hDist = 1;
  x = 0;
  y = 0;
  num = 1;
  spiral.push_back({x,y,num});
  while(num <= input)
  {
    i = 0;
    while(num <= input && i != hDist)
    {
      i++;
      x++;
      num = 0;
      for (std::list<Block>::const_iterator it = spiral.begin(); it != spiral.end(); ++it)
        if(abs(x-it->x)<2 && abs(y-it->y)<2)
          num += it->value;
      spiral.push_back({x,y,num});
    }
    i = 0;
    while(num <= input && i != vDist)
    {
      i++;
      y--;
      num = 0;
      for (std::list<Block>::const_iterator it = spiral.begin(); it != spiral.end(); ++it)
        if(abs(x-it->x)<2 && abs(y-it->y)<2)
          num += it->value;
      spiral.push_back({x,y,num});
    }
    i = 0;
    hDist++;
    vDist++;
    while(num <= input && i != hDist)
    {
      i++;
      x--;
      num = 0;
      for (std::list<Block>::const_iterator it = spiral.begin(); it != spiral.end(); ++it)
        if(abs(x-it->x)<2 && abs(y-it->y)<2)
          num += it->value;
      spiral.push_back({x,y,num});
    }
    i = 0;
    while(num <= input && i != vDist)
    {
      i++;
      y++;
      num = 0;
      for (std::list<Block>::const_iterator it = spiral.begin(); it != spiral.end(); ++it)
        if(abs(x-it->x)<2 && abs(y-it->y)<2)
          num += it->value;
      spiral.push_back({x,y,num});
    }
    hDist++;
    vDist++;
  }
  int ans2 = num;
  std::string ans;
  std::stringstream out;
  out << "Day 3\nPart 1: " << ans1 << "\nPart 2: " << ans2;
  ans = out.str();
  SetWindowText(GetDlgItem(hwnd, T000_ANS), ans.c_str());
}
