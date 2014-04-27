#include <iostream>
#include <pvm3.h>
#include <stdio.h>
#include <algorithm>
#include <unistd.h>

#include "Monitor.hpp"

using namespace std;

Monitor::Monitor() :
  pvm(Pvm::getInstance())
{

}

Monitor::~Monitor()
{
  // for(vector<int>::iterator i = vTids.begin(); i != vTids.end(); i++)
  //   pvm_psend(*i,MONITOR_DONE+id*THRESHOLD,&tid,1,PVM_INT);
  // while(!done())
  //   recv();
  cout << "x";
  // pvm_exit();
}

bool Monitor::done()
{
  // sort(vTids.begin(),vTids.end());
  // sort(vDone.begin(),vDone.end());
  // return vTids == vDone;
}

void Monitor::recv()
{
  int bufid;

  // MONITOR_DONE
  bufid = pvm_nrecv(-1,MONITOR_DONE);
  if(bufid > 0)
    {
      int who;
      pvm_upkint(&who,1,1);
      vDone.push_back(who);
    }

  // dont waste CPU
  usleep(100000);
}

Monitor::_export::_export()
{
  // this->mx = mx;
  // mx->lock();
}

Monitor::_export::~_export()
{
  // mx->unlock();
}
