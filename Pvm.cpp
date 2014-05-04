#include "Pvm.hpp"

Pvm & Pvm::getInstance()
{
  static Pvm instance;
  return instance;
}

Pvm::Pvm()
{
  tid = pvm_mytid();
  struct pvmtaskinfo * taskp;
  int ntask;
  pvm_tasks(0,&ntask,&taskp);
  for(int i = 0; i < ntask; i++)
    if(taskp[i].ti_ptid != 0 && taskp[i].ti_tid != tid)
      vTids.push_back(taskp[i].ti_tid);
}

Pvm::~Pvm()
{
  pvm_exit();
}
