#include "Demo.hpp"

int main()
{
  Demo d;
  for(int i = 0; i < 5; i++)
    {
      d.grab();
      // eating...
      d.put();
    }

  return 0;
}
