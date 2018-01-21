#ifndef DAY18_H_INCLUDED
#define DAY18_H_INCLUDED

#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>

#define DAY18_SND               100
#define DAY18_SET               101
#define DAY18_ADD               102
#define DAY18_MUL               103
#define DAY18_MOD               104
#define DAY18_RCV               105
#define DAY18_JGZ               106

std::string day18(std::ifstream& file);

class Day18Operation
{
public:
  int operation;
  std::string arg1;
  std::string arg2;
  Day18Operation();
  Day18Operation(std::string input);
  bool load(std::string input);
};

class Day18Variable
{
public:
  char name;
  __int64 val;
  Day18Variable();
  Day18Variable(char name, __int64 val);
};

class Day18VariableVector
{
public:
  std::vector<Day18Variable> variables;
  void add(char name);
  void output();
  __int64 getVal(std::string arg);
  void setVal(std::string name, std::string val);
  void setVal(std::string name, __int64 val);
  void copy(Day18VariableVector& other, int pVal);
};
#endif // DAY18_H_INCLUDED
