#include "Condition.hpp"

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
