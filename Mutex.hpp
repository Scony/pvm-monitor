#ifndef MUTEX_HPP
#define MUTEX_HPP

#include <list>

#include "Pvm.hpp"

#define MUTEX_REQUEST 10
#define MUTEX_RESPONSE 11
#define MUTEX_RELEASE 12

class Mutex
{
public:
  static Mutex & getInstance();
  void lock();
  void unlock();
  void recv();

private:
  Pvm & pvm;
  int timestamp;
  int responses;

  Mutex();
  bool critical();

  class Element
  {
  public:
    int id;
    int timestamp;
    Element(int id, int timestamp);
    bool operator<(Element &e);
  };

  std::list<Element> queue;
};

#endif
