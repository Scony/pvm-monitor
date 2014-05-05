#include "Schar.hpp"

Schar::Schar()
{
  id = nextId++;
  instances.push_back(this);
  value = 0;
}

std::vector<Schar*> Schar::instances;
int Schar::nextId = 0;
