#include <vector>

#define MONITOR_DONE 1

#define THRESHOLD 100

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
  static int monitorNextId;
  static int mutexNextId;
  int id;
  int tid;
  std::vector<int> vTids;
  std::vector<int> vDone;

  bool done();
  void recv();
};
