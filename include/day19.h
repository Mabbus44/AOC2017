#ifndef DAY19_H_INCLUDED
#define DAY19_H_INCLUDED

#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <vector>

std::string day19(std::ifstream& file);

class Day19Maze
{
  public:
  int sizeX, sizeY;
  int posX, posY;
  int lastPosX, lastPosY;
  std::vector<std::vector<char>> maze;
  void loadLine(std::string line);
  void calcSize();
  void findStart();
  bool step();
};

#endif // DAY19_H_INCLUDED
