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
  cout << "MID: " << id << endl;
  tid = pvm_mytid();
  struct pvmtaskinfo * taskp;
  int ntask;
  int info = pvm_tasks(0,&ntask,&taskp);
  for(int i = 0; i < ntask; i++)
    if(taskp[i].ti_ptid != 0 && taskp[i].ti_tid != tid)
      {
	cout << "MATE: " << taskp[i].ti_tid << endl;
	vTids.push_back(taskp[i].ti_tid);
      }
}

Monitor::~Monitor()
{
  cout << "TAG" << endl;
  for(vector<int>::iterator i = vTids.begin(); i != vTids.end(); i++)
    {
      cout << "PSEND: " << *i << " :: "<< pvm_psend(*i,MONITOR_DONE+id*THRESHOLD,&tid,1,PVM_INT) << endl;
      // pvm_initsend( PvmDataDefault );
      // pvm_pkint( &tid, 1, 1 );
      // pvm_send( *i, MONITOR_DONE+id*THRESHOLD );
    }
  while(!done())
    recv();
  cout << "D" << (int)done() << endl;
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
  cout << "BUFID: " << bufid << endl;
  if(bufid > 0)
    {
      int who;
      int info = pvm_upkint(&who,1,1);
      if(info < 0)
	;			// FIXME: exception ?
      cout << "WHO: " << who << endl;
      vDone.push_back(who);
    }

  // dont waste CPU
  usleep(100000);
}

int Monitor::monitorNextId = 0;
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
