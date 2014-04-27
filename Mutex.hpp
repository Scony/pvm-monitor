#ifndef MUTEX_HPP
#define MUTEX_HPP

#include "Pvm.hpp"

class Mutex
{
public:
  static Mutex & getInstance();
  void lock();
  void unlock();
private:
  Mutex();
};

#endif
