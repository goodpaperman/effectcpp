
#include <iostream> 
using std::cout; 
using std::endl; 

template <std::size_t n>
struct factorial {
enum { value = n * factorial<n-1>::value }; 
}; 

template <>
struct factorial<0> {
enum { value = 1 }; 
}; 

int main()
{
  cout << factorial<5>::value  << endl; 
  cout << factorial<10>::value  << endl; 
  return 0; 
}
