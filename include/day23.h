#ifndef DAY23_H_INCLUDED
#define DAY23_H_INCLUDED

#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>

std::string day23(std::ifstream& file);

#define DAY23_SET               100
#define DAY23_SUB               101
#define DAY23_MUL               102
#define DAY23_JNZ               103

class Day23Operation
{
public:
  int operation;
  std::string arg1;
  std::string arg2;
  Day23Operation();
  Day23Operation(std::string input);
  bool load(std::string input);
};

class Day23Variable
{
public:
  char name;
  __int64 val;
  Day23Variable();
  Day23Variable(char name, __int64 val);
};

class Day23VariableVector
{
public:
  std::vector<Day23Variable> variables;
  void add(char name);
  void output();
  __int64 getVal(std::string arg);
  void setVal(std::string name, std::string val);
  void setVal(std::string name, __int64 val);
  void copy(Day23VariableVector& other, int pVal);
};

#endif // DAY23_H_INCLUDED
