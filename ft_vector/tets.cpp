#include <iostream>
#include <vector>

int main ()
{
  std::vector<int> myvector;
  myvector.erase(myvector.begin());

    std::cout << myvector.capacity() << std::endl;
  return 0;
}
