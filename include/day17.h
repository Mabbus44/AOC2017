#ifndef DAY17_H_INCLUDED
#define DAY17_H_INCLUDED

#include <string>
#include <sstream>
#include <list>
#include <stdlib.h>
#include <iostream>

std::string day17(std::string input);

class Day17Buffer
{
  public:
  std::list<int> buffer;
  std::list<int>::iterator pos;
  Day17Buffer();
  void stepForward(int steps);
  void insertNumber(int num);
  int getNext();
  int getAfter0();
  void output();
};

#endif // DAY17_H_INCLUDED
