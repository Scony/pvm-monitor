#ifndef MONITOR_HPP
#define MONITOR_HPP

#include <list>

#include "Pvm.hpp"
#include "Condition.hpp"

#define MONITOR_DONE 1
#define MUTEX_REQUEST 2
#define MUTEX_RESPONSE 3
#define MUTEX_RELEASE 4
#define CONDITION_ENQUEUE 5
#define CONDITION_DEQUEUE 6
#define CONDITION_SIGNAL 7

#define EXPORT _export _exp;

class Monitor
{
protected:
  static Monitor * instance;
  Pvm & pvm;

  Monitor();
  ~Monitor();

  class _export
  {
  public:
    _export();
    ~_export();
  };

  // class sint			/* ? */
  // {
  //   /* operators */
  // };

private:
  int timestamp;
  int responses;
  std::vector<int> vDone;

  void lock();
  void unlock();
  void recv();

  bool done();
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
