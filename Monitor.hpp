#include <vector>

#define MONITOR_BYE 1

class Monitor
{
protected:
  Monitor();
  ~Monitor();

  class mutex
  {
  public:
    void lock();
    void unlock();
    mutex();

  private:
    int id;
  };

  // class condition
  // {
  //   void wait(...);
  //   void signal(...);
  // };

  // class sint			/* ? */
  // {
  //   /* operators */
  // };

private:
  static int mutexNextId;
  int tid;
  std::vector<int> vTids;
  std::vector<int> vDone;

  bool done();
};
