#ifndef DAY08_H_INCLUDED
#define DAY08_H_INCLUDED

#include <fstream>
#include <sstream>
#include <list>
#include <algorithm>

std::string day08(std::ifstream& file);

class Day8Variable
{
public:
  std::string name;
  int val;
  Day8Variable(std::string name, int val);
  operator==(std::string other);
};

#endif // DAY08_H_INCLUDED
