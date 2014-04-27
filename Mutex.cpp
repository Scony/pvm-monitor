#include <iostream>
#include <vector>
#include <unistd.h>

#include "Mutex.hpp"

using namespace std;

Mutex::Mutex() :
  pvm(Pvm::getInstance())
{
  timestamp = 0;
  responses = 0;
}

Mutex & Mutex::getInstance()
{
  static Mutex instance;
  return instance;
}

void Mutex::lock()
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

void Mutex::unlock()
{
  if(critical())
    {
      cout << "unlock\n";

      // increment lamport clock
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
}

void Mutex::recv()
{
  int bufid;

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

  // dont waste CPU
  usleep(100000);
}

bool Mutex::critical()
{
  cout << responses << "::" << pvm.vTids.size() << "::" << queue.size() << endl;
  if(responses == pvm.vTids.size() && queue.front().id == pvm.tid)
    return true;
  return false;
}

Mutex::Element::Element(int id, int timestamp)
{
  this->id = id;
  this->timestamp = timestamp;
}

bool Mutex::Element::operator<(Element &e)
{
  if(timestamp != e.timestamp)
    return timestamp < e.timestamp;
  return id < e.id;
}
