#include "day23.h"

std::string day23(std::ifstream& file)
{
  int ans1 = 0;
  int ans2 = 0;
  std::string line;
  std::vector<Day23Operation> operations;
  Day23VariableVector variables;

  while(std::getline(file, line))
  {
    if(line.length() > 0)
    {
      Day23Operation op(line);
      operations.push_back(op);
    }
  }

  for(std::vector<Day23Operation>::iterator it1 = operations.begin(); it1 != operations.end(); ++it1)
  {
    if((int)(it1->arg1[0]) >= 97 && (int)(it1->arg1[0]) <= 122)
      variables.add(it1->arg1[0]);
    if((int)(it1->arg2[0]) >= 97 && (int)(it1->arg2[0]) <= 122)
      variables.add(it1->arg2[0]);
  }
  std::vector<Day23Operation>::iterator op = operations.begin();
  bool done = false;
  bool justJumped;
  while(!done)
  {
    justJumped = false;
    switch(op->operation)
    {
      case DAY23_SET:
      {
        variables.setVal(op->arg1, op->arg2);
        break;
      }
      case DAY23_SUB:
      {
        variables.setVal(op->arg1, variables.getVal(op->arg1) - variables.getVal(op->arg2));
        break;
      }
      case DAY23_MUL:
      {
        variables.setVal(op->arg1, variables.getVal(op->arg1) * variables.getVal(op->arg2));
        ans1++;
        break;
      }
      case DAY23_JNZ:
      {
        if(variables.getVal(op->arg1) != 0)
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

  int h=0;
  for(int b = 105700; b<122700+17; b+=17)
  {
    int f=1;
    for(int d=2; d*d<=b+1 && f==1; d++)
    {
      for(int e=d; e*d<=b+1 && f==1; e++)
      {
        if(b == e*d)
          f=0;
      }
    }
    if(f==0)
      h++;
  }

  ans2 = h;

  std::stringstream out;
  out << "Day 23\nPart 1: " << ans1 << "\nPart 2: " << ans2;
  return out.str();
}

Day23Operation::Day23Operation()
{
}

Day23Operation::Day23Operation(std::string input)
{
  load(input);
}

bool Day23Operation::load(std::string input)
{
  if(input.length() > 0)
  {
    std::stringstream ss(input);
    std::string word;
    ss >> word;
    if(word.compare("set") == 0)
      operation = DAY23_SET;
    if(word.compare("sub") == 0)
      operation = DAY23_SUB;
    if(word.compare("mul") == 0)
      operation = DAY23_MUL;
    if(word.compare("jnz") == 0)
      operation = DAY23_JNZ;
    ss >> arg1;
    ss >> arg2;
    return true;
  }
  else
    return false;
}

Day23Variable::Day23Variable()
{
}

Day23Variable::Day23Variable(char name, __int64 val)
{
  this->name = name;
  this->val = val;
}

void Day23VariableVector::add(char name)
{
  bool exist = false;
  for(std::vector<Day23Variable>::iterator it = variables.begin(); it != variables.end(); ++it)
  {
    if(name == it->name)
      exist = true;
  }
  if(!exist)
  {
    Day23Variable var(name, 0);
    variables.push_back(var);
  }
}

void Day23VariableVector::output()
{
  for(std::vector<Day23Variable>::iterator it = variables.begin(); it != variables.end(); ++it)
    std::cout << it->name << ":" << it->val << std::endl;
}

__int64 Day23VariableVector::getVal(std::string arg)
{
  if((int)(arg[0]) >= 97 && (int)(arg[0]) <= 122)
  {
    for(std::vector<Day23Variable>::iterator it = variables.begin(); it != variables.end(); ++it)
      if(it->name == arg[0])
        return it->val;
    return 0;
  }
  else
    return atoi(arg.c_str());
}

void Day23VariableVector::setVal(std::string name, std::string val)
{
  for(std::vector<Day23Variable>::iterator it = variables.begin(); it != variables.end(); ++it)
    if(it->name == name[0])
      it->val = getVal(val);
}

void Day23VariableVector::setVal(std::string name, __int64 val)
{
  for(std::vector<Day23Variable>::iterator it = variables.begin(); it != variables.end(); ++it)
    if(it->name == name[0])
      it->val = val;
}

void Day23VariableVector::copy(Day23VariableVector& other, int pVal)
{
  for(std::vector<Day23Variable>::iterator it = other.variables.begin(); it != other.variables.end(); ++it)
    this->add(it->name);
  this->setVal("p", pVal);
}
