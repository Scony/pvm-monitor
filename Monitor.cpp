#include <iostream>
#include <pvm3.h>
#include <stdio.h>
#include <algorithm>
#include <unistd.h>

#include "Monitor.hpp"

using namespace std;

Monitor::Monitor()
{
  id = Monitor::monitorNextId++;
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
  for(vector<int>::iterator i = vTids.begin(); i != vTids.end(); i++)
    pvm_psend(*i,MONITOR_DONE+id*THRESHOLD,&tid,1,PVM_INT);
  while(!done())
    recv();
}

bool Monitor::done()
{
  sort(vTids.begin(),vTids.end());
  sort(vDone.begin(),vDone.end());
  return vTids == vDone;
}

void Monitor::recv()
{
  int bufid;

  // MONITOR_DONE
  bufid = pvm_nrecv(-1,MONITOR_DONE+id*THRESHOLD);
  if(bufid > 0)
    {
      int who;
      int info = pvm_upkint(&who,1,1);
      if(info < 0)
	;			// FIXME: exception ?
      vDone.push_back(who);
    }

  // dont waste CPU
  usleep(100000);
}

Monitor::_export::_export(mutex * mx)
{
  this->mx = mx;
  mx->lock();
}

Monitor::_export::~_export()
{
  mx->unlock();
}

int Monitor::monitorNextId = 0;
int Monitor::mutexNextId = 0;

Monitor::mutex::mutex()
{
  id = Monitor::mutexNextId++;
}

void Monitor::mutex::lock()
{
  cout << "lock\n";
}

void Monitor::mutex::unlock()
{
  cout << "unlock\n";
}
