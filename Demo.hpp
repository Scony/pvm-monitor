#include "Monitor.hpp"

class Demo : public Monitor
{
public:
  void print(int id);

private:
  mutex mx;
};
