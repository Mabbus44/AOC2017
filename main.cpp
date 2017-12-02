#include <tchar.h>
#include <windows.h>
#include <Commdlg.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include "windowObjects.h"

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
        break;
      case WM_DESTROY:
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
      case WM_COMMAND:
        switch( HIWORD( wParam ) )
        {
          case BN_CLICKED:
            switch( LOWORD(wParam) )
            {
              case T000_OPEN_FILE:
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

//*************************************** DAY 1 ***************************************

/*                  char letter;
                  std::list<int> digits;
                  int digit;
                  while(file.get(letter))
                  {
                    digit = (int)letter - 48;
                    if(digit>=0 && digit<=9)
                      digits.push_back(digit);
                  }
                  std::list<int>::iterator it;
                  int digitsArray[digits.size()];
                  it = digits.begin();
                  for(unsigned int i = 0; i<digits.size(); i++)
                  {
                    digitsArray[i] = *it;
                    ++it;
                  }

                  int sum1 = 0;
                  for(unsigned int i = 0; i<digits.size()-1; i++)
                      if(digitsArray[i] == digitsArray[i+1])
                        sum1 += digitsArray[i];
                  if(digitsArray[0] == digitsArray[digits.size()-1])
                    sum1 += digitsArray[0];

                  int sum2 = 0;
                  for(unsigned int i=0; i<digits.size(); i++)
                  {
                    unsigned int i2 = i + digits.size()/2;
                    if(i2 >= digits.size())
                      i2 -= digits.size();
                    if(digitsArray[i] == digitsArray[i2])
                      sum2 += digitsArray[i];
                  }
                  std::string ans;
                  std::stringstream out;
                  out << "Part 1: " << sum1 << "\nPart 2: " << sum2;
                  ans = out.str();
                  SetWindowText(GetDlgItem(hwnd, T000_ANS), ans.c_str());*/

//*************************************** DAY 2 ***************************************
                  char letter;
                  int number = 0;
                  std::list<int> numbers;
                  std::list<std::list<int>> rows;
                  int digit;
                  while(file.get(letter))
                  {
                    switch ((int)letter)
                    {
                      case 9:     //End of number
                        if(number != 0)
                          numbers.push_back(number);
                        number = 0;
                        break;
                      case 10:    //End of row
                        if(number != 0)
                          numbers.push_back(number);
                        number = 0;
                        if(numbers.size()>0)
                          rows.push_back(numbers);
                        numbers.clear();
                        break;
                      default:    //Hopefully a digit
                        digit = (int)letter - 48;
                        if(digit<0 && digit>9)
                          MessageBox(NULL, "Unknown char found", "warning",MB_OK);
                        else
                        {
                          number *= 10;
                          number += digit;
                        }
                    }
                  }
                  int sum1 = 0;
                  for (std::list<std::list<int>>::const_iterator it1 = rows.begin(); it1 != rows.end(); ++it1)
                  {
                    unsigned int min = -1;
                    unsigned int max = 0;
                    for (std::list<int>::const_iterator it2 = it1->begin(); it2 != it1->end(); ++it2)
                    {
                      if(*it2 < min)
                        min = *it2;
                      if(*it2 > max)
                        max = *it2;
                    }
                    sum1 += max-min;
                  }
                  int sum2=0;
                  for (std::list<std::list<int>>::const_iterator it1 = rows.begin(); it1 != rows.end(); ++it1)
                    for (std::list<int>::const_iterator it2 = it1->begin(); it2 != it1->end(); ++it2)
                      for (std::list<int>::const_iterator it3 = it1->begin(); it3 != it1->end(); ++it3)
                        if(*it2%(*it3) == 0 && *it2/(*it3) != 1)
                          sum2 += *it2/(*it3);
                  std::string ans;
                  std::stringstream out;
                  out << "Part 1: " << sum1 << "\nPart 2: " << sum2;
                  ans = out.str();
                  SetWindowText(GetDlgItem(hwnd, T000_ANS), ans.c_str());
                }
                break;
            }
            break;
        }
        break;

      case WM_CTLCOLORSTATIC:
      {
        //DWORD CtrlID = GetDlgCtrlID((HWND)lParam); //Window Control ID
        //if (CtrlID == IDC_STATIC) //If desired control
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
