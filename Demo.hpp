#ifndef DEMO_HPP
#define DEMO_HPP

#include "Monitor.hpp"

class Demo : public Monitor
{
  Condition c;
  schar sc[4];
public:
  void print();
};

#endif
