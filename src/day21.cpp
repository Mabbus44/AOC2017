#include "day21.h"

std::string day21(std::ifstream& file)
{
  int ans1, ans2;
  std::string line;
  Day21Art art;
  while(std::getline(file, line))
  {
    if(line.length() > 0)
    {
      Day21Rule newRule;
      newRule.load(line);
      art.rules.push_back(newRule);
    }
  }
  for(int i=0; i<18; i++)
  {
    art.splitArt();
    art.applyRules();
    art.assembleArt();
    if(i==4)
      ans1 = art.art.countOn();
  }
  ans2 = art.art.countOn();
  for(std::list<Day21Rule>::iterator it = art.rules.begin(); it != art.rules.end(); ++it)
    it->clean();
  std::stringstream out;
  out << "Day 21\nPart 1: " << ans1 << "\nPart 2: " << ans2;
  return out.str();
}


Day21Matrix::Day21Matrix()
{
}

Day21Matrix::Day21Matrix(std::string line)
{
  load(line);
}

void Day21Matrix::load(std::string line)
{
  if(line.size() == 5)
    setSize(2);
  else if(line.size() == 11)
    setSize(3);
  else if(line.size() == 19)
    setSize(4);
  else
  {
    std::cout << "Warning, invalid inputstring:" << line << std::endl;
    return;
  }
  std::stringstream ssLine(line);
  char bit;
  for(int y=0; y<size; y++)
  {
    for(int x=0; x<size;x++)
    {
      ssLine >> bit;
      if(bit == '#')
        matrix[x][y] = true;
      else if(bit == '.')
        matrix[x][y] = false;
      else
      {
        std::cout << "Warning, invalid inputstring:" << line << std::endl;
        size = 0;
        delete[] matrix;
        return;
      }
    }
    ssLine >> bit;
  }
}

Day21Matrix::~Day21Matrix()
{
}

void Day21Matrix::rot()
{
  int thisX, thisY, nextX, nextY, saveVal;
  for(int startY=0; startY<size/2; startY++)
  {
    for(int startX=0; startX<size-1; startX++)
    {
      thisX = startX;
      thisY = startY;
      saveVal = matrix[thisX][thisY];
      for(int i=0; i<3; i++)
      {
        nextX = size - 1 - thisY;
        nextY = thisX;
        matrix[thisX][thisY] = matrix[nextX][nextY];
        thisX = nextX;
        thisY = nextY;
      }
      matrix[thisX][thisY] = saveVal;
    }
  }
}

void Day21Matrix::flip()
{
  for(int y=0; y<size/2; y++)
    for(int x=0; x<size; x++)
      std::swap(matrix[x][y], matrix[x][size-y-1]);
}

void Day21Matrix::clean()
{
  delete[] matrix;
}

Day21Matrix& Day21Matrix::operator=(Day21Matrix& other)
{
  setSize(other.size);
  for(int x=0; x<size; x++)
    for(int y=0; y<size; y++)
      matrix[x][y] = other.matrix[x][y];
  return *this;
}

bool Day21Matrix::operator==(Day21Matrix& other)
{
  if(size != other.size)
    return false;
  for(int y=0; y<size; y++)
    for(int x=0; x<size; x++)
      if(matrix[x][y] != other.matrix[x][y])
        return false;
  return true;
}

void Day21Matrix::setSize(int size)
{
  this->size = size;
  matrix = new bool*[size];
  for(int x=0; x<size; x++)
    matrix[x] = new bool[size];
}

int Day21Matrix::getSize()
{
  return size;
}

Day21Matrix* Day21Matrix::getSubMatrix(int startX, int startY, int size)
{
  Day21Matrix* ret = new Day21Matrix;
  ret->setSize(size);
  for(int x=0; x<size; x++)
    for(int y=0; y<size; y++)
      ret->matrix[x][y] = matrix[startX + x][startY + y];
  return ret;
}

void Day21Matrix::print()
{
  for(int y=0; y<size; y++)
  {
    for(int x=0; x<size; x++)
    {
      if(matrix[x][y])
        std::cout << "#";
      else
        std::cout << ".";
    }
    std::cout << std::endl;
  }
}

int Day21Matrix::countOn()
{
  int ans = 0;
  for(int y=0; y<size; y++)
  {
    for(int x=0; x<size; x++)
    {
      if(matrix[x][y])
        ans++;
    }
  }
  return ans;
}

void Day21Rule::print()
{
  std::cout << "Inputs" << std::endl;
  for(std::list<Day21Matrix*>::iterator it=input.begin(); it!=input.end(); ++it)
  {
    (*it)->print();
    std::cout << std::endl;
  }
  std::cout << "Output" << std::endl;
  output.print();
  std::cout << std::endl;
}

void Day21Rule::load(std::string line)
{
  int charPos = line.find_first_of(' ');
  Day21Matrix* inputMat = new Day21Matrix(line.substr(0, charPos));
  Day21Matrix* oldInputMat;
  input.push_back(inputMat);
  for(int i = 0; i<7; i++)
  {
    oldInputMat = inputMat;
    inputMat = new Day21Matrix();
    *inputMat = *oldInputMat;
    if(i==3)
      inputMat->flip();
    else
      inputMat->rot();
    input.push_back(inputMat);
  }
  charPos = line.find_first_of('>')+2;
  output.load(line.substr(charPos, line.size()-charPos));
}

bool Day21Rule::applyRule(Day21Matrix* mat)
{
  bool match = false;
  for(std::list<Day21Matrix*>::iterator it=input.begin(); it!=input.end() && !match; ++it)
  {
    if((**it) == (*mat))
      match = true;
  }
  if(match)
  {
    mat->clean();
    *mat = output;
    return true;
  }
  return false;
}

Day21Rule::Day21Rule()
{
}

Day21Rule::~Day21Rule()
{
}

void Day21Rule::clean()
{
  for(std::list<Day21Matrix*>::iterator it = input.begin(); it != input.end(); ++it)
  {
    (*it)->clean();
    delete *it;
  }
  output.clean();
}

Day21Art::Day21Art()
{
  std::string startString = ".#./..#/###";
  art.load(startString);
  artInPieces = NULL;
}

Day21Art::~Day21Art()
{

}

void Day21Art::splitArt()
{
  int blockSize;
  if(art.getSize()%2 == 0)
    blockSize = 2;
  else
  {
    blockSize = 3;
    if(art.getSize()%3 !=0)
      std::cout << "Error: Invalid matrix size!!!" << std::endl;
  }
  if(artInPieces)
  {
    for(int x=0; x<splitArtSize; x++)
    {
      for(int y=0; y<splitArtSize; y++)
      {
        artInPieces[x][y]->clean();
        delete artInPieces[x][y];
      }
      delete[] artInPieces[x];
    }
    delete[] artInPieces;
  }
  splitArtSize = art.getSize()/blockSize;
  artInPieces = new Day21Matrix**[splitArtSize];
  for(int x=0; x<splitArtSize; x++)
  {
    artInPieces[x] = new Day21Matrix*[splitArtSize];
    for(int y=0; y<splitArtSize; y++)
    {
      artInPieces[x][y] = art.getSubMatrix(x*blockSize, y*blockSize, blockSize);
    }
  }
}

void Day21Art::applyRules()
{
  bool done;
  for(int x=0; x<splitArtSize; x++)
  {
    for(int y=0; y<splitArtSize; y++)
    {
      done = false;
      for(std::list<Day21Rule>::iterator it=rules.begin(); it!=rules.end() && !done; ++it)
        done = it->applyRule(artInPieces[x][y]);
      if(!done)
        std::cout << "Error: Matrix matched no rule" << std::endl;
    }
  }
}

void Day21Art::assembleArt()
{
  int blockSize = artInPieces[0][0]->getSize();
  art.clean();
  art.setSize(splitArtSize*blockSize);
  for(int x=0; x<splitArtSize; x++)
  {
    for(int y=0; y<splitArtSize; y++)
    {
      for(int x2=0; x2<blockSize; x2++)
      {
        for(int y2=0; y2<blockSize; y2++)
        {
          art.matrix[x*blockSize+x2][y*blockSize+y2] = artInPieces[x][y]->matrix[x2][y2];
        }
      }
    }
  }
}
