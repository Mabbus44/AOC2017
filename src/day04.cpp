#include "day04.h"

std::string day04(std::ifstream& file)
{
  int ans1 = 0;
  int ans2 = 0;
  std::string line;
  while(std::getline(file, line))
  {
    std::istringstream iss(line);
    std::list<std::string> passphrase;
    std::list<std::string> passphrase2;
    bool valid = true;
    bool valid2 = true;
    do
    {
        std::string subs;
        iss >> subs;
        if(subs.length() > 0)
        {
          std::list<std::string>::iterator it;
          for(it=passphrase.begin(); it!=passphrase.end(); ++it)
          {
            if(subs.compare(*it) == 0)
              valid = false;
          }
          passphrase.push_back(subs);
          std::sort(subs.begin(), subs.end());
          for(it=passphrase2.begin(); it!=passphrase2.end(); ++it)
          {
            if(subs.compare(*it) == 0)
              valid2 = false;
          }
          passphrase2.push_back(subs);
        }
    } while (iss);
    if(valid)
      ans1++;
    if(valid2)
      ans2++;
  }
  std::stringstream out;
  out << "Day 4\nPart 1: " << ans1 << "\nPart 2: " << ans2;
  return out.str();
}
