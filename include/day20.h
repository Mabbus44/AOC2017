#ifndef DAY20_H_INCLUDED
#define DAY20_H_INCLUDED

#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>

std::string day20(std::ifstream& file);

class Day20V3
{
  public:
  int v[3];
  int& operator[](int x);
};

class Day20Particle
{
  public:
  int index;
  Day20V3 pos;
  Day20V3 vel;
  Day20V3 acc;
  void load(std::string line);
  int timeForStandstill();
  void step();
  bool operator==(Day20Particle other);
};

#endif // DAY20_H_INCLUDED
