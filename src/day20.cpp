#include "day20.h"

std::string day20(std::ifstream& file)
{
  int ans1;
  int ans2;
  std::string line;
  std::vector<Day20Particle> particles;
  int particleCount = 0;
  while(std::getline(file, line))
  {
    if(line.length() > 0)
    {
      Day20Particle particle;
      particle.load(line);
      particle.index = particleCount;
      particleCount++;
      particles.push_back(particle);
    }
  }
  std::list<Day20Particle> parList;
  for(int i=0; i<(int)particles.size(); i++)
    parList.push_back(particles[i]);
  int minAcc = -1;
  int thisAcc;
  std::vector<Day20Particle> minParticles;
  std::vector<Day20Particle> minParticles2;
  for(int i=0; i<(int)particles.size(); i++)
  {
    thisAcc = abs(particles[i].acc[0]) + abs(particles[i].acc[1]) + abs(particles[i].acc[2]);
    //std::cout << particles[i].index << ": " << thisAcc << " (" << particles[i].acc[0] << "," << particles[i].acc[1] << "," << particles[i].acc[2] << ")" << std::endl;
    if(minAcc == -1 || thisAcc < minAcc)
    {
      minParticles.clear();
      minParticles.push_back(particles[i]);
      minAcc = thisAcc;
      ans1 = particles[i].index;
    }
    else if(thisAcc == minAcc)
      minParticles.push_back(particles[i]);
  }
  int minVel = -1;
  int thisVel;
  for(int i=0; i<(int)minParticles.size(); i++)
  {
    int time = minParticles[i].timeForStandstill();
    for(int i2=0; i2<time; i2++)
      for(int i3=0; i3<(int)minParticles.size(); i3++)
        minParticles[i3].step();
  }
  for(int i=0; i<(int)minParticles.size(); i++)
  {
    thisVel = abs(minParticles[i].vel[0]) + abs(minParticles[i].vel[1]) + abs(minParticles[i].vel[2]);
    //std::cout << minParticles[i].index << "v: " << thisVel << " (" << minParticles[i].vel[0] << "," << minParticles[i].vel[1] << "," << minParticles[i].vel[2] << ")" << std::endl;
    if(minVel == -1 || thisVel < minVel)
    {
      minParticles2.clear();
      minParticles2.push_back(minParticles[i]);
      minVel = thisVel;
      ans1 = minParticles[i].index;
    }
    else if(thisVel == minVel)
      minParticles2.push_back(minParticles[i]);
  }
  __int64 steps=0;
  bool deleteMe;
  for(int fusk=0; fusk<100; fusk++)         //100 visade sig vara tillräckligt länge. Kom inte på lätt sätt att veta när det var klart
  {
    for(std::list<Day20Particle>::iterator it = parList.begin(); it!=parList.end(); ++it)
      it->step();
    steps++;
    std::list<Day20Particle>::iterator it1 = parList.begin();
    while(it1!=parList.end())
    {
      deleteMe = false;
      std::list<Day20Particle>::iterator it2 = it1;
      ++it2;
      while(it2!=parList.end())
      {
        if(*it1 == *it2)
        {
          parList.erase(it2++);
          //std::cout << steps << ": " << parList.size() << std::endl;
          deleteMe = true;
        }
        else
          ++it2;
      }
      if(deleteMe)
      {
        parList.erase(it1++);
        //std::cout << steps << ": " << parList.size() << std::endl;
      }
      else
        it1++;
    }
  }
  ans2 = parList.size();

  std::stringstream out;
  out << "Day 20\nPart 1: " << ans1 << "\nPart 2: " << ans2;
  return out.str();
}

int& Day20V3::operator[](int x)
{
  return v[x];
}

void Day20Particle::load(std::string line)
{
  int charPos = line.find_first_of('<');
  line = line.substr(charPos+1, line.size()-charPos-1);
  charPos = line.find_first_of(',');
  pos[0] = atoi(line.substr(0,charPos).c_str());
  line = line.substr(charPos+1, line.size()-charPos-1);

  charPos = line.find_first_of(',');
  pos[1] = atoi(line.substr(0,charPos).c_str());
  line = line.substr(charPos+1, line.size()-charPos-1);

  charPos = line.find_first_of('>');
  pos[2] = atoi(line.substr(0,charPos).c_str());
  charPos = line.find_first_of('<');
  line = line.substr(charPos+1, line.size()-charPos-1);

  charPos = line.find_first_of(',');
  vel[0] = atoi(line.substr(0,charPos).c_str());
  line = line.substr(charPos+1, line.size()-charPos-1);

  charPos = line.find_first_of(',');
  vel[1] = atoi(line.substr(0,charPos).c_str());
  line = line.substr(charPos+1, line.size()-charPos-1);

  charPos = line.find_first_of('>');
  vel[2] = atoi(line.substr(0,charPos).c_str());
  charPos = line.find_first_of('<');
  line = line.substr(charPos+1, line.size()-charPos-1);

  charPos = line.find_first_of(',');
  acc[0] = atoi(line.substr(0,charPos).c_str());
  line = line.substr(charPos+1, line.size()-charPos-1);

  charPos = line.find_first_of(',');
  acc[1] = atoi(line.substr(0,charPos).c_str());
  line = line.substr(charPos+1, line.size()-charPos-1);

  charPos = line.find_first_of('>');
  acc[2] = atoi(line.substr(0,charPos).c_str());
}

int Day20Particle::timeForStandstill()
{
  int time[3] = {0,0,0};
  int maxTime = 0;
  for(int i=0; i<3; i++)
  {
    if(acc[i] != 0)
    {
      time[i] = vel[i] / -acc[i];
      if(vel[i]%acc[i] != 0)
        time[i]++;
    }
    if(time[i] > maxTime)
      maxTime = time[i];
  }
  return maxTime;
}

void Day20Particle::step()
{
  for(int i=0; i<3; i++)
  {
    vel[i] += acc[i];
    pos[i] += vel[i];
  }
}

bool Day20Particle::operator==(Day20Particle other)
{
  for(int i=0; i<3; i++)
    if(pos[i] != other.pos[i])
      return false;
  return true;
}
