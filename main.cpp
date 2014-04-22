#include <iostream>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
#include <pvm3.h>

#include "Demo.hpp"

using namespace std;

int main()
{
  int mytid = pvm_mytid();
  // int partid = pvm_parent();

  cout << "TID:" << mytid << endl;

  Demo * d = new Demo;
  for(int i = 0; i < 10; i++)
    d->print(mytid);
  delete d;
  // printf("TID: %d %x (parent %d %x) \n",mytid,mytid,partid,partid);
  // sleep(rand() % 6);

  // struct pvmtaskinfo * taskp;
  // int ntask;
  // int info = pvm_tasks(0,&ntask,&taskp);
  // for(int i = 0; i < ntask; i++)
  //   printf("ITEM: %d %x\n",taskp[i].ti_tid,taskp[i].ti_tid);

  pvm_exit();
  return 0;
}
