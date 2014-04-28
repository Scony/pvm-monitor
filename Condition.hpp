#ifndef CONDITION_HPP
#define CONDITION_HPP

#include <vector>
#include <list>
#include "Monitor.hpp"

class Condition
{
  friend class Monitor;

public:
  Condition();
  static Condition & getInstance(int id);
  void wait();
  void signal();

private:
  Pvm & pvm;
  int id;
  std::list<int> queue;
  bool signalized;
  bool released;

private:
  static std::vector<Condition*> instances;
  static int nextId;
};

#endif
