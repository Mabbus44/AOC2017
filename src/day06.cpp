#include "day06.h"

std::string day06(std::ifstream& file)
{
  int ans1 = 0;
  int ans2 = 0;
  std::string line;
  std::getline(file, line);
  std::istringstream iss(line);
  std::vector<int> v;
  std::vector<std::vector<int>> oldVectors;
  do
  {
      std::string subs;
      iss >> subs;
      if(subs.length() > 0)
        v.push_back(atoi(subs.c_str()));
  } while (iss);
  int seqLength = v.size();
  int loopBackTo = 0;
  int vCount = 0;
  bool done = false;
  oldVectors.push_back(v);
  while(!done)
  {
    int vPos = 0;
    int vMax = 0;
    for(int i=0; i<seqLength; i++)
    {
      if(v[i]>vMax)
      {
        vPos = i;
        vMax = v[i];
      }
    }
    v[vPos] = 0;
    while(vMax>0)
    {
      vPos++;
      if(vPos>=seqLength)
        vPos = 0;
      v[vPos]++;
      vMax--;
    }
    for(std::vector<std::vector<int>>::iterator it=oldVectors.begin(); it!=oldVectors.end(); ++it)
    {
      bool identical = true;
      for(int i=0; i<seqLength && identical; i++)
        if(v[i] != (*it)[i])
          identical = false;
      if(identical)
      {
        done = true;
        loopBackTo = it - oldVectors.begin();
      }
    }
    oldVectors.push_back(v);
    vCount++;
  }
  ans1 = vCount;
  ans2 = vCount - loopBackTo;
  std::stringstream out;
  out << "Day 6\nPart 1: " << ans1 << "\nPart 2: " << ans2;
  return out.str();
}
