#ifndef CONDITION_HPP
#define CONDITION_HPP

#include "Monitor.hpp"

class Condition
{
public:
  void wait();
  void signal();
};

#endif
