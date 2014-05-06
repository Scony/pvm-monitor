#include "Sint.hpp"

Sint::Sint()
{
  value = 0;
  serialize();
}

Sint::operator int()
{
  deserialize();
  return value;
}

Sint & Sint::operator=(const Sint &rhs)
{
  value = rhs.value;
  serialize();
  return *this;
}

Sint & Sint::operator=(const int &rhs)
{
  value = rhs;
  serialize();
  return *this;
}

void Sint::serialize()
{
  char * rc = reinterpret_cast<char*>(&value);
  for(int i = 0; i < 4; i++)
    byte[i] = rc[i];
}

void Sint::deserialize()
{
  value = ((unsigned char)byte[0]) | ((unsigned char)byte[1] << 8) | ((unsigned char)byte[2] << 16) | ((unsigned char)byte[3] << 24);
}
