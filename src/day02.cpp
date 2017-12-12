#include "day02.h"

std::string day02(std::ifstream& file)
{
  int ans1 = 0;
  int ans2 = 0;
  char letter;
  int number = 0;
  std::list<int> numbers;
  std::list<std::list<int>> rows;
  int digit;
  while(file.get(letter))
  {
    switch ((int)letter)
    {
      case 9:     //End of number
        if(number != 0)
          numbers.push_back(number);
        number = 0;
        break;
      case 10:    //End of row
        if(number != 0)
          numbers.push_back(number);
        number = 0;
        if(numbers.size()>0)
          rows.push_back(numbers);
        numbers.clear();
        break;
      default:    //Hopefully a digit
        digit = (int)letter - 48;
        if(digit<0 && digit>9)
          MessageBox(NULL, "Unknown char found", "warning",MB_OK);
        else
        {
          number *= 10;
          number += digit;
        }
    }
  }
  for (std::list<std::list<int>>::const_iterator it1 = rows.begin(); it1 != rows.end(); ++it1)
  {
    unsigned int min = -1;
    unsigned int max = 0;
    for (std::list<int>::const_iterator it2 = it1->begin(); it2 != it1->end(); ++it2)
    {
      if((unsigned int)(*it2) < min)
        min = *it2;
      if((unsigned int)(*it2) > max)
        max = *it2;
    }
    ans1 += max-min;
  }
  for (std::list<std::list<int>>::const_iterator it1 = rows.begin(); it1 != rows.end(); ++it1)
    for (std::list<int>::const_iterator it2 = it1->begin(); it2 != it1->end(); ++it2)
      for (std::list<int>::const_iterator it3 = it1->begin(); it3 != it1->end(); ++it3)
        if(*it2%(*it3) == 0 && *it2/(*it3) != 1)
          ans2 += *it2/(*it3);
  std::stringstream out;
  out << "Day 2\nPart 1: " << ans1 << "\nPart 2: " << ans2;
  return out.str();
}
