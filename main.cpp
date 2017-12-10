#include <tchar.h>
#include <windows.h>
#include <Commdlg.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <math.h>
#include <algorithm>
#include "windowObjects.h"
#include "smallClasses.h"

class Day7Program
{
  public:
    Day7Program();
    Day7Program(std::string name, int weight);
    std::string name;
    int weight;
    int trueWeight;
    std::vector<Day7Program*> children;
    void searchForChildren(std::vector<Day7Program*> &programList);
    int getTrueWeight(Day7Program* &wrongProgram);
    int getMissingWeight(bool toBig);
};


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
                  int ans1 = 0;
                  int ans2 = 0;
                  std::string strAns1;
                  std::string strAns2;
                  std::string debugAns;
                  std::string ans;
                  std::stringstream out;
                  switch(selectedDay)
                  {
//*************************************** DAY 1 ***************************************
                    case 1:
                    {
                      char letter;
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

                      for(unsigned int i = 0; i<digits.size()-1; i++)
                          if(digitsArray[i] == digitsArray[i+1])
                            ans1 += digitsArray[i];
                      if(digitsArray[0] == digitsArray[digits.size()-1])
                        ans1 += digitsArray[0];

                      for(unsigned int i=0; i<digits.size(); i++)
                      {
                        unsigned int i2 = i + digits.size()/2;
                        if(i2 >= digits.size())
                          i2 -= digits.size();
                        if(digitsArray[i] == digitsArray[i2])
                          ans2 += digitsArray[i];
                      }
                      out << "Day " << selectedDay << "\nPart 1: " << ans1 << "\nPart 2: " << ans2;
                      break;
                    }
//*************************************** DAY 2 ***************************************
                    case 2:
                    {
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
                      for (std::list<std::list<int>>::const_iterator it1 = rows.begin(); it1 != rows.end(); ++it1)
                      {
                        unsigned int min = -1;
                        unsigned int max = 0;
                        for (std::list<int>::const_iterator it2 = it1->begin(); it2 != it1->end(); ++it2)
                        {
                          if((unsigned int)(*it2) < min)
                            min = *it2;
                          if((unsigned int)(*it2) > max)
                            max = *it2;
                        }
                        ans1 += max-min;
                      }
                      for (std::list<std::list<int>>::const_iterator it1 = rows.begin(); it1 != rows.end(); ++it1)
                        for (std::list<int>::const_iterator it2 = it1->begin(); it2 != it1->end(); ++it2)
                          for (std::list<int>::const_iterator it3 = it1->begin(); it3 != it1->end(); ++it3)
                            if(*it2%(*it3) == 0 && *it2/(*it3) != 1)
                              ans2 += *it2/(*it3);
                      out << "Day " << selectedDay << "\nPart 1: " << ans1 << "\nPart 2: " << ans2;
                      break;
                    }
//*************************************** DAY 4 ***************************************
                    case 4:
                    {
                      std::string line;
                      while(std::getline(file, line))
                      {
                        std::istringstream iss(line);
                        std::list<std::string> passphrase;
                        std::list<std::string> passphrase2;
                        bool valid = true;
                        bool valid2 = true;
                        do
                        {
                            std::string subs;
                            iss >> subs;
                            if(subs.length() > 0)
                            {
                              std::list<std::string>::iterator it;
                              for(it=passphrase.begin(); it!=passphrase.end(); ++it)
                              {
                                if(subs.compare(*it) == 0)
                                  valid = false;
                              }
                              passphrase.push_back(subs);
                              std::sort(subs.begin(), subs.end());
                              for(it=passphrase2.begin(); it!=passphrase2.end(); ++it)
                              {
                                if(subs.compare(*it) == 0)
                                  valid2 = false;
                              }
                              passphrase2.push_back(subs);
                            }
                        } while (iss);
                        if(valid)
                          ans1++;
                        if(valid2)
                          ans2++;
                      }
                      out << "Day " << selectedDay << "\nPart 1: " << ans1 << "\nPart 2: " << ans2;
                      break;
                    }
//*************************************** DAY 5 ***************************************
                    case 5:
                    {
                      std::string line;
                      int mazeLength = 0;
                      std::list<int> mazeList;
                      while(std::getline(file, line))
                      {
                        if(line.length()>0)
                        {
                          mazeList.push_back(atoi(line.c_str()));   //Becaure std::stoi() is bugged in mingw :(
                          mazeLength++;
                        }
                      }
                      int maze[mazeLength];
                      int maze2[mazeLength];
                      mazeLength = 0;
                      for(std::list<int>::iterator it=mazeList.begin(); it!=mazeList.end(); ++it)
                      {
                        maze[mazeLength] = *it;
                        maze2[mazeLength] = *it;
                        mazeLength++;
                      }
                      int pos = 0;
                      while(pos >= 0 && pos < mazeLength)
                      {
                        maze[pos]++;
                        pos += maze[pos] - 1;
                        ans1++;
                      }
                      pos = 0;
                      while(pos >= 0 && pos < mazeLength)
                      {
                        int oldPos = pos;
                        pos += maze2[pos];
                        if(maze2[oldPos] >2)
                          maze2[oldPos]--;
                        else
                          maze2[oldPos]++;
                        ans2++;
                      }
                      out << "Day " << selectedDay << "\nPart 1: " << ans1 << "\nPart 2: " << ans2;
                      break;
                    }
//*************************************** DAY 6 ***************************************
                    case 6:
                    {
                      std::string line;
                      std::getline(file, line);
                      std::istringstream iss(line);
                      std::vector<int> v;
                      std::vector<std::vector<int>> oldVectors;
                      do
                      {
                          std::string subs;
                          iss >> subs;
                          if(subs.length() > 0)
                            v.push_back(atoi(subs.c_str()));
                      } while (iss);
                      int seqLength = v.size();
                      int loopBackTo = 0;
                      int vCount = 0;
                      bool done = false;
                      oldVectors.push_back(v);
                      while(!done)
                      {
                        int vPos = 0;
                        int vMax = 0;
                        for(int i=0; i<seqLength; i++)
                        {
                          if(v[i]>vMax)
                          {
                            vPos = i;
                            vMax = v[i];
                          }
                        }
                        v[vPos] = 0;
                        while(vMax>0)
                        {
                          vPos++;
                          if(vPos>=seqLength)
                            vPos = 0;
                          v[vPos]++;
                          vMax--;
                        }
                        for(std::vector<std::vector<int>>::iterator it=oldVectors.begin(); it!=oldVectors.end(); ++it)
                        {
                          bool identical = true;
                          for(int i=0; i<seqLength && identical; i++)
                            if(v[i] != (*it)[i])
                              identical = false;
                          if(identical)
                          {
                            done = true;
                            loopBackTo = it - oldVectors.begin();
                          }
                        }
                        oldVectors.push_back(v);
                        vCount++;
                      }
                      ans1 = vCount;
                      ans2 = vCount - loopBackTo;
                      out << "Day " << selectedDay << "\nPart 1: " << ans1 << "\nPart 2: " << ans2;
                      break;
                    }
//*************************************** DAY 7 ***************************************
                    case 7:
                    {
                      std::string line;
                      std::vector<Day7Program*> allPrograms;
                      Day7Program* base;
                      while(std::getline(file, line))
                      {
                        if(line.length() > 0)
                        {
                          std::istringstream iss(line);
                          int inputSequence = 0;
                          Day7Program* p = new Day7Program();
                          do
                          {
                              std::string subs;
                              iss >> subs;
                              if(subs.length() > 0)
                              {
                                switch(inputSequence)
                                {
                                  case 0:
                                  {
                                    p->name = subs;
                                    break;
                                  }
                                  case 1:
                                  {
                                    p->weight = atoi(subs.substr(1, subs.length()-2).c_str());
                                    break;
                                  }
                                  case 2:
                                    break;
                                  default:
                                  {
                                    if(subs.substr(subs.length()-1, 1).compare(",") == 0)
                                      p->children.push_back(new Day7Program(subs.substr(0, subs.length()-1), 0));
                                    else
                                      p->children.push_back(new Day7Program(subs, 0));
                                    break;
                                  }
                                }
                                inputSequence++;
                              }
                          } while (iss);
                          if(p->name.length() > 0)
                            allPrograms.push_back(p);
                        }
                      }
                      base = *(allPrograms.begin());
                      bool baseFound = false;
                      while(!baseFound)
                      {
                        baseFound = true;
                        for(std::vector<Day7Program*>::iterator it1=allPrograms.begin(); it1!=allPrograms.end() && baseFound; ++it1)
                        {
                          for(std::vector<Day7Program*>::iterator it2=(*it1)->children.begin(); it2!=(*it1)->children.end() && baseFound; ++it2)
                          {
                            if(base->name.compare((*it2)->name) == 0)
                            {
                               base = (*it1);
                               baseFound=false;
                            }
                          }
                        }
                      }
                      strAns1 = base->name;
                      base->searchForChildren(allPrograms);
                      Day7Program* p = NULL;
                      ans2 = -base->getTrueWeight(p);
                      out << "Day " << selectedDay << "\nPart 1: " << strAns1 << "\nPart 2: " << ans2;
                      break;
                    }
                    default:
                      break;
                  }
                  ans = out.str();
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




Day7Program::Day7Program()
{
  name = "";
  weight = 0;
}


Day7Program::Day7Program(std::string name, int weight)
{
  this->name = name;
  this->weight = weight;
}

void Day7Program::searchForChildren(std::vector<Day7Program*> &programList)
{
  for(std::vector<Day7Program*>::iterator it1=this->children.begin(); it1!=this->children.end(); ++it1)
  {
    for(std::vector<Day7Program*>::iterator it2=programList.begin(); it2!=programList.end(); ++it2)
    {
      if((*it1)->name.compare((*it2)->name) == 0)
      {
        delete (*it1);
        (*it1) = (*it2);
      }
    }
    (*it1)->searchForChildren(programList);
  }
}

int Day7Program::getTrueWeight(Day7Program* &wrongProgram)
{
  int weight = 0;
  int oldWeight = 0;
  int totWeight = 0;
  int min = -1;
  int max = -1;
  bool childIsWrong = false;
  bool wrongProgramAlreadyFound = false;
  bool grandchildIsWrong = false;

  if(wrongProgram != NULL)
    wrongProgramAlreadyFound = true;
  for(std::vector<Day7Program*>::iterator it1=this->children.begin(); it1!=this->children.end(); ++it1)
  {
    oldWeight = weight;
    weight = (*it1)->getTrueWeight(wrongProgram);
    if(weight < 0)
      return weight;
    totWeight += weight;
    if(oldWeight != 0 && oldWeight != weight)
      childIsWrong = true;
    if(weight < min || min == -1)
      min = weight;
    if(weight > max)
      max = weight;
  }
  if(wrongProgram != NULL && !wrongProgramAlreadyFound)
    grandchildIsWrong = true;
  if(grandchildIsWrong)
  {
    for(std::vector<Day7Program*>::iterator it1=this->children.begin(); it1!=this->children.end(); ++it1)
    {
      if(wrongProgram == *it1)
      {
        if((*it1)->trueWeight > min)
          return wrongProgram->getMissingWeight(true);
        else
          return wrongProgram->getMissingWeight(false);
      }
    }
    std::cout << "grandchildIsWrong: " << this->name << std::endl;
    for(std::vector<Day7Program*>::iterator it1=this->children.begin(); it1!=this->children.end(); ++it1)
    {
      std::cout << "   Child: " << (*it1)->name << std::endl;
    }
  }
  if(childIsWrong)
  {
    wrongProgram = this;
    std::cout << "ChildIsWrong: " << this->name << std::endl;
    for(std::vector<Day7Program*>::iterator it1=this->children.begin(); it1!=this->children.end(); ++it1)
    {
      std::cout << "   Child: " << (*it1)->name << std::endl;
    }
  }
  trueWeight = totWeight + this->weight;
  return trueWeight;
}

int Day7Program::getMissingWeight(bool toBig)
{
  int min = -1;
  int max = -1;
  int weight = 0;
  for(std::vector<Day7Program*>::iterator it1=this->children.begin(); it1!=this->children.end(); ++it1)
  {
    weight = (*it1)->trueWeight;
    if(weight < min || min == -1)
      min = weight;
    if(weight > max)
      max = weight;
  }
  std::cout << "getMissingWeight: " << this->name << std::endl;
  for(std::vector<Day7Program*>::iterator it1=this->children.begin(); it1!=this->children.end(); ++it1)
  {
    if((*it1)->trueWeight > min && toBig)
      return -((*it1)->weight - (max - min));
    if((*it1)->trueWeight < max && !toBig)
      return -((*it1)->weight + (max - min));
  }
  return 0;   //Ska aldrig hända
}
