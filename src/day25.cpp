#include "day25.h"

std::string day25(std::ifstream& file)
{
  int ans1;
  std::string ans2 = "FREE";
  Day25Tape tape;
  tape.list.loadInstructions(file);
  //tape.list.print();
  for(int i=0; i<tape.list.stepGoal; i++)
    tape.performInstruction();
  ans1 = tape.tape->checksum();
  std::stringstream out;
  out << "Day 25\nPart 1: " << ans1 << "\nPart 2: " << ans2;
  return out.str();
}

void Day25Node::expand(int dir)
{
  int dirOpp;
  if(dir == DAY25_LEFT)
    dirOpp = DAY25_RIGHT;
  if(dir == DAY25_RIGHT)
    dirOpp = DAY25_LEFT;

  Day25Node* existingNode;
  Day25Node* newNode;

  existingNode = this->getEdge(dir);
  newNode = new Day25Node;

  existingNode->setNextRaw(dir, newNode);
  newNode->setNextRaw(dirOpp, existingNode);
}

Day25Node* Day25Node::getNext(int dir)
{
  if(next[dir])
    return next[dir];
  else
  {
    expand(dir);
    return next[dir];
  }
}

Day25Node* Day25Node::getNextRaw(int dir)
{
  return next[dir];
}

Day25Node* Day25Node::getEdge(int dir)
{
  if(next[dir])
    return next[dir]->getEdge(dir);
  else
    return this;
}

void Day25Node::setNextRaw(int dir, Day25Node* addr)
{
  next[dir] = addr;
}

Day25Node::Day25Node()
{
  val = 0;
  next[DAY25_LEFT] = NULL;
  next[DAY25_RIGHT] = NULL;
}

int Day25Node::checksum()
{
  int checksum=0;
  Day25Node* node = getEdge(DAY25_LEFT);
  while(node)
  {
    checksum += node->val;
    node = node->getNextRaw(DAY25_RIGHT);
  }
  return checksum;
}

Day25Node::~Day25Node()
{
}

Day25Tape::Day25Tape()
{
  tape = new Day25Node;
  state = '0';
}

Day25Tape::~Day25Tape()
{
  Day25Node* eraser = tape->getEdge(DAY25_LEFT);
  while(eraser->getNextRaw(DAY25_RIGHT))
  {
    eraser = eraser->getNextRaw(DAY25_RIGHT);
    delete eraser->getNextRaw(DAY25_LEFT);
  }
  delete eraser;
}

void Day25Tape::performInstruction()
{
  if(state == '0')
    state = list.beginState;
  int ruleNr;
  for(int i=0; i<(int)(list.instructions.size()); i++)
    if(list.instructions[i].state == state)
      ruleNr = i;
  if(ruleNr >= (int)(list.instructions.size()) || ruleNr < 0)
  {
    std::cout << "Error, state matches no instruction" << std::endl;
    return;
  }
  int oldVal = tape->val;
  tape->val = list.instructions[ruleNr].writeValue[oldVal];
  tape = tape->getNext(list.instructions[ruleNr].moveDirection[oldVal]);
  state = list.instructions[ruleNr].nextState[oldVal];
}

void Day25InstructionList::loadInstructions(std::ifstream& file)
{
  std::string line;
  int loadState = 0;
  Day25Instruction newInstruction;
  while(std::getline(file, line))
  {
    if(line.length() > 0)
    {
      switch(loadState)
      {
      case 0:
        {
          int charPos = line.find("state") + 6;
          if(charPos-6>0)
          {
            beginState = line[charPos];
            loadState++;
          }
          break;
        }
      case 1:
        {
          int charPos = line.find("after") + 6;
          int charPos2 = line.find("steps") - 1;
          if(charPos-6>0 && charPos2+1>0)
          {
            stepGoal = atoi(line.substr(charPos, charPos2-charPos).c_str());
            loadState++;
          }
          break;
        }
      case 2:
        {
          int charPos = line.find("state") + 6;
          if(charPos-6>0)
          {
            newInstruction.state = line[charPos];
            loadState++;
          }
          break;
        }
      case 3:
        {
          int charPos = line.find("the value") + 10;
          if(charPos-10>0)
          {
            newInstruction.writeValue[0] = line[charPos] == '1';
            loadState++;
          }
          break;
        }
      case 4:
        {
          int charPos = line.find("the") + 4;
          if(charPos-4>0)
          {
            if(line.substr(charPos, 4) == "left")
              newInstruction.moveDirection[0] = DAY25_LEFT;
            else
              newInstruction.moveDirection[0] = DAY25_RIGHT;
            loadState++;
          }
          break;
        }
      case 5:
        {
          int charPos = line.find("state") + 6;
          if(charPos-6>0)
          {
            newInstruction.nextState[0] = line[charPos];
            loadState++;
          }
          break;
        }
      case 6:
        {
          int charPos = line.find("the value") + 10;
          if(charPos-10>0)
          {
            newInstruction.writeValue[1] = line[charPos] == '1';
            loadState++;
          }
          break;
        }
      case 7:
        {
          int charPos = line.find("the") + 4;
          if(charPos-4>0)
          {
            if(line.substr(charPos, 4) == "left")
              newInstruction.moveDirection[1] = DAY25_LEFT;
            else
              newInstruction.moveDirection[1] = DAY25_RIGHT;
            loadState++;
          }
          break;
        }
      case 8:
        {
          int charPos = line.find("state") + 6;
          if(charPos-6>0)
          {
            newInstruction.nextState[1] = line[charPos];
            loadState=2;
            instructions.push_back(newInstruction);
          }
          break;
        }
      }
    }
  }
}

void Day25InstructionList::print()
{
  for(int i=0; i<(int)(instructions.size()); i++)
  {
    std::cout << "Instruction " << i << ":" << std::endl;
    std::cout << "State: " << instructions[i].state << std::endl;
    std::cout << "0: " << instructions[i].writeValue[0] << " " << instructions[i].moveDirection[0] << " " << instructions[i].nextState[0] << std::endl;
    std::cout << "1: " << instructions[i].writeValue[1] << " " << instructions[i].moveDirection[1] << " " << instructions[i].nextState[1] << std::endl;
  }
}
