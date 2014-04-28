#include "Condition.hpp"

Condition::Condition()
{
  id = nextId++;
  instances[id] = this;
}

Condition & Condition::getInstance(int id)
{
  return *instances[id];
}

void Condition::wait()
{
  // send CONDITION_ENQUEUE
  // unlock()
  // wait for signal
  // send CONDITION_DEQUEUE

}

void Condition::signal()
{
  // send CONDITION_SIGNAL
  // wait for MUTEX_RELEASE
}

int Condition::nextId = 0;
std::vector<Condition*> Condition::instances;
