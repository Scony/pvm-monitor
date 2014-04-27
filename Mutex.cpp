#include <iostream>

#include "Mutex.hpp"

Mutex::Mutex() :
  pvm(Pvm::getInstance())
{
}

Mutex & Mutex::getInstance()
{
  static Mutex instance;
  return instance;
}

void Mutex::lock()
{
  std::cout << "lock\n";
}

void Mutex::unlock()
{
  std::cout << "unlock\n";
}
