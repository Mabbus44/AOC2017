#include "day19.h"

std::string day19(std::ifstream& file)
{
  std::string ans1;
  int ans2;
  std::string line;

  Day19Maze maze;
  while(std::getline(file, line))
  {
    if(line.length() > 0)
      maze.loadLine(line);
  }
  maze.calcSize();
  maze.findStart();
  ans1 = "";
  ans2 = 1;
  while(maze.step())
  {
    if((int)maze.maze[maze.posY][maze.posX] >= 65 && (int)maze.maze[maze.posY][maze.posX] <= 90)
      ans1 = ans1 + maze.maze[maze.posY][maze.posX];
    ans2++;
  }

  std::stringstream out;
  out << "Day 19\nPart 1: " << ans1 << "\nPart 2: " << ans2;
  return out.str();
}

void Day19Maze::loadLine(std::string line)
{
  std::vector<char> empty;
  maze.push_back(empty);
  std::vector<std::vector<char>>::iterator it = --maze.end();
  for(int i=0; i<(int)line.size(); i++)
    it->push_back(line[i]);
}

void Day19Maze::calcSize()
{
  sizeY = maze.size();
  sizeX = -1;
  for(std::vector<std::vector<char>>::iterator it = maze.begin(); it!=maze.end(); ++it)
  {
    if(sizeX == -1)
      sizeX = it->size();
    else
    {
      if(sizeX != (int)it->size())
        std::cout << "Varning (" << sizeX << "," << it->size() << std::endl;
    }
  }
}

void Day19Maze::findStart()
{
  posX = 0;
  posY = 0;
  lastPosY = -1;
  for(std::vector<char>::iterator it = maze.begin()->begin(); it!= maze.begin()->end() && *it==' '; ++it)
    posX++;
  lastPosX = posX;
}

bool Day19Maze::step()
{
  int dirX = posX-lastPosX;
  int dirY = posY-lastPosY;
  int nextX = posX + dirX;
  int nextY = posY + dirY;
  if(nextX >= 0 && nextX < sizeX && nextY >= 0 && nextY < sizeY && maze[nextY][nextX] != ' ')
  {
    lastPosX = posX;
    lastPosY = posY;
    posX = nextX;
    posY = nextY;
    return true;
  }
  std::swap(dirX, dirY);
  nextX = posX + dirX;
  nextY = posY + dirY;
  if(nextX >= 0 && nextX < sizeX && nextY >= 0 && nextY < sizeY && maze[nextY][nextX] != ' ')
  {
    lastPosX = posX;
    lastPosY = posY;
    posX = nextX;
    posY = nextY;
    return true;
  }
  dirX = -dirX;
  dirY = -dirY;
  nextX = posX + dirX;
  nextY = posY + dirY;
  if(nextX >= 0 && nextX < sizeX && nextY >= 0 && nextY < sizeY && maze[nextY][nextX] != ' ')
  {
    lastPosX = posX;
    lastPosY = posY;
    posX = nextX;
    posY = nextY;
    return true;
  }
  return false;
}
