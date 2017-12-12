#include "day03.h"

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
  std::list<Day3Block> spiral;
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
      for (std::list<Day3Block>::const_iterator it = spiral.begin(); it != spiral.end(); ++it)
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
      for (std::list<Day3Block>::const_iterator it = spiral.begin(); it != spiral.end(); ++it)
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
      for (std::list<Day3Block>::const_iterator it = spiral.begin(); it != spiral.end(); ++it)
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
      for (std::list<Day3Block>::const_iterator it = spiral.begin(); it != spiral.end(); ++it)
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
