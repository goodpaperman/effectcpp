
#include <iostream> 
#include <string> 
#include <vector> 

using std::cout; 
using std::endl; 
using std::string; 
using std::vector; 
using std::ostream; 

class UPNumber 
{
public:
  UPNumber() { cout << "ctor" << endl; }
  void destroy() const { delete this; } 

protected:
  ~UPNumber() { cout << "dtor" << endl; } 
}; 

class NegativeUPNumber : public UPNumber
{
}; 


int main()
{
  //UPNumber n; 
  UPNumber *p = new UPNumber(); 
  //delete p; 
  p->destroy(); 

  NegativeUPNumber n; 
  NegativeUPNumber *n2 = new NegativeUPNumber; 
  delete n2; 
  return 0; 
}
