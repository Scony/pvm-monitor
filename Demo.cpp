#include <iostream>

#include "Demo.hpp"

using namespace std;

Demo::Demo()
{
  id = pvm.tid % PHILOSOPHERS;
  for(int i = 0; i < PHILOSOPHERS; i++)
    state[i] = THINKING;
}

void Demo::grab()
{
  EXPORT;
  state[id] = STARVING;
  cout << id << " started starving\n";

  if(isAlone(id))
    state[id] = EATING;
  else
    {
      alone[id].wait();
      state[id] = EATING;
    }
  cout << id << " started eating\n";
}

void Demo::put()
{
  EXPORT;
  state[id] = THINKING;
  cout << id << " started thinking\n";

  if(isAlone((id + 1) % PHILOSOPHERS))
    alone[(id + 1) % PHILOSOPHERS].signal();

  if(isAlone((id + PHILOSOPHERS - 1) % PHILOSOPHERS))
    alone[(id + PHILOSOPHERS - 1) % PHILOSOPHERS].signal();
}

bool Demo::isAlone(int id)
{
  if(state[id] == STARVING &&
     state[(id + 1) % PHILOSOPHERS] != EATING &&
     state[(id + PHILOSOPHERS - 1) % PHILOSOPHERS] != EATING)
    return true;
  return false;
}
