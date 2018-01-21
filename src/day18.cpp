#include "day18.h"

std::string day18(std::ifstream& file)
{
  __int64 ans1;
  int ans2;
  std::string line;
  std::vector<Day18Operation> operations;
  Day18VariableVector variables;

  while(std::getline(file, line))
  {
    if(line.length() > 0)
    {
      Day18Operation op(line);
      operations.push_back(op);
    }
  }

  for(std::vector<Day18Operation>::iterator it1 = operations.begin(); it1 != operations.end(); ++it1)
  {
    if((int)(it1->arg1[0]) >= 97 && (int)(it1->arg1[0]) <= 122)
      variables.add(it1->arg1[0]);
    if(!(it1->operation == DAY18_SND || it1->operation == DAY18_RCV) && ((int)(it1->arg2[0]) >= 97 && (int)(it1->arg2[0]) <= 122))
      variables.add(it1->arg2[0]);
  }
  std::vector<Day18Operation>::iterator op = operations.begin();
  bool done = false;
  bool justJumped;
  __int64 lastPlayed = -1;
  while(!done)
  {
    justJumped = false;
    switch(op->operation)
    {
      case DAY18_SND:
      {
        lastPlayed = variables.getVal(op->arg1);
        break;
      }
      case DAY18_SET:
      {
        variables.setVal(op->arg1, op->arg2);
        break;
      }
      case DAY18_ADD:
      {
        variables.setVal(op->arg1, variables.getVal(op->arg1) + variables.getVal(op->arg2));
        break;
      }
      case DAY18_MUL:
      {
        variables.setVal(op->arg1, variables.getVal(op->arg1) * variables.getVal(op->arg2));
        break;
      }
      case DAY18_MOD:
      {
        variables.setVal(op->arg1, variables.getVal(op->arg1) % variables.getVal(op->arg2));
        break;
      }
      case DAY18_RCV:
      {
        if(variables.getVal(op->arg1) != 0)
        {
          variables.setVal(op->arg1, lastPlayed);
          ans1 = lastPlayed;
          done = true;
        }
        break;
      }
      case DAY18_JGZ:
      {
        if(variables.getVal(op->arg1) > 0)
        {
          int jump = variables.getVal(op->arg2);
          if(jump>0)
          {
            for(int i=0; !done && i<jump; i++)
            {
              op++;
              if(op == operations.end())
                done = true;
            }
            justJumped = true;
          }
          if(jump<0)
          {
            for(int i=0; !done && i>jump; i--)
            {
              op--;
              if(op == operations.begin() && jump < i-1)
                done = true;
            }
            justJumped = true;
          }
        }
        break;
      }
    }
    if(!justJumped)
      op++;
    if(op == operations.end())
      done = true;
  }
  Day18VariableVector v[2];
  std::list<__int64> send[2];
  v[0].copy(variables, 0);
  v[1].copy(variables, 1);
  std::vector<Day18Operation>::iterator op2[2];
  op2[0] = operations.begin();
  op2[1] = operations.begin();
  bool locked[2] = {false, false};
  bool terminated[2] = {false, false};
  bool step;
  done = false;
  int activeProgram = 0;
  bool debug = false;
  while(!done)
  {
    step = true;
    switch(op2[activeProgram]->operation)
    {
      case DAY18_SND:
      {
        send[activeProgram].push_back(v[activeProgram].getVal(op2[activeProgram]->arg1));
        if(activeProgram == 1)
          ans2++;
        if(debug)
          std::cout << activeProgram << " SND:" << op2[activeProgram]->arg1 << " (" << v[activeProgram].getVal(op2[activeProgram]->arg1) << ")" << std::endl;
        break;
      }
      case DAY18_SET:
      {
        if(debug)
          std::cout << activeProgram << " SET:" << op2[activeProgram]->arg1 << "," << op2[activeProgram]->arg2 <<  " (" << v[activeProgram].getVal(op2[activeProgram]->arg1) << "," << v[activeProgram].getVal(op2[activeProgram]->arg2) << ")" << std::endl;
        v[activeProgram].setVal(op2[activeProgram]->arg1, op2[activeProgram]->arg2);
        break;
      }
      case DAY18_ADD:
      {
        if(debug)
          std::cout << activeProgram << " ADD:" << op2[activeProgram]->arg1 << "," << op2[activeProgram]->arg2 <<  " (" << v[activeProgram].getVal(op2[activeProgram]->arg1) << "," << v[activeProgram].getVal(op2[activeProgram]->arg2) << ")" << std::endl;
        v[activeProgram].setVal(op2[activeProgram]->arg1, v[activeProgram].getVal(op2[activeProgram]->arg1) + v[activeProgram].getVal(op2[activeProgram]->arg2));
        break;
      }
      case DAY18_MUL:
      {
        if(debug)
          std::cout << activeProgram << " MUL:" << op2[activeProgram]->arg1 << "," << op2[activeProgram]->arg2 <<  " (" << v[activeProgram].getVal(op2[activeProgram]->arg1) << "," << v[activeProgram].getVal(op2[activeProgram]->arg2) << ")" << std::endl;
        v[activeProgram].setVal(op2[activeProgram]->arg1, v[activeProgram].getVal(op2[activeProgram]->arg1) * v[activeProgram].getVal(op2[activeProgram]->arg2));
        break;
      }
      case DAY18_MOD:
      {
        if(debug)
          std::cout << activeProgram << " MOD:" << op2[activeProgram]->arg1 << "," << op2[activeProgram]->arg2 <<  " (" << v[activeProgram].getVal(op2[activeProgram]->arg1) << "," << v[activeProgram].getVal(op2[activeProgram]->arg2) << ")" << std::endl;
        v[activeProgram].setVal(op2[activeProgram]->arg1, v[activeProgram].getVal(op2[activeProgram]->arg1) % v[activeProgram].getVal(op2[activeProgram]->arg2));
        break;
      }
      case DAY18_RCV:
      {
        if(send[1-activeProgram].size() == 0)
        {
          locked[activeProgram] = true;
          step = false;
          if(debug)
            std::cout << activeProgram << " RCV: EMPTY" << std::endl;
        }
        else
        {
          v[activeProgram].setVal(op2[activeProgram]->arg1, send[1-activeProgram].front());
          if(debug)
            std::cout << activeProgram << " RCV:" << op2[activeProgram]->arg1 << " (" << send[1-activeProgram].front() << ")" << std::endl;
          send[1-activeProgram].pop_front();
        }
        break;
      }
      case DAY18_JGZ:
      {
        if(debug)
          std::cout << activeProgram << " JGZ:" << op2[activeProgram]->arg1 << "," << op2[activeProgram]->arg2 <<  " (" << v[activeProgram].getVal(op2[activeProgram]->arg1) << "," << v[activeProgram].getVal(op2[activeProgram]->arg2) << ")" << std::endl;
        if(v[activeProgram].getVal(op2[activeProgram]->arg1) > 0)
        {
          int jump = v[activeProgram].getVal(op2[activeProgram]->arg2);
          if(jump>0)
          {
            for(int i=0; !terminated[activeProgram] && i<jump; i++)
            {
              op2[activeProgram]++;
              if(op2[activeProgram] == operations.end())
                terminated[activeProgram] = true;
            }
            step = false;
          }
          if(jump<0)
          {
            for(int i=0; !terminated[activeProgram] && i>jump; i--)
            {
              op2[activeProgram]--;
              if(op2[activeProgram] == operations.begin() && jump < i-1)
                terminated[activeProgram] = true;
            }
            step = false;
          }
        }
        break;
      }
    }
    if(!(terminated[activeProgram] || locked[activeProgram]))
      locked[1-activeProgram] = false;
    if(step)
      op2[activeProgram]++;
    if(op2[activeProgram] == operations.end())
      terminated[activeProgram] = true;
    if((terminated[0] || locked[0]) && (terminated[1] || locked[1]))
      done = true;
    if(terminated[activeProgram] || locked[activeProgram])
      activeProgram = 1- activeProgram;
  }

  std::stringstream out;
  out << "Day 18\nPart 1: " << ans1 << "\nPart 2: " << ans2;
  return out.str();
}

Day18Operation::Day18Operation()
{
}

Day18Operation::Day18Operation(std::string input)
{
  load(input);
}

bool Day18Operation::load(std::string input)
{
  if(input.length() > 0)
  {
    std::stringstream ss(input);
    std::string word;
    ss >> word;
    if(word.compare("snd") == 0)
      operation = DAY18_SND;
    if(word.compare("set") == 0)
      operation = DAY18_SET;
    if(word.compare("add") == 0)
      operation = DAY18_ADD;
    if(word.compare("mul") == 0)
      operation = DAY18_MUL;
    if(word.compare("mod") == 0)
      operation = DAY18_MOD;
    if(word.compare("rcv") == 0)
      operation = DAY18_RCV;
    if(word.compare("jgz") == 0)
      operation = DAY18_JGZ;
    ss >> arg1;
    if(operation == DAY18_SND || operation == DAY18_RCV)
      arg2 = "";
    else
      ss >> arg2;
    return true;
  }
  else
    return false;
}

Day18Variable::Day18Variable()
{
}

Day18Variable::Day18Variable(char name, __int64 val)
{
  this->name = name;
  this->val = val;
}

void Day18VariableVector::add(char name)
{
  bool exist = false;
  for(std::vector<Day18Variable>::iterator it = variables.begin(); it != variables.end(); ++it)
  {
    if(name == it->name)
      exist = true;
  }
  if(!exist)
  {
    Day18Variable var(name, 0);
    variables.push_back(var);
  }
}

void Day18VariableVector::output()
{
  for(std::vector<Day18Variable>::iterator it = variables.begin(); it != variables.end(); ++it)
    std::cout << it->name << ":" << it->val << std::endl;
}

__int64 Day18VariableVector::getVal(std::string arg)
{
  if((int)(arg[0]) >= 97 && (int)(arg[0]) <= 122)
  {
    for(std::vector<Day18Variable>::iterator it = variables.begin(); it != variables.end(); ++it)
      if(it->name == arg[0])
        return it->val;
    return 0;
  }
  else
    return atoi(arg.c_str());
}

void Day18VariableVector::setVal(std::string name, std::string val)
{
  for(std::vector<Day18Variable>::iterator it = variables.begin(); it != variables.end(); ++it)
    if(it->name == name[0])
      it->val = getVal(val);
}

void Day18VariableVector::setVal(std::string name, __int64 val)
{
  for(std::vector<Day18Variable>::iterator it = variables.begin(); it != variables.end(); ++it)
    if(it->name == name[0])
      it->val = val;
}

void Day18VariableVector::copy(Day18VariableVector& other, int pVal)
{
  for(std::vector<Day18Variable>::iterator it = other.variables.begin(); it != other.variables.end(); ++it)
    this->add(it->name);
  this->setVal("p", pVal);
}
