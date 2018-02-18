#ifndef DAY22_H_INCLUDED
#define DAY22_H_INCLUDED

#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <iostream>

std::string day22(std::ifstream& file);

#define DAY22_UP    0
#define DAY22_DOWN  1
#define DAY22_LEFT  2
#define DAY22_RIGHT 3

#define DAY22_CLEAN     0
#define DAY22_WEAKEND   1
#define DAY22_INFECTED  2
#define DAY22_FLAGGED   3

class Day22Node
{
private:
  Day22Node* next[4];
  void expand(int dir);
public:
  int val;
  Day22Node* getNext(int dir);
  Day22Node* getNextRaw(int dir);
  Day22Node* getEdge(int dir);
  void setNextRaw(int dir, Day22Node* addr);
  void printRow();
  Day22Node();
  ~Day22Node();
};

class Day22Virus
{
public:
  Day22Node* pos;
  int dir;
};

class Day22Matrix
{
public:
  Day22Node* matrix;
  Day22Virus virus;
  Day22Node* getMiddleNode();
  void loadRow(std::string line);
  void print();
  bool moveVirus();
  bool moveVirus2();
  Day22Matrix();
  ~Day22Matrix();
};

#endif // DAY22_H_INCLUDED
