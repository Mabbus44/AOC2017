#ifndef DAY13_H_INCLUDED
#define DAY13_H_INCLUDED

#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

std::string day13(std::ifstream& file);

class Day13Wall
{
public:
  int depth;
  int range;
  int pos;
  bool dir;
  Day13Wall();
  void move();
};

#endif // DAY13_H_INCLUDED
