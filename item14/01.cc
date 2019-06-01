
#include <iostream> 
#include <string> 
#include <vector> 

using std::cout; 
using std::endl; 
using std::string; 
using std::vector; 


void f1() 
{ 
  cout << "f1()" << endl; 
  throw 0.1; 
} 

void f2() //throw(int)
{
  cout << "f2()" << endl; 
  f1(); 
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
