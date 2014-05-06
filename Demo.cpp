#include <iostream>
#include <stdlib.h>
#include <unistd.h>

#include "Demo.hpp"

using namespace std;

void Demo::print()
{
  EXPORT;
  if(pvm.tid > pvm.vTids.front())
    {
      x = rand() % 1337;
      cout << "producer:" << x << endl;
      c.signal();
      usleep(1000000);
    }
  else
    {
      c.wait();
      cout << "consumer:" << x << endl;
    }
}
