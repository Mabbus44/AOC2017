#include "day05.h"

std::string day05(std::ifstream& file)
{
  int ans1 = 0;
  int ans2 = 0;
  std::string line;
  int mazeLength = 0;
  std::list<int> mazeList;
  while(std::getline(file, line))
  {
    if(line.length()>0)
    {
      mazeList.push_back(atoi(line.c_str()));   //Becaure std::stoi() is bugged in mingw :(
      mazeLength++;
    }
  }
  int maze[mazeLength];
  int maze2[mazeLength];
  mazeLength = 0;
  for(std::list<int>::iterator it=mazeList.begin(); it!=mazeList.end(); ++it)
  {
    maze[mazeLength] = *it;
    maze2[mazeLength] = *it;
    mazeLength++;
  }
  int pos = 0;
  while(pos >= 0 && pos < mazeLength)
  {
    maze[pos]++;
    pos += maze[pos] - 1;
    ans1++;
  }
  pos = 0;
  while(pos >= 0 && pos < mazeLength)
  {
    int oldPos = pos;
    pos += maze2[pos];
    if(maze2[oldPos] >2)
      maze2[oldPos]--;
    else
      maze2[oldPos]++;
    ans2++;
  }
  std::stringstream out;
  out << "Day 5\nPart 1: " << ans1 << "\nPart 2: " << ans2;
  return out.str();
}
