#include "day10.h"

std::string day10(std::ifstream& file)
{
  int ans1 = 0;
  std::string strAns2;
  std::string line;
  std::getline(file, line);
  int buffer[256];
  std::stringstream ss(line);
  int length;
  int skip = 0;
  int pos = 0;
  int botPos;
  int topPos;
  for(int i=0; i<256; i++)
    buffer[i] = i;
  while (ss >> length)
  {
    botPos = pos;
    topPos = pos + length - 1;
    if(topPos>255)
      topPos -= 256;
    for(int i=0; i<length/2; i++)
    {
      std::swap(buffer[botPos], buffer[topPos]);
      topPos--;
      botPos++;
      if(topPos<0)
        topPos += 256;
      if(botPos>255)
        botPos -= 256;
    }
    pos += length;
    pos += skip;
    skip++;
    while(pos>255)
      pos -= 256;
    if (ss.peek() == ',')
      ss.ignore();
  }
  ans1 = buffer[0] * buffer[1];
  int input[line.size() + 5];
  for(unsigned int i=0; i<line.size(); i++)
    input[i] = int(line[i]);
  input[line.size()] = 17;
  input[line.size()+1] = 31;
  input[line.size()+2] = 73;
  input[line.size()+3] = 47;
  input[line.size()+4] = 23;
  skip = 0;
  pos = 0;
  for(int i=0; i<256; i++)
    buffer[i] = i;
  for(int i3=0; i3<64; i3++)
  {
    for(int i2=0; i2<(int)(sizeof(input)/sizeof(int)); i2++)
    {
      length = input[i2];
      botPos = pos;
      topPos = pos + length - 1;
      while(topPos>255)
        topPos -= 256;
      for(int i=0; i<length/2; i++)
      {
        std::swap(buffer[botPos], buffer[topPos]);
        topPos--;
        botPos++;
        while(topPos<0)
          topPos += 256;
        while(botPos>255)
          botPos -= 256;
      }
      pos += length;
      pos += skip;
      skip++;
      while(pos>255)
        pos -= 256;
    }
  }
  int denseBuffer[16];
  for(int i2=0; i2<16; i2++)
  {
    denseBuffer[i2] = 0;
    for(int i=0; i<16; i++)
      denseBuffer[i2] = denseBuffer[i2] ^ buffer[i2*16+i];
  }
  for(int i=0; i<16; i++)
  {
    int digit1 = denseBuffer[i]/16;
    int digit2 = denseBuffer[i]-digit1*16;
    strAns2 += day10Num2Hex(digit1);
    strAns2 += day10Num2Hex(digit2);
  }
  std::stringstream out;
  out << "Day 10\nPart 1: " << ans1 << "\nPart 2: " << strAns2;
  return out.str();
}

char day10Num2Hex(int num)
{
  if(num<0 || num>15)
    return 'q';          //invalid input
  switch(num)
  {
    case 10:
      return 'a';
    case 11:
      return 'b';
    case 12:
      return 'c';
    case 13:
      return 'd';
    case 14:
      return 'e';
    case 15:
      return 'f';
    default:
      return char(num+48);
  }
  return 'q';          //should never happend
}
