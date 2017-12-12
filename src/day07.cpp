#include "day07.h"

std::string day07(std::ifstream& file)
{
  std::string strAns1;
  int ans2 = 0;
  std::string line;
  std::vector<Day7Program*> allPrograms;
  Day7Program* base;
  while(std::getline(file, line))
  {
    if(line.length() > 0)
    {
      std::istringstream iss(line);
      int inputSequence = 0;
      Day7Program* p = new Day7Program();
      do
      {
          std::string subs;
          iss >> subs;
          if(subs.length() > 0)
          {
            switch(inputSequence)
            {
              case 0:
              {
                p->name = subs;
                break;
              }
              case 1:
              {
                p->weight = atoi(subs.substr(1, subs.length()-2).c_str());
                break;
              }
              case 2:
                break;
              default:
              {
                if(subs.substr(subs.length()-1, 1).compare(",") == 0)
                  p->children.push_back(new Day7Program(subs.substr(0, subs.length()-1), 0));
                else
                  p->children.push_back(new Day7Program(subs, 0));
                break;
              }
            }
            inputSequence++;
          }
      } while (iss);
      if(p->name.length() > 0)
        allPrograms.push_back(p);
    }
  }
  base = *(allPrograms.begin());
  bool baseFound = false;
  while(!baseFound)
  {
    baseFound = true;
    for(std::vector<Day7Program*>::iterator it1=allPrograms.begin(); it1!=allPrograms.end() && baseFound; ++it1)
    {
      for(std::vector<Day7Program*>::iterator it2=(*it1)->children.begin(); it2!=(*it1)->children.end() && baseFound; ++it2)
      {
        if(base->name.compare((*it2)->name) == 0)
        {
           base = (*it1);
           baseFound=false;
        }
      }
    }
  }
  strAns1 = base->name;
  base->searchForChildren(allPrograms);
  Day7Program* p = NULL;
  ans2 = -base->getTrueWeight(p);
  std::stringstream out;
  out << "Day 7\nPart 1: " << strAns1 << "\nPart 2: " << ans2;
  return out.str();
}

Day7Program::Day7Program()
{
  name = "";
  weight = 0;
}


Day7Program::Day7Program(std::string name, int weight)
{
  this->name = name;
  this->weight = weight;
}

void Day7Program::searchForChildren(std::vector<Day7Program*> &programList)
{
  for(std::vector<Day7Program*>::iterator it1=this->children.begin(); it1!=this->children.end(); ++it1)
  {
    for(std::vector<Day7Program*>::iterator it2=programList.begin(); it2!=programList.end(); ++it2)
    {
      if((*it1)->name.compare((*it2)->name) == 0)
      {
        delete (*it1);
        (*it1) = (*it2);
      }
    }
    (*it1)->searchForChildren(programList);
  }
}

int Day7Program::getTrueWeight(Day7Program* &wrongProgram)
{
  int weight = 0;
  int oldWeight = 0;
  int totWeight = 0;
  int min = -1;
  int max = -1;
  bool childIsWrong = false;
  bool wrongProgramAlreadyFound = false;
  bool grandchildIsWrong = false;

  if(wrongProgram != NULL)
    wrongProgramAlreadyFound = true;
  for(std::vector<Day7Program*>::iterator it1=this->children.begin(); it1!=this->children.end(); ++it1)
  {
    oldWeight = weight;
    weight = (*it1)->getTrueWeight(wrongProgram);
    if(weight < 0)
      return weight;
    totWeight += weight;
    if(oldWeight != 0 && oldWeight != weight)
      childIsWrong = true;
    if(weight < min || min == -1)
      min = weight;
    if(weight > max)
      max = weight;
  }
  if(wrongProgram != NULL && !wrongProgramAlreadyFound)
    grandchildIsWrong = true;
  if(grandchildIsWrong)
  {
    for(std::vector<Day7Program*>::iterator it1=this->children.begin(); it1!=this->children.end(); ++it1)
    {
      if(wrongProgram == *it1)
      {
        if((*it1)->trueWeight > min)
          return wrongProgram->getMissingWeight(true);
        else
          return wrongProgram->getMissingWeight(false);
      }
    }
  }
  if(childIsWrong)
    wrongProgram = this;
  trueWeight = totWeight + this->weight;
  return trueWeight;
}

int Day7Program::getMissingWeight(bool toBig)
{
  int min = -1;
  int max = -1;
  int weight = 0;
  for(std::vector<Day7Program*>::iterator it1=this->children.begin(); it1!=this->children.end(); ++it1)
  {
    weight = (*it1)->trueWeight;
    if(weight < min || min == -1)
      min = weight;
    if(weight > max)
      max = weight;
  }
  for(std::vector<Day7Program*>::iterator it1=this->children.begin(); it1!=this->children.end(); ++it1)
  {
    if((*it1)->trueWeight > min && toBig)
      return -((*it1)->weight - (max - min));
    if((*it1)->trueWeight < max && !toBig)
      return -((*it1)->weight + (max - min));
  }
  return 0;   //should never happend
}
