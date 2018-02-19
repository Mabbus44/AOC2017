#include "day24.h"

std::string day24(std::ifstream& file)
{
  int ans1, ans2;
  std::string line;
  Day24Bridge bridge;
  while(std::getline(file, line))
  {
    if(line.length() > 0)
    {
      bridge.loadPart(line);
    }
  }
  std::vector<int> emptyVector, emptyVector2;
  ans1 = bridge.strongest(emptyVector, 0);
  int strength = 0;
  int length = 0;
  bridge.longest(emptyVector2, 0, length, strength);
  ans2 = strength;
  std::stringstream out;
  out << "Day 24\nPart 1: " << ans1 << "\nPart 2: " << ans2;
  return out.str();
}

void Day24Bridge::loadPart(std::string line)
{
  Day24Part part;
  int dividePos = line.find('/');
  part.sides[0] = atoi(line.substr(0,dividePos).c_str());
  part.sides[1] = atoi(line.substr(dividePos+1, line.length()-dividePos-1).c_str());
  parts.push_back(part);
}

int Day24Bridge::strongest(std::vector<int> usedParts, int conStr)
{
  bool fit;
  int maxStr = 0;
  for(int i=0; i<(int)(parts.size()); i++)
  {
    if(parts[i].sides[0] == conStr || parts[i].sides[1] == conStr)
      fit = true;
    else
      fit = false;
    for(int i2=0; i2<(int)(usedParts.size()) && fit; i2++)
    {
      if(i==usedParts[i2])
        fit = false;
    }
    if(fit)
    {
      std::vector<int> newUsedParts = usedParts;
      int newConStr;
      newUsedParts.push_back(i);
      if(parts[i].sides[0] == conStr)
        newConStr = parts[i].sides[1];
      else
        newConStr = parts[i].sides[0];
      int str = strongest(newUsedParts, newConStr);
      if(str>maxStr)
        maxStr = str;
    }
  }
  if(usedParts.size()>0)
    maxStr = maxStr + parts[usedParts[usedParts.size()-1]].sides[0] + parts[usedParts[usedParts.size()-1]].sides[1];
  return maxStr;
}

void Day24Bridge::longest(std::vector<int> usedParts, int conStr, int& length, int& strength)
{
  bool fit;
  for(int i=0; i<(int)(parts.size()); i++)
  {
    if(parts[i].sides[0] == conStr || parts[i].sides[1] == conStr)
      fit = true;
    else
      fit = false;
    for(int i2=0; i2<(int)(usedParts.size()) && fit; i2++)
    {
      if(i==usedParts[i2])
        fit = false;
    }
    if(fit)
    {
      std::vector<int> newUsedParts = usedParts;
      int newConStr;
      newUsedParts.push_back(i);
      if(parts[i].sides[0] == conStr)
        newConStr = parts[i].sides[1];
      else
        newConStr = parts[i].sides[0];
      longest(newUsedParts, newConStr, length, strength);
    }
  }
  if((int)(usedParts.size())>=length)
  {
    int thisStrength = 0;
    for(int i=0; i<(int)(usedParts.size()); i++)
      thisStrength += (parts[usedParts[i]].sides[0] + parts[usedParts[i]].sides[1]);
    if((int)(usedParts.size())>length || ((int)(usedParts.size()) == length && thisStrength>strength))
    {
      length = (int)(usedParts.size());
      strength = thisStrength;
    }
  }
}
