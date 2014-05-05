#ifndef SCHAR_HPP
#define SCHAR_HPP

#include <vector>

class Schar
{
public:
  Schar();
private:
  int id;
  char value;

private:
  static std::vector<Schar*> instances;
  static int nextId;
};

#endif
