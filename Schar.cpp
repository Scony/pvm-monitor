#include "Schar.hpp"

Schar::Schar()
{
  instances.push_back(this);
  value = 0;
}

Schar::operator char()
{
  return value;
}

Schar & Schar::operator=(const Schar &rhs)
{
  value = rhs.value;
  return *this;
}

Schar & Schar::operator=(const char &rhs)
{
  value = rhs;
  return *this;
}

std::vector<Schar*> Schar::instances;
