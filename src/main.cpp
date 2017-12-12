#include <tchar.h>
#include <windows.h>
#include <Commdlg.h>
#include <fstream>
#include <string>
#include "windowObjects.h"
#include "day01.h"
#include "day02.h"
#include "day03.h"
#include "day04.h"
#include "day05.h"
#include "day06.h"
#include "day07.h"
#include "day08.h"
#include "day09.h"
#include "day10.h"
#include "day11.h"


/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("AOC2017");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
  HWND hwnd;               /* This is the handle for our window */
  MSG messages;            /* Here messages to the application are saved */
  WNDCLASSEX wincl;        /* Data structure for the windowclass */

  /* The Window structure */
  wincl.hInstance = hThisInstance;
  wincl.lpszClassName = szClassName;
  wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
  wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
  wincl.cbSize = sizeof (WNDCLASSEX);
  /* Use default icon and mouse-pointer */
  wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
  wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
  wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
  wincl.lpszMenuName = NULL;                 /* No menu */
  wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
  wincl.cbWndExtra = 0;                      /* structure or the window instance */
  /* Use Windows's default colour as the background of the window */
  wincl.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
  /* Register the window class, and if it fails quit the program */
  if (!RegisterClassEx (&wincl))
    return 0;

  /* The class is registered, let's create the program*/
  hwnd = CreateWindowEx (
         0,                   /* Extended possibilites for variation */
         szClassName,         /* Classname */
         _T("Advent Of Code 2017"),       /* Title Text */
         WS_OVERLAPPEDWINDOW, /* default window */
         CW_USEDEFAULT,       /* Windows decides the position */
         CW_USEDEFAULT,       /* where the window ends up on the screen */
         544,                 /* The programs width */
         375,                 /* and height in pixels */
         HWND_DESKTOP,        /* The window is a child-window to desktop */
         NULL,                /* No menu */
         hThisInstance,       /* Program Instance handler */
         NULL                 /* No Window Creation data */
         );

  /* Make the window visible on the screen */
  ShowWindow (hwnd, nCmdShow);

  defineWindowObjects(hwnd);
  /* Run the message loop. It will run until GetMessage() returns 0 */
  while (GetMessage (&messages, NULL, 0, 0))
  {
    /* Translate virtual-key messages into character messages */
    TranslateMessage(&messages);
    /* Send message to WindowProcedure */
    DispatchMessage(&messages);
  }

  /* The program return-value is 0 - The value that PostQuitMessage() gave */
  return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
      case WM_CREATE:
      {
        break;
      }
      case WM_DESTROY:
      {
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
      }
      case WM_COMMAND:
      {
        switch( HIWORD( wParam ) )
        {
          case BN_CLICKED:
          {
            switch( LOWORD(wParam) )
            {
              case T000_OPEN_FILE:
              {
                OPENFILENAME ofn;
                char filename[256];
                ZeroMemory( &ofn , sizeof( ofn));
                ofn.lStructSize = sizeof ( ofn );
                ofn.lpstrFile = filename;
                ofn.lpstrFile[0] = L'\0';
                ofn.nMaxFile = 2048;
                ofn.lpstrFilter = _T("All\0*.*\0Text\0*.TXT\0");
                ofn.Flags = OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST;
                if(GetOpenFileName( &ofn ))
                {
                  std::ifstream file(filename);
                  if(!file.is_open())
                  {
                      MessageBox(hwnd, "Could not open file", "Error", MB_OK);
                      return 0;
                  }
                  HWND selectedDayCB = GetDlgItem(hwnd, T000_DAY_SELECTION);
                  int selectedDay = SendMessage(selectedDayCB, CB_GETCURSEL, 0, 0) + 1;
                  std::string ans;
                  switch(selectedDay)
                  {
                    case 1:
                    {
                      ans = day01(file);
                      break;
                    }
                    case 2:
                    {
                      ans = day02(file);
                      break;
                    }
                    case 4:
                    {
                      ans = day04(file);
                      break;
                    }
                    case 5:
                    {
                      ans = day05(file);
                      break;
                    }
                    case 6:
                    {
                      ans = day06(file);
                      break;
                    }
                    case 7:
                    {
                      ans = day07(file);
                      break;
                    }
                    case 8:
                    {
                      ans = day08(file);
                      break;
                    }
                    case 9:
                    {
                      ans = day09(file);
                      break;
                    }
                    case 10:
                    {
                      ans = day10(file);
                      break;
                    }
                    case 11:
                    {
                      ans = day11(file);
                      int a= 1+1;
                      break;
                    }
                    default:
                      break;
                  }
                  SetWindowText(GetDlgItem(hwnd, T000_ANS), ans.c_str());
                  file.close();
                }
                break;
              }
            }
            break;
          }
          case CBN_SELCHANGE:
          {
            switch( LOWORD(wParam) )
            {
              case T000_DAY_SELECTION:
              {
                HWND selectedDayCB = GetDlgItem(hwnd, T000_DAY_SELECTION);
                int selectedDay = SendMessage(selectedDayCB, CB_GETCURSEL, 0, 0) + 1;
                HWND t000OpenFile = GetDlgItem(hwnd,T000_OPEN_FILE);
                HWND t030Input = GetDlgItem(hwnd,T030_INPUT);
                ShowWindow(t000OpenFile, SW_HIDE);
                ShowWindow(t030Input, SW_HIDE);
                switch(selectedDay)
                {
                  case 3:
                    ShowWindow(t030Input, SW_SHOW);
                    break;
                  default:
                    ShowWindow(t000OpenFile, SW_SHOW);
                    break;
                }
                break;
              }
            }
          }
        }
        break;
      }
      case WM_CTLCOLORSTATIC:
      {
        HDC hdcStatic = (HDC) wParam;
        SetBkColor(hdcStatic, RGB(255,255,255));
        static HBRUSH hBrush = CreateSolidBrush(RGB(255,255,255));
        return (INT_PTR)hBrush;
        break;
      }
      default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}
