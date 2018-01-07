#include "day17.h"

std::string day17(std::string input)
{
  int ans1, ans2;
  int steps = atoi(input.c_str());
  int pos = 0;
  Day17Buffer buff;
  for(int i=1; i<2018; i++)
  {
    pos += steps;
    pos = pos%i + 1;
    buff.stepForward(steps);
    buff.insertNumber(i);
  }
  ans1 = buff.getNext();
  for(int i=2018; i<50000001; i++)
  {
    pos += steps;
    pos = pos%i + 1;
    if(pos == 1)
      ans2 = i;
  }
  std::stringstream out;
  out << "Day 17\nPart 1: " << ans1 << "\nPart 2: " << ans2;
  return out.str();
}

Day17Buffer::Day17Buffer()
{
  this->buffer.push_back(0);
  pos = buffer.begin();
}

void Day17Buffer::stepForward(int steps)
{
  for(int i=0; i<steps; i++)
  {
    pos++;
    if(pos == this->buffer.end())
      pos = this->buffer.begin();
  }
}

void Day17Buffer::insertNumber(int num)
{
  pos++;
  if(pos == buffer.end())
    buffer.push_back(num);
  else
    buffer.insert(pos, num);
  pos--;
}

int Day17Buffer::getNext()
{
  std::list<int>::iterator nextPos = pos;
  nextPos++;
  if(nextPos == buffer.end())
    nextPos = buffer.begin();
  return *nextPos;
}

int Day17Buffer::getAfter0()
{
  std::list<int>::iterator it = this->buffer.begin();
  while(*it != 0)
    it++;
  it++;
  if(it == this->buffer.end())
    it = this->buffer.begin();
  return *it;
}

void Day17Buffer::output()
{
  std::list<int>::iterator it;
  for(it = buffer.begin(); it != buffer.end(); ++it)
    std::cout << *it <<",";
  std::cout << std::endl;
}
