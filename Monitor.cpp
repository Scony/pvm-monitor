#include <iostream>
#include <pvm3.h>
#include <stdio.h>

#include "Monitor.hpp"

using namespace std;

Monitor::Monitor()
{
  tid = pvm_mytid();
  struct pvmtaskinfo * taskp;
  int ntask;
  int info = pvm_tasks(0,&ntask,&taskp);
  for(int i = 0; i < ntask; i++)
    if(taskp[i].ti_ptid != 0 && taskp[i].ti_tid != tid)
      vTids.push_back(taskp[i].ti_tid);
}

Monitor::~Monitor()
{
  cout << "D" << (int)done() << endl;
}

bool Monitor::done()
{
  return vTids == vDone;
}

int Monitor::mutexNextId = 0;

Monitor::mutex::mutex()
{
  id = Monitor::mutexNextId++;
}

void Monitor::mutex::lock()
{
  // 
}

void Monitor::mutex::unlock()
{
  // 
}
