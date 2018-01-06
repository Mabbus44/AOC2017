#include "day13.h"
#include <iostream>

std::string day13(std::ifstream& file)
{
  int ans1 = 0;
  int ans2 = 0;
  std::string line;
  std::vector<Day13Wall> walls;
  int maxDepth = -1;
  while(std::getline(file, line))
  {
    if(line.length() > 0)
    {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::stringstream ss(line);
      int inputSequence = 0;
      int num;
      while(ss >> num)
      {
        if(inputSequence == 0)
        {
          Day13Wall newWall;
          walls.push_back(newWall);
          walls[walls.size() - 1].depth = num;
          if(num > maxDepth)
            maxDepth = num;
        }
        if(inputSequence == 1)
          walls[walls.size() - 1].range = num;
        inputSequence++;
      }
    }
  }
  int depth = -1;
  int severity = 0;
  while(depth < maxDepth)
  {
    depth++;
    for(int i=0; i < int(walls.size()); i++)
    {
      if(walls[i].depth == depth && walls[i].pos == 0)
        severity += walls[i].depth*walls[i].range;
      walls[i].move();
    }
  }
  ans1 = severity;
  int delay = -1;
  bool caught = true;
  while(caught)
  {
    caught = false;
    delay++;
    for(int i=0; !caught && i<int(walls.size()); i++)
    {
        int time = delay + walls[i].depth;
        int positions = (walls[i].range - 2) * 2 + 2;
        if(time%positions == 0)
          caught = true;
    }
  }
  /*while(caught)
  {
    caught = false;
    depth = -1;
    delay++;
    for(int i=0; i<int(walls.size()); i++)
      walls[i].pos = 0;
    for(int i=0; i<delay; i++)
      for(int i2=0; i2<int(walls.size()); i2++)
        walls[i2].move();
//    std::cout << std::endl << "Delay: " << delay << std::endl;
    while(depth < maxDepth && !caught)
    {
      depth++;
//      std::cout << "Pos: " << depth  << std::endl;
      for(int i=0; i<int(walls.size())  && !caught; i++)
      {
        if(walls[i].depth == depth && walls[i].pos == 0)
        {
          caught = true;
//          std::cout << "*";
        }
//        std::cout << walls[i].depth << ":" << walls[i].pos << "  ";
        walls[i].move();
      }
      //std::cout << std::endl;
      //if(caught)
//        std::cout << "caught!!!!" << std::endl;
    }
    std::cout << delay << std::endl;
  }*/
  ans2 = delay;
  std::stringstream out;
  out << "Day 13\nPart 1: " << ans1 << "\nPart 2: " << ans2;
  return out.str();
}

Day13Wall::Day13Wall()
{
  pos = 0;
  dir = true;
}

void Day13Wall::move()
{
  if(range == 1)
    pos = 0;
  else
  {
    if(dir)
      pos++;
    else
      pos--;
    if(pos<0)
    {
      pos = 1;
      dir = true;
    }
    if(pos >= range)
    {
      pos = range - 2;
      dir = false;
    }
  }
}
