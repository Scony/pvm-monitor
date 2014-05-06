#ifndef SCHAR_HPP
#define SCHAR_HPP

#include <vector>

class Schar
{
  friend class Monitor;

public:
  Schar();

public:
  operator char();
  Schar & operator=(const Schar &rhs);
  Schar & operator=(const char &rhs);

private:
  char value;

private:
  static std::vector<Schar*> instances;
};

#endif
