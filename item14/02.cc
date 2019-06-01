
#include <iostream> 
#include <string> 
#include <vector> 

using std::cout; 
using std::endl; 
using std::string; 
using std::vector; 



void f2() //throw()
{
  cout << "f2()" << endl; 
  throw 1.1; 
}

int main()
{
  try
  {
    f2(); 
  } 
  catch(double d)
  {
    cout << "catch a double " << d << endl; 
  }

  cout << endl; 
  return 0; 
}
