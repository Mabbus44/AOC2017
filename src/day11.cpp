#include "day11.h"

std::string day11(std::ifstream& file)
{
  int ans1 = 0;
  int ans2 = 0;
  std::string line;
  std::getline(file, line);
  std::replace(line.begin(), line.end(), ',', ' ');
  std::stringstream ss(line);
  std::string dir;
  int x = 0;
  int y = 0;
  while (ss >> dir)
  {
    if(dir.compare("s") == 0)
      y-=2;
    if(dir.compare("se") == 0)
    {
      y--;
      x++;
    }
    if(dir.compare("ne") == 0)
    {
      y++;
      x++;
    }
    if(dir.compare("n") == 0)
      y+=2;
    if(dir.compare("nw") == 0)
    {
      y++;
      x--;
    }
    if(dir.compare("sw") == 0)
    {
      y--;
      x--;
    }
    int distX = std::abs(x);
    int distY = std::abs(y);
    int dist = distX;
    distY -= distX;
    if(distY>0)
      dist += distY/2;
    if(dist > ans2)
      ans2 = dist;
  }
  ans1 = std::abs(x);
  y = std::abs(y);
  y -= ans1;
  if(y>0)
    ans1 += y/2;
  std::stringstream out;
  out << "Day 11\nPart 1: " << ans1 << "\nPart 2: " << ans2;
  return out.str();
}
