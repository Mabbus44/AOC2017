#include "day01.h"

std::string day01(std::ifstream& file)
{
  int ans1 = 0;
  int ans2 = 0;
  char letter;
  std::list<int> digits;
  int digit;
  while(file.get(letter))
  {
    digit = (int)letter - 48;
    if(digit>=0 && digit<=9)
      digits.push_back(digit);
  }
  std::list<int>::iterator it;
  int digitsArray[digits.size()];
  it = digits.begin();
  for(unsigned int i = 0; i<digits.size(); i++)
  {
    digitsArray[i] = *it;
    ++it;
  }

  for(unsigned int i = 0; i<digits.size()-1; i++)
    if(digitsArray[i] == digitsArray[i+1])
      ans1 += digitsArray[i];
  if(digitsArray[0] == digitsArray[digits.size()-1])
    ans1 += digitsArray[0];

  for(unsigned int i=0; i<digits.size(); i++)
  {
    unsigned int i2 = i + digits.size()/2;
    if(i2 >= digits.size())
      i2 -= digits.size();
    if(digitsArray[i] == digitsArray[i2])
      ans2 += digitsArray[i];
  }
  std::stringstream out;
  out << "Day 1\nPart 1: " << ans1 << "\nPart 2: " << ans2;
  return out.str();
}
