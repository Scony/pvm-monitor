#include <iostream>

#include "Monitor.hpp"

using namespace std;

Monitor::mutex::mutex()
{
  id = Monitor::mutexNextId++;
  cout << id << endl;
}

void Monitor::mutex::lock()
{
  // 
}

void Monitor::mutex::unlock()
{
  // 
}

int Monitor::mutexNextId = 0;
