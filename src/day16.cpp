#include "day16.h"

std::string day16(std::ifstream& file)
{
  std::string ans1, ans2;
  std::string line;
  std::vector<Day16Instruction> instructions;
  std::vector<int*> oldList;
  while(std::getline(file, line))
  {
    if(line.length() > 0)
    {
      std::replace(line.begin(), line.end(), ',', ' ');
      std::stringstream ss(line);
      std::string instruction;
      while(ss >> instruction)
      {
        if(instruction.length() > 0)
        {
          Day16Instruction newInstruction(instruction);
          instructions.push_back(newInstruction);
        }
      }
    }
  }
  bool identical;
  bool foundLoop = false;
  int loopStart;
  int loopLength;
  int lastDance;
  int dances = 0;
  int positions[16];
  int* savePos;
  for(int i=0; i<16; i++)
    positions[i] = i;
  while(!foundLoop && dances < 1000000000)
  {
    for(std::vector<Day16Instruction>::iterator it1=instructions.begin(); it1!=instructions.end(); ++it1)
    {
      switch(it1->operation)
      {
        case DAY16_SPIN:
        {
          for(int i2=0; i2<it1->arg1; i2++)
          {
            int oldLast = positions[15];
            for(int i=15; i>0; i--)
              positions[i] = positions[i-1];
            positions[0] = oldLast;
          }
          break;
        }
        case DAY16_SWITCH_POSITIONS:
        {
          std::swap(positions[it1->arg1], positions[it1->arg2]);
          break;
        }
        case DAY16_SWITCH_PARTNERS:
        {
          int pos1 = -1;
          int pos2 = -1;
          for(int i=0; i<16; i++)
          {
            if(positions[i] == it1->arg1)
              pos1 = i;
            if(positions[i] == it1->arg2)
              pos2 = i;
          }
          std::swap(positions[pos1], positions[pos2]);
          break;
        }
      }
    }
    for(int i=0; !foundLoop && i<(int)(oldList.size()); i++)
    {
      identical = true;
      for(int i2=0; identical && i2<16; i2++)
      {
        if(oldList[i][i2] != positions[i2])
          identical = false;
      }
      if(identical)
      {
        foundLoop = true;
        loopStart = i;
        loopLength = oldList.size() - i;
      }
    }
    if(foundLoop)
    {
      lastDance = (1000000000-loopStart-1)%loopLength;
      std::stringstream ssAns2;
      for(int i=0; i<16; i++)
        ssAns2 << (char)(oldList[lastDance][i] + 97);
      ans2 = ssAns2.str();
      for(int i2=0; i2<(int)(oldList.size()); i2++)
        delete [] oldList[i2];
    }
    else
    {
      savePos = new int[16];
      for(int i=0; i<16; i++)
        savePos[i] = positions[i];
      oldList.push_back(savePos);
    }
    if(dances == 0)
    {
      std::stringstream ssAns1;
      for(int i=0; i<16; i++)
        ssAns1 << (char)(positions[i] + 97);
      ans1 = ssAns1.str();
    }
    dances++;
  }
  if(!foundLoop)
    ans2 = "No loop found";
  std::stringstream out;
  out << "Day 16\nPart 1: " << ans1 << "\nPart 2: " << ans2;
  return out.str();
}

Day16Instruction::Day16Instruction()
{

}

Day16Instruction::Day16Instruction(std::string instruction)
{
  this->load(instruction);

}

void Day16Instruction::load(std::string instruction)
{
  this->arg1 = -1;
  this->arg2 = -1;
  if(instruction[0] == 's')
  {
    this->operation = DAY16_SPIN;
    instruction=instruction.substr(1, instruction.length()-1);
    this->arg1 = atoi(instruction.c_str());
  }
  if(instruction[0] == 'x')
  {
    this->operation = DAY16_SWITCH_POSITIONS;
    instruction=instruction.substr(1, instruction.length()-1);
    std::replace(instruction.begin(), instruction.end(), '/', ' ');
    std::stringstream ss(instruction);
    std::string stringPart;
    while(ss >> stringPart)
    {
      if(stringPart.length() > 0)
      {
        if(this->arg1 == -1)
          this->arg1 = atoi(stringPart.c_str());
        else
          this->arg2 = atoi(stringPart.c_str());
      }
    }
  }
  if(instruction[0] == 'p')
  {
    this->operation = DAY16_SWITCH_PARTNERS;
    instruction=instruction.substr(1, instruction.length()-1);
    std::replace(instruction.begin(), instruction.end(), '/', ' ');
    std::stringstream ss(instruction);
    std::string stringPart;
    while(ss >> stringPart)
    {
      if(stringPart.length() > 0)
      {
        if(this->arg1 == -1)
          this->arg1 = (int)(stringPart[0]) - 97;
        else
          this->arg2 = (int)(stringPart[0]) - 97;
      }
    }
  }
}
