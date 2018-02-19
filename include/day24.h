#ifndef DAY24_H_INCLUDED
#define DAY24_H_INCLUDED

#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <vector>

std::string day24(std::ifstream& file);

class Day24Part
{
public:
  int sides[2];
};

class Day24Bridge
{
public:
  std::vector<Day24Part> parts;
  void loadPart(std::string line);
  int strongest(std::vector<int> usedParts, int conStr);
  void longest(std::vector<int> usedParts, int conStr, int& length, int& strength);
};

#endif // DAY24_H_INCLUDED
