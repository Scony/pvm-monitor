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
      for(int i = 0; i < 4; i++)
	sc[i] = (rand() % 26) + 97;
      cout << "producer:";
      for(int i = 0; i < 4; i++)
	cout << sc[i];
      cout << endl;
      c.signal();
      usleep(1000000);
    }
  else
    {
      c.wait();
      cout << "consumer:";
      for(int i = 0; i < 4; i++)
	cout << sc[i];
      cout << endl;
    }
}
