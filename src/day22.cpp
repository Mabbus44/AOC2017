#include "day22.h"

std::string day22(std::ifstream& file)
{
  int ans1=0, ans2=0;
  std::string line;
  Day22Matrix matrix, matrix2;
  while(std::getline(file, line))
  {
    if(line.length() > 0)
    {
      matrix.loadRow(line);
      matrix2.loadRow(line);
    }
  }
  matrix.virus.pos = matrix.getMiddleNode();
  matrix2.virus.pos = matrix2.getMiddleNode();
  for(int i=0; i<10000; i++)
  {
    if(matrix.moveVirus())
      ans1++;
  }
  for(int i=0; i<10000000; i++)
  {
    if(matrix2.moveVirus2())
      ans2++;
  }
  std::stringstream out;
  out << "Day 22\nPart 1: " << ans1 << "\nPart 2: " << ans2;
  return out.str();
}

void Day22Node::expand(int dir)
{
  int dirStart;
  int dirGo;
  int dirOpp;
  if(dir == DAY22_LEFT)
  {
    dirStart = DAY22_UP;
    dirGo = DAY22_DOWN;
    dirOpp = DAY22_RIGHT;
  }
  if(dir == DAY22_RIGHT)
  {
    dirStart = DAY22_UP;
    dirGo = DAY22_DOWN;
    dirOpp = DAY22_LEFT;
  }
  if(dir == DAY22_UP)
  {
    dirStart = DAY22_LEFT;
    dirGo = DAY22_RIGHT;
    dirOpp = DAY22_DOWN;
  }
  if(dir == DAY22_DOWN)
  {
    dirStart = DAY22_LEFT;
    dirGo = DAY22_RIGHT;
    dirOpp = DAY22_UP;
  }
  Day22Node* existingNode;
  Day22Node* newNode;
  Day22Node* oldNewNode;

  existingNode = this->getEdge(dir)->getEdge(dirStart);
  newNode = new Day22Node;

  existingNode->setNextRaw(dir, newNode);
  newNode->setNextRaw(dirOpp, existingNode);

  while(existingNode->getNextRaw(dirGo))
  {
    oldNewNode = newNode;
    existingNode = existingNode->getNextRaw(dirGo);
    newNode = new Day22Node;
    existingNode->setNextRaw(dir, newNode);
    newNode->setNextRaw(dirOpp, existingNode);
    newNode->setNextRaw(dirStart, oldNewNode);
    oldNewNode->setNextRaw(dirGo, newNode);
  }
}

Day22Node* Day22Node::getNext(int dir)
{
  if(next[dir])
    return next[dir];
  else
  {
    expand(dir);
    return next[dir];
  }
}

Day22Node* Day22Node::getNextRaw(int dir)
{
  return next[dir];
}

Day22Node* Day22Node::getEdge(int dir)
{
  if(next[dir])
    return next[dir]->getEdge(dir);
  else
    return this;
}

void Day22Node::setNextRaw(int dir, Day22Node* addr)
{
  next[dir] = addr;
}

void Day22Node::printRow()
{
  if(val == DAY22_CLEAN)
    std::cout << ".";
  else if(val == DAY22_WEAKEND)
    std::cout << "W";
  else if(val == DAY22_INFECTED)
    std::cout << "#";
  else if(val == DAY22_FLAGGED)
    std::cout << "F";
  else
    std::cout << "0";
  if(next[DAY22_RIGHT])
    next[DAY22_RIGHT]->printRow();
}

Day22Node::Day22Node()
{
  val = DAY22_CLEAN;
  next[DAY22_DOWN] = NULL;
  next[DAY22_UP] = NULL;
  next[DAY22_LEFT] = NULL;
  next[DAY22_RIGHT] = NULL;
}

Day22Node::~Day22Node()
{
}

Day22Node* Day22Matrix::getMiddleNode()
{
  Day22Node* middleNode = matrix->getEdge(DAY22_LEFT)->getEdge(DAY22_UP);
  int x = 1;
  int y = 1;
  while(middleNode->getNextRaw(DAY22_RIGHT))
  {
    x++;
    middleNode = middleNode->getNextRaw(DAY22_RIGHT);
  }
  while(middleNode->getNextRaw(DAY22_DOWN))
  {
    y++;
    middleNode = middleNode->getNextRaw(DAY22_DOWN);
  }
  x = (x+1)/2;
  y = (y+1)/2;
  while(x>1)
  {
    x--;
    middleNode = middleNode->getNextRaw(DAY22_LEFT);
  }
  while(y>1)
  {
    y--;
    middleNode = middleNode->getNextRaw(DAY22_UP);
  }
  return middleNode;
}

void Day22Matrix::loadRow(std::string line)
{
  std::stringstream ssLine(line);
  char bit;
  int val;
  bool first = true;
  bool goDown = true;
  Day22Node* node;
  if(!matrix)
  {
    matrix = new Day22Node;
    node = matrix;
    goDown = false;
  }
  else
    node = matrix->getEdge(DAY22_LEFT)->getEdge(DAY22_DOWN);
  while(ssLine >> bit)
  {
    if(bit == '#')
      val = DAY22_INFECTED;
    else if(bit == '.')
      val = DAY22_CLEAN;
    else
      val = -1;
    if(val >= 0)
    {
      if(!first)
        node = node->getNext(DAY22_RIGHT);
      if(goDown)
        node = node->getNext(DAY22_DOWN);
      node->val = val;
      first = false;
      goDown = false;
    }
  }
  if(first && !goDown)
    delete matrix;
}

void Day22Matrix::print()
{
  Day22Node* leftColumn = matrix->getEdge(DAY22_LEFT)->getEdge(DAY22_UP);
  while(leftColumn)
  {
    leftColumn->printRow();
    leftColumn = leftColumn->getNextRaw(DAY22_DOWN);
    if(leftColumn)
      std::cout << std::endl;
  }
}

bool Day22Matrix::moveVirus()
{
  bool ret;
  if(virus.pos->val)
  {
    if(virus.dir == DAY22_UP)
      virus.dir = DAY22_RIGHT;
    else if(virus.dir == DAY22_RIGHT)
      virus.dir = DAY22_DOWN;
    else if(virus.dir == DAY22_DOWN)
      virus.dir = DAY22_LEFT;
    else if(virus.dir == DAY22_LEFT)
      virus.dir = DAY22_UP;
  }
  else
  {
    if(virus.dir == DAY22_UP)
      virus.dir = DAY22_LEFT;
    else if(virus.dir == DAY22_LEFT)
      virus.dir = DAY22_DOWN;
    else if(virus.dir == DAY22_DOWN)
      virus.dir = DAY22_RIGHT;
    else if(virus.dir == DAY22_RIGHT)
      virus.dir = DAY22_UP;
  }
  if(virus.pos->val == DAY22_CLEAN)
  {
    virus.pos->val = DAY22_INFECTED;
    ret = true;
  }
  else
  {
    virus.pos->val = DAY22_CLEAN;
    ret = false;
  }
  virus.pos = virus.pos->getNext(virus.dir);
  return ret;
}

bool Day22Matrix::moveVirus2()
{
  bool ret;
  if(virus.pos->val == DAY22_CLEAN)
  {
    if(virus.dir == DAY22_UP)
      virus.dir = DAY22_LEFT;
    else if(virus.dir == DAY22_LEFT)
      virus.dir = DAY22_DOWN;
    else if(virus.dir == DAY22_DOWN)
      virus.dir = DAY22_RIGHT;
    else if(virus.dir == DAY22_RIGHT)
      virus.dir = DAY22_UP;
  }
  else if(virus.pos->val == DAY22_WEAKEND)
  {}
  else if(virus.pos->val == DAY22_INFECTED)
  {
    if(virus.dir == DAY22_UP)
      virus.dir = DAY22_RIGHT;
    else if(virus.dir == DAY22_RIGHT)
      virus.dir = DAY22_DOWN;
    else if(virus.dir == DAY22_DOWN)
      virus.dir = DAY22_LEFT;
    else if(virus.dir == DAY22_LEFT)
      virus.dir = DAY22_UP;
  }
  else if(virus.pos->val == DAY22_FLAGGED)
  {
    if(virus.dir == DAY22_UP)
      virus.dir = DAY22_DOWN;
    else if(virus.dir == DAY22_RIGHT)
      virus.dir = DAY22_LEFT;
    else if(virus.dir == DAY22_DOWN)
      virus.dir = DAY22_UP;
    else if(virus.dir == DAY22_LEFT)
      virus.dir = DAY22_RIGHT;
  }
  ret = false;
  if(virus.pos->val == DAY22_CLEAN)
    virus.pos->val = DAY22_WEAKEND;
  else if(virus.pos->val == DAY22_WEAKEND)
  {
    virus.pos->val = DAY22_INFECTED;
    ret = true;
  }
  else if(virus.pos->val == DAY22_INFECTED)
    virus.pos->val = DAY22_FLAGGED;
  else if(virus.pos->val == DAY22_FLAGGED)
    virus.pos->val = DAY22_CLEAN;
  virus.pos = virus.pos->getNext(virus.dir);
  return ret;
}

Day22Matrix::Day22Matrix()
{
  matrix = NULL;
  virus.pos = NULL;
  virus.dir = DAY22_UP;
}

Day22Matrix::~Day22Matrix()
{
  if(matrix)
  {
    Day22Node* thisNode = matrix->getEdge(DAY22_LEFT)->getEdge(DAY22_UP);
    Day22Node* nextNode = matrix->getNextRaw(DAY22_RIGHT);
    Day22Node* nextRow = matrix->getNextRaw(DAY22_DOWN);
    while(thisNode)
    {
      while(thisNode)
      {
        delete thisNode;
        thisNode = nextNode;
        if(nextNode)
          nextNode = nextNode->getNextRaw(DAY22_RIGHT);
      }
      thisNode = nextRow;
      if(thisNode)
        nextRow = nextRow->getNextRaw(DAY22_DOWN);
    }
  }
}
