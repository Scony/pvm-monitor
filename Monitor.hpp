#ifndef MONITOR_HPP
#define MONITOR_HPP

#include <list>

#include "Pvm.hpp"

#define MONITOR_DONE 1

#define MUTEX_REQUEST 10
#define MUTEX_RESPONSE 11
#define MUTEX_RELEASE 12

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

  // class condition
  // {
  //   void wait();
  //   void signal();
  // };

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
