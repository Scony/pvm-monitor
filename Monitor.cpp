#include <iostream>
#include <pvm3.h>
#include <algorithm>
#include <unistd.h>

#include "Monitor.hpp"
#include "Mutex.hpp"

using namespace std;

Monitor::Monitor() :
  pvm(Pvm::getInstance())
{

}

Monitor::~Monitor()
{
  for(vector<int>::iterator i = pvm.vTids.begin(); i != pvm.vTids.end(); i++)
    pvm_psend(*i,MONITOR_DONE,&pvm.tid,1,PVM_INT);
  while(!done())
    recv();
}

bool Monitor::done()
{
  sort(pvm.vTids.begin(),pvm.vTids.end());
  sort(vDone.begin(),vDone.end());
  return pvm.vTids == vDone;
}

void Monitor::recv()
{
  int bufid;

  // mutex recv
  Mutex::getInstance().recv();

  // MONITOR_DONE
  bufid = pvm_nrecv(-1,MONITOR_DONE);
  if(bufid > 0)
    {
      int who;
      pvm_upkint(&who,1,1);
      vDone.push_back(who);
    }

  // dont waste CPU
  // usleep(100000);
}

Monitor::_export::_export()
{
  Mutex::getInstance().lock();
}

Monitor::_export::~_export()
{
  Mutex::getInstance().unlock();
}
