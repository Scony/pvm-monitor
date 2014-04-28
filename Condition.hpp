#ifndef CONDITION_HPP
#define CONDITION_HPP

#include <vector>
#include "Monitor.hpp"

class Condition
{
public:
  Condition();
  static Condition & getInstance(int id);
  void wait();
  void signal();

private:
  int id;

private:
  static std::vector<Condition*> instances;
  static int nextId;
};

#endif
