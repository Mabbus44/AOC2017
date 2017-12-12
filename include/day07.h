#ifndef DAY07_H_INCLUDED
#define DAY07_H_INCLUDED

#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>

std::string day07(std::ifstream& file);

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

#endif // DAY07_H_INCLUDED
