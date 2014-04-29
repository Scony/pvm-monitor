#include <iostream>
#include <pvm3.h>
#include <algorithm>
#include <unistd.h>

#include "Monitor.hpp"

using namespace std;

Monitor * Monitor::instance = NULL;

Monitor & Monitor::getInstance()
{
  return *instance;
}

Monitor::Monitor() :
  pvm(Pvm::getInstance())
{
  instance = this;
  timestamp = 0;
  responses = 0;
  conditionWaitingForRelease = -1;
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

bool Monitor::critical()
{
  cout << responses << "::" << pvm.vTids.size() << "::" << queue.size() << endl;
  if(responses == pvm.vTids.size() && queue.front().id == pvm.tid)
    return true;
  return false;
}

void Monitor::recv()
{
  int bufid;

  // CONDITION_ENQUEUE
  bufid = pvm_nrecv(-1,CONDITION_ENQUEUE);
  if(bufid > 0)
    {
      int msg[2];
      pvm_upkint(msg,2,1);
      Condition::getInstance(msg[1]).queue.push_back(msg[0]);
    }

  // CONDITION_DEQUEUE
  bufid = pvm_nrecv(-1,CONDITION_DEQUEUE);
  if(bufid > 0)
    {
      int msg[2];
      pvm_upkint(msg,2,1);
      Condition::getInstance(msg[1]).queue.pop_front();
    }

  // CONDITION_SIGNAL
  bufid = pvm_nrecv(-1,CONDITION_SIGNAL);
  if(bufid > 0)
    {
      int msg;
      pvm_upkint(&msg,1,1);
      Condition::getInstance(msg).signalized = true;
    }

  // MUTEX_REQUEST
  bufid = pvm_nrecv(-1,MUTEX_REQUEST);
  if(bufid > 0)
    {
      // add to queue & sort it
      int inMsg[2];
      pvm_upkint(inMsg,2,1);
      queue.push_back(Element(inMsg[0],inMsg[1]));
      queue.sort();

      // update lamport clock
      timestamp = (timestamp > inMsg[1] ? timestamp : inMsg[1]) + 1;

      // send response
      int outMsg[2] = { pvm.tid, timestamp };
      pvm_psend(inMsg[0],MUTEX_RESPONSE,outMsg,2,PVM_INT);
    }

  // MUTEX_RESPONSE
  bufid = pvm_nrecv(-1,MUTEX_RESPONSE);
  if(bufid > 0)
    {
      // increment responses
      int msg[2];
      pvm_upkint(msg,2,1);
      responses++;

      // update lamport clock
      timestamp = (timestamp > msg[1] ? timestamp : msg[1]) + 1;
    }

  // MUTEX_RELEASE
  bufid = pvm_nrecv(-1,MUTEX_RELEASE);
  if(bufid > 0)
    {
      // if some condition.signal() is waiting for release of waived mutex
      if(conditionWaitingForRelease >= 0)
	Condition::getInstance(conditionWaitingForRelease).released = true;
      else
	{
	  // drop him from queue
	  int msg[2];
	  pvm_upkint(msg,2,1);
	  for(list<Element>::iterator i = queue.begin(); i != queue.end(); i++)
	    if(i->id == msg[0])
	      {
		queue.erase(i);
		break;
	      }

	  // update lamport clock
	  timestamp = (timestamp > msg[1] ? timestamp : msg[1]) + 1;
	}
    }

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

void Monitor::lock()
{
  cout << "lock\n";

  // increment lamport clock
  timestamp++;

  // add myself to queue & sort
  queue.push_back(Element(pvm.tid,timestamp));
  queue.sort();

  // send MUTEX_REQUEST to all
  int msg[2] = { pvm.tid, timestamp };
  for(vector<int>::iterator i = pvm.vTids.begin(); i != pvm.vTids.end(); i++)
    pvm_psend(*i,MUTEX_REQUEST,msg,2,PVM_INT);

  // while not in critical section wait for messages
  while(!critical())
    recv();
}

void Monitor::unlock()
{
  cout << "unlock\n";

  // increment lamport clock
  if(critical())
    timestamp++;

  // send MUTEX_RELEASE to all
  int msg[2] = { pvm.tid, timestamp };
  for(vector<int>::iterator i = pvm.vTids.begin(); i != pvm.vTids.end(); i++)
    pvm_psend(*i,MUTEX_RELEASE,msg,2,PVM_INT);

  // drop myself from queue
  for(list<Element>::iterator i = queue.begin(); i != queue.end(); i++)
    if(i->id == pvm.tid)
      {
	queue.erase(i);
	break;
      }

  // clear responses
  responses = 0;
}

Monitor::_export::_export()
{
  Monitor::instance->lock();
}

Monitor::_export::~_export()
{
  Monitor::instance->unlock();
}

Monitor::Element::Element(int id, int timestamp)
{
  this->id = id;
  this->timestamp = timestamp;
}

bool Monitor::Element::operator<(Element &e)
{
  if(timestamp != e.timestamp)
    return timestamp < e.timestamp;
  return id < e.id;
}
