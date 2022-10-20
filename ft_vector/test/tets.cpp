#include <iostream>
#include <vector>

int main ()
{
  std::vector<int> myvector(3, 42);// = {10,20,30};

  myvector.emplace ( myvector.begin()+1, 100 );
  return 0;
}
/*
#include <iostream>
#include <vector>

int main ()
{
  std::vector<int> myvector;
  myvector.erase(myvector.begin());

    std::cout << myvector.capacity() << std::endl;
  return 0;
}
*/
