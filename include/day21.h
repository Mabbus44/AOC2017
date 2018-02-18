#ifndef DAY21_H_INCLUDED
#define DAY21_H_INCLUDED

#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <list>

std::string day21(std::ifstream& file);

class Day21Matrix
{
private:
  int size;
public:
  bool** matrix;
  void load(std::string line);
  Day21Matrix();
  Day21Matrix(std::string line);
  ~Day21Matrix();
  void rot();
  void flip();
  void clean();
  void setSize(int size);
  int getSize();
  Day21Matrix* getSubMatrix(int startX, int startY, int size);
  void print();
  int countOn();
  Day21Matrix& operator=(Day21Matrix& other);
  bool operator==(Day21Matrix& other);
};

class Day21Rule
{
public:
  Day21Rule();
  ~Day21Rule();
  std::list<Day21Matrix*> input;
  Day21Matrix output;
  void load(std::string line);
  bool applyRule(Day21Matrix* mat);
  void print();
  void clean();
};

class Day21Art
{
public:
  std::list<Day21Rule> rules;
  int splitArtSize;
  Day21Matrix art;
  Day21Matrix*** artInPieces;
  Day21Art();
  ~Day21Art();
  void splitArt();
  void applyRules();
  void assembleArt();
};


#endif // DAY21_H_INCLUDED
