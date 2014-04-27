#ifndef MONITOR_HPP
#define MONITOR_HPP

#include "Pvm.hpp"
#include "Mutex.hpp"

#define MONITOR_DONE 1

#define EXPORT _export _exp();

class Monitor
{
protected:
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
  std::vector<int> vDone;

  bool done();
  void recv();
};

#endif
