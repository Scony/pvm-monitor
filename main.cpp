#include <pvm3.h>

#include "Demo.hpp"

int main()
{
  pvm_mytid();

  Demo * d = new Demo;
  for(int i = 0; i < 10; i++)
    d->print();
  delete d;

  pvm_exit();
  return 0;
}
