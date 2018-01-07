#ifndef DAY16_H_INCLUDED
#define DAY16_H_INCLUDED

#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>

#define DAY16_SPIN              100
#define DAY16_SWITCH_POSITIONS  101
#define DAY16_SWITCH_PARTNERS   102

std::string day16(std::ifstream& file);

class Day16Instruction
{
public:
  int operation;
  int arg1;
  int arg2;
  Day16Instruction();
  Day16Instruction(std::string instruction);
  void load(std::string instruction);
};

#endif // DAY16_H_INCLUDED
