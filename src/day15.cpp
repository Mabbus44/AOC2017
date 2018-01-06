#include "day15.h"

std::string day15(std::ifstream& file)
{
  int ans1 = 0, ans2 = 0;
  std::string line;
  unsigned __int64 genAStart = 0;
  unsigned __int64 genBStart = 0;
  unsigned __int64 genA = 0;
  unsigned __int64 genB = 0;
  unsigned __int64 factorA = 16807;
  unsigned __int64 factorB = 48271;
  unsigned __int64 divisor = 2147483647;
  unsigned __int16 genALowest16Bits;
  unsigned __int16 genBLowest16Bits;
  while(std::getline(file, line))
  {
    if(line.length() > 0)
    {
      std::stringstream ss(line);
      int inputSequence = 0;
      std::string num;
      while(ss >> num)
      {
        if(inputSequence == 4)
        {
          if(genAStart == 0)
            genAStart = atoi(num.c_str());
          else
            genBStart = atoi(num.c_str());
        }
        inputSequence++;
      }
    }
  }
  genA = genAStart;
  genB = genBStart;
  for(int i=0; i<40000000; i++)
  {
    genA *= factorA;
    genB *= factorB;
    genA = genA%divisor;
    genB = genB%divisor;
    genALowest16Bits = (unsigned __int16)genA;
    genBLowest16Bits = (unsigned __int16)genB;
    if(genALowest16Bits == genBLowest16Bits)
      ans1++;
  }
  genA = genAStart;
  genB = genBStart;
  for(int i=0; i<5000000; i++)
  {
    do
    {
      genA *= factorA;
      genA = genA%divisor;
    }while(genA%4 != 0);
    do
    {
      genB *= factorB;
      genB = genB%divisor;
    }while(genB%8 != 0);
    genALowest16Bits = (unsigned __int16)genA;
    genBLowest16Bits = (unsigned __int16)genB;
    if(genALowest16Bits == genBLowest16Bits)
      ans2++;
  }
  std::stringstream out;
  out << "Day 15\nPart 1: " << ans1 << "\nPart 2: " << ans2;
  return out.str();
}
