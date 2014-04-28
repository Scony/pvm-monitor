#include <iostream>
#include <unistd.h>

#include "Demo.hpp"

using namespace std;

void Demo::print()
{
  EXPORT;
  if(pvm.tid > pvm.vTids.front())
    {
      c.signal();
      usleep(1000000);
    }
  else
    c.wait();
  cout << "in print\n";
}
