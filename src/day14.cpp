#include "day14.h"

std::string day14(std::string input)
{
  int ans1 = 0;
  for(int i=0; i<128; i++)
  {
    std::stringstream out;
    out << input << "-" << i;
    std::string hashInput = out.str();
    ans1 += day14CountFreeSquares(day14KnotHash(hashInput));
  }
  int** grid = new int*[128];
  for(int i=0; i<128; i++)
    grid[i] = new int[128];

  for(int i=0; i<128; i++)
  {
    std::stringstream out;
    out << input << "-" << i;
    std::string hashInput = out.str();
    std::string hashOutput = day14KnotHash(hashInput);
    int i2 = 0;
    for(int charNum=0; (unsigned int)charNum<hashOutput.size(); charNum++)
    {
      if(hashOutput[charNum] == '0')
      {
        grid[i][i2] = 0;
        grid[i][i2+1] = 0;
        grid[i][i2+2] = 0;
        grid[i][i2+3] = 0;
      }
      if(hashOutput[charNum] == '1')
      {
        grid[i][i2] = 0;
        grid[i][i2+1] = 0;
        grid[i][i2+2] = 0;
        grid[i][i2+3] = 1;
      }
      if(hashOutput[charNum] == '2')
      {
        grid[i][i2] = 0;
        grid[i][i2+1] = 0;
        grid[i][i2+2] = 1;
        grid[i][i2+3] = 0;
      }
      if(hashOutput[charNum] == '3')
      {
        grid[i][i2] = 0;
        grid[i][i2+1] = 0;
        grid[i][i2+2] = 1;
        grid[i][i2+3] = 1;
      }
      if(hashOutput[charNum] == '4')
      {
        grid[i][i2] = 0;
        grid[i][i2+1] = 1;
        grid[i][i2+2] = 0;
        grid[i][i2+3] = 0;
      }
      if(hashOutput[charNum] == '5')
      {
        grid[i][i2] = 0;
        grid[i][i2+1] = 1;
        grid[i][i2+2] = 0;
        grid[i][i2+3] = 1;
      }
      if(hashOutput[charNum] == '6')
      {
        grid[i][i2] = 0;
        grid[i][i2+1] = 1;
        grid[i][i2+2] = 1;
        grid[i][i2+3] = 0;
      }
      if(hashOutput[charNum] == '7')
      {
        grid[i][i2] = 0;
        grid[i][i2+1] = 1;
        grid[i][i2+2] = 1;
        grid[i][i2+3] = 1;
      }
      if(hashOutput[charNum] == '8')
      {
        grid[i][i2] = 1;
        grid[i][i2+1] = 0;
        grid[i][i2+2] = 0;
        grid[i][i2+3] = 0;
      }
      if(hashOutput[charNum] == '9')
      {
        grid[i][i2] = 1;
        grid[i][i2+1] = 0;
        grid[i][i2+2] = 0;
        grid[i][i2+3] = 1;
      }
      if(hashOutput[charNum] == 'a')
      {
        grid[i][i2] = 1;
        grid[i][i2+1] = 0;
        grid[i][i2+2] = 1;
        grid[i][i2+3] = 0;
      }
      if(hashOutput[charNum] == 'b')
      {
        grid[i][i2] = 1;
        grid[i][i2+1] = 0;
        grid[i][i2+2] = 1;
        grid[i][i2+3] = 1;
      }
      if(hashOutput[charNum] == 'c')
      {
        grid[i][i2] = 1;
        grid[i][i2+1] = 1;
        grid[i][i2+2] = 0;
        grid[i][i2+3] = 0;
      }
      if(hashOutput[charNum] == 'd')
      {
        grid[i][i2] = 1;
        grid[i][i2+1] = 1;
        grid[i][i2+2] = 0;
        grid[i][i2+3] = 1;
      }
      if(hashOutput[charNum] == 'e')
      {
        grid[i][i2] = 1;
        grid[i][i2+1] = 1;
        grid[i][i2+2] = 1;
        grid[i][i2+3] = 0;
      }
      if(hashOutput[charNum] == 'f')
      {
        grid[i][i2] = 1;
        grid[i][i2+1] = 1;
        grid[i][i2+2] = 1;
        grid[i][i2+3] = 1;
      }
      i2 += 4;
    }
  }
  int ans2 = 0;
  for(int i=0; i<128; i++)
  {
    for(int i2=0; i2<128; i2++)
    {
      if(grid[i][i2] == 1)
      {
        ans2++;
        day14RemoveArea(grid, i, i2);
      }
    }
  }
  delete [] grid;
  std::stringstream out;
  out << "Day 14\nPart 1: " << ans1 << "\nPart 2: " << ans2;
  return out.str();
}

int day14CountFreeSquares(std::string input)
{
  int count = 0;
  for(int i=0; (unsigned int)i<input.size(); i++)
  {
    if(input[i] == '1' || input[i] == '2' || input[i] == '4' || input[i] == '8')
      count += 1;
    if(input[i] == '3' || input[i] == '5' || input[i] == '6' || input[i] == '9' || input[i] == 'a' || input[i] == 'c')
      count += 2;
    if(input[i] == '7' || input[i] == 'b' || input[i] == 'd' || input[i] == 'e')
      count += 3;
    if(input[i] == 'f')
      count += 4;
  }
  return count;
}

std::string day14KnotHash(std::string input)
{
  std::string strAns;
  int buffer[256];
  int length;
  int skip = 0;
  int pos = 0;
  int botPos;
  int topPos;

  int intInput[input.size() + 5];
  for(unsigned int i=0; i<input.size(); i++)
    intInput[i] = int(input[i]);
  intInput[input.size()] = 17;
  intInput[input.size()+1] = 31;
  intInput[input.size()+2] = 73;
  intInput[input.size()+3] = 47;
  intInput[input.size()+4] = 23;
  for(int i=0; i<256; i++)
    buffer[i] = i;
  for(int i3=0; i3<64; i3++)
  {
    for(int i2=0; i2<(int)(sizeof(intInput)/sizeof(int)); i2++)
    {
      length = intInput[i2];
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
    strAns += day14Num2Hex(digit1);
    strAns += day14Num2Hex(digit2);
  }
  return strAns;
}

char day14Num2Hex(int num)
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

void day14RemoveArea(int** grid, int x, int y)
{
  grid[x][y] = 0;
  if(x>0 && grid[x-1][y] == 1)
    day14RemoveArea(grid, x-1, y);
  if(x<127 && grid[x+1][y] == 1)
    day14RemoveArea(grid, x+1, y);
  if(y>0 && grid[x][y-1] == 1)
    day14RemoveArea(grid, x, y-1);
  if(y<127 && grid[x][y+1] == 1)
    day14RemoveArea(grid, x, y+1);
}
