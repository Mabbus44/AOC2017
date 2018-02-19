#ifndef DAY25_H_INCLUDED
#define DAY25_H_INCLUDED

#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <vector>

std::string day25(std::ifstream& file);

#define DAY25_LEFT  0
#define DAY25_RIGHT 1

class Day25Node
{
private:
  Day25Node* next[2];
  void expand(int dir);
public:
  int val;
  Day25Node* getNext(int dir);
  Day25Node* getNextRaw(int dir);
  Day25Node* getEdge(int dir);
  void setNextRaw(int dir, Day25Node* addr);
  int checksum();
  Day25Node();
  ~Day25Node();
};

class Day25Instruction
{
public:
  char state;
  bool writeValue[2];
  bool moveDirection[2];
  char nextState[2];
};

class Day25InstructionList
{
public:
  char beginState;
  int stepGoal;
  std::vector<Day25Instruction> instructions;
  void loadInstructions(std::ifstream& file);
  void print();
};

class Day25Tape
{
public:
  char state;
  Day25InstructionList list;
  Day25Node* tape;
  Day25Tape();
  ~Day25Tape();
  void performInstruction();
};

#endif // DAY25_H_INCLUDED
