
#include <iostream> 
#include <string> 
#include <vector> 

using std::cout; 
using std::endl; 
using std::string; 
using std::vector; 

class exception
{
public:
  virtual const char* what() throw() { return "exception"; } 
}; 

class runtime_error : public exception
{
public:
  virtual const char* what() throw() { return "runtime error"; } 
}; 

class validation_error : public runtime_error
{
public:
  virtual const char* what() throw() { return "validation error"; } 
}; 

void ThrowIt()
{
  validation_error err; 
  throw err; 
}

void ThrowItEx()
{
  try
  {
    ThrowIt(); 
  }
  catch(runtime_error &err)
  {
    cout << "catch a runtime_error, " << err.what() << endl; 
    //throw err;  
    throw; 
  }
}

int main()
{
  try 
  {
    ThrowItEx(); 
  }
  catch(exception &err) 
  {
    cout << "catch a exception, " << err.what() << endl; 
  }
  

  cout << endl; 
  return 0; 
}
