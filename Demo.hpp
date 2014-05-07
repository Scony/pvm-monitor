#ifndef DEMO_HPP
#define DEMO_HPP

#include "Monitor.hpp"

#define THINKING 1
#define STARVING 2
#define EATING 3

#define PHILOSOPHERS 5

class Demo : public Monitor
{
public:
  Demo();
  void grab();
  void put();

private:
  bool isAlone(int id);

private:
  int id;
  schar state[PHILOSOPHERS];
  condition alone[PHILOSOPHERS];
};

#endif
