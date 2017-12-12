#include "day12.h"

std::string day12(std::ifstream& file)
{
  int ans1 = 0;
  int ans2 = 0;
  std::string line;
  std::vector<std::vector<int>> programs;
  while(std::getline(file, line))
  {
    if(line.length() > 0)
    {
      std::replace(line.begin(), line.end(), ',', ' ');
      std::stringstream ss(line);
      int inputSequence = 0;
      std::string word;
      while(ss >> word)
      {
        if(inputSequence == 0)
        {
          std::vector<int> newProgram;
          programs.push_back(newProgram);
        }
        if(inputSequence > 1)
          programs[programs.size()-1].push_back(atoi(word.c_str()));
        inputSequence++;
      }
    }
  }
  std::vector<int> allFriendsGroup;
  allFriendsGroup.push_back(0);
  day12AddFriends(programs, allFriendsGroup, 0);
  ans1 = allFriendsGroup.size();
  int friendGroupCount = 1;
  for(int i = 0; i < int(programs.size()); i++)
  {
    std::vector<int>::iterator alreadyFriend = std::find(allFriendsGroup.begin(), allFriendsGroup.end(), i);
    if(alreadyFriend == allFriendsGroup.end())
    {
      std::vector<int> friendsGroup;
      friendsGroup.push_back(i);
      day12AddFriends(programs, friendsGroup, i);
      for(std::vector<int>::iterator localFriend = friendsGroup.begin(); localFriend != friendsGroup.end(); ++localFriend)
        allFriendsGroup.push_back(*localFriend);
      friendGroupCount++;
    }
  }
  ans2 = friendGroupCount;
  std::stringstream out;
  out << "Day 12\nPart 1: " << ans1 << "\nPart 2: " << ans2;
  return out.str();
}

void day12AddFriends(std::vector<std::vector<int>>& programs, std::vector<int>& friendsGroup, int index)
{
  for(std::vector<int>::iterator friendOfIndex = programs[index].begin(); friendOfIndex != programs[index].end(); ++friendOfIndex)
  {
    std::vector<int>::iterator alreadyFriend = std::find(friendsGroup.begin(), friendsGroup.end(), *friendOfIndex);
    if(alreadyFriend == friendsGroup.end())
    {
      friendsGroup.push_back(*friendOfIndex);
      day12AddFriends(programs, friendsGroup, *friendOfIndex);
    }
  }
}
