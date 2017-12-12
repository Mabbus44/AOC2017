#include "day08.h"

std::string day08(std::ifstream& file)
{
  int ans1 = 0;
  int ans2 = 0;
  std::string line;
  std::list<Day8Variable> vars;
  while(std::getline(file, line))
  {
    if(line.length() > 0)
    {
      std::istringstream iss(line);
      std::list<Day8Variable>::iterator opVar;
      std::string operation;
      int opValue;
      std::list<Day8Variable>::iterator coVar;
      std::string condition;
      int coValue;
      int inputSequence = 0;
      do
      {
        std::string subs;
        iss >> subs;
        switch(inputSequence)
        {
          case 0:
          {
            std::list<Day8Variable>::iterator findVar = std::find(vars.begin(), vars.end(), subs);
            if(findVar == vars.end())
            {
              Day8Variable temp(subs, 0);
              vars.push_front(temp);
              opVar = vars.begin();
            }
            else
              opVar = findVar;
            break;
          }
          case 1:
          {
            operation = subs;
            break;
          }
          case 2:
          {
            opValue = atoi(subs.c_str());
            break;
          }
          case 3:
          {
            break;
          }
          case 4:
          {
            std::list<Day8Variable>::iterator findVar = std::find(vars.begin(), vars.end(), subs);
            if(findVar == vars.end())
            {
              Day8Variable temp(subs, 0);
              vars.push_front(temp);
              coVar = vars.begin();
            }
            else
              coVar = findVar;
            break;
          }
          case 5:
          {
            condition = subs;
            break;
          }
          case 6:
          {
            coValue = atoi(subs.c_str());
            break;
          }

        }
        inputSequence++;
      } while (iss);
      bool changeVal = false;
      if(condition.compare(">=") == 0 && (*coVar).val >= coValue)
        changeVal = true;
      if(condition.compare("<=") == 0 && (*coVar).val <= coValue)
        changeVal = true;
      if(condition.compare(">") == 0 && (*coVar).val > coValue)
        changeVal = true;
      if(condition.compare("<") == 0 && (*coVar).val < coValue)
        changeVal = true;
      if(condition.compare("==") == 0 && (*coVar).val == coValue)
        changeVal = true;
      if(condition.compare("!=") == 0 && (*coVar).val != coValue)
        changeVal = true;
      if(changeVal)
      {
        if(operation.compare("inc") == 0)
        {
          (*opVar).val += opValue;
          if((*opVar).val >ans2)
            ans2= (*opVar).val;
        }
        if(operation.compare("dec") == 0)
        {
          (*opVar).val -= opValue;
          if((*opVar).val >ans2)
            ans2= (*opVar).val;
        }
      }
    }
  }
  for(std::list<Day8Variable>::iterator it1 = vars.begin(); it1 != vars.end(); ++it1)
    if((*it1).val > ans1)
      ans1 = (*it1).val;
  std::stringstream out;
  out << "Day 8\nPart 1: " << ans1 << "\nPart 2: " << ans2;
  return out.str();
}

Day8Variable::Day8Variable(std::string name, int val)
{
  this->name = name;
  this->val = val;
}

Day8Variable::operator==(std::string other)
{
  if(this->name.compare(other) == 0)
    return true;
  return false;
}
