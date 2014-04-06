#include <iostream>

#include "Demo.hpp"

using namespace std;

void Demo::print(int id)
{
  mx.lock();
  cout << id << ": in print\n";
  mx.unlock();
}
