#include "day09.h"

std::string day09(std::ifstream& file)
{
  int ans1 = 0;
  int ans2 = 0;
  std::string line;
  std::getline(file, line);
  int score = 0;
  int totalScore = 0;
  int garbageCount = 0;
  bool garbage = false;
  bool ignoreNext = false;
  for(unsigned int i = 0; i < line.size(); ++i)
  {
    if(ignoreNext)
      ignoreNext = false;
    else
    {
      if(!garbage && line[i] == '{')
      {
        score++;
        totalScore += score;
      }
      if(!garbage && line[i] == '}')
        score--;
      if(line[i] == '!')
        ignoreNext = true;
      if(line[i] == '>')
        garbage = false;
      if(garbage && !ignoreNext)
        garbageCount++;
      if(line[i] == '<')
        garbage = true;
    }
  }
  ans1 = totalScore;
  ans2 = garbageCount;
  std::stringstream out;
  out << "Day 9\nPart 1: " << ans1 << "\nPart 2: " << ans2;
  return out.str();
}
