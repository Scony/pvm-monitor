#include <iostream>
#include "Condition.hpp"

using namespace std;

Condition::Condition() :
  pvm(Pvm::getInstance())
{
  id = nextId++;
  instances.push_back(this);
  signalized = false;
  released = false;
  cout << "C" << id << endl;
}

Condition & Condition::getInstance(int id)
{
  return *instances[id];
}

void Condition::wait()
{
  cout << "wait\n";

  // send CONDITION_ENQUEUE to all
  int msg[2] = { pvm.tid, id };
  for(vector<int>::iterator i = pvm.vTids.begin(); i != pvm.vTids.end(); i++)
    pvm_psend(*i,CONDITION_ENQUEUE,msg,2,PVM_INT);

  // unlock()
  Monitor::getInstance().unlock();

  // wait for CONDITION_SIGNAL
  while(!signalized)
    Monitor::getInstance().recv();
  signalized = false;

  // send CONDITION_DEQUEUE
  for(vector<int>::iterator i = pvm.vTids.begin(); i != pvm.vTids.end(); i++)
    pvm_psend(*i,CONDITION_DEQUEUE,msg,2,PVM_INT);

}

void Condition::signal()
{
  cout << "signal" << queue.size() << endl;

  if(queue.size() > 0)
    {
      // send CONDITION_SIGNAL to first element in queue
      int msg = id;
      pvm_psend(queue.front(),CONDITION_SIGNAL,&msg,1,PVM_INT);

      // wait for MUTEX_RELEASE
      Monitor::getInstance().conditionWaitingForRelease = id;
      while(!released)
	Monitor::getInstance().recv();
      released = false;
      Monitor::getInstance().conditionWaitingForRelease = -1;
    }
}

int Condition::nextId = 0;
vector<Condition*> Condition::instances;
