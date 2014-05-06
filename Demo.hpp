#ifndef DEMO_HPP
#define DEMO_HPP

#include "Monitor.hpp"

class Demo : public Monitor
{
  Condition c;
  sint x;
public:
  void print();
};

#endif
