#include "Mutex.hpp"
#include <iostream>
using namespace std;

Mutex::Mutex()
{
}

Mutex & Mutex::getInstance()
{
  static Mutex instance;
  return instance;
}

void Mutex::lock()
{
  cout << "lock\n";
}

void Mutex::unlock()
{
  cout << "unlock\n";
}
