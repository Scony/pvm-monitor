#ifndef PVM_HPP
#define PVM_HPP

#include <pvm3.h>
#include <vector>

class Pvm
{
public:
  static Pvm & getInstance();

  int tid;
  std::vector<int> vTids;
private:
  Pvm();
  ~Pvm();
};

#endif
