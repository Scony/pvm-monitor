#ifndef SINT_HPP
#define SINT_HPP

#include "Schar.hpp"

class Sint
{
public:
  Sint();

public:
  operator int();
  Sint & operator=(const Sint &rhs);
  Sint & operator=(const int &rhs);

private:
  int value;
  Schar byte[4];

  void serialize();
  void deserialize();
};

#endif
