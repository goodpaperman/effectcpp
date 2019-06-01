
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

void testAddress()
{
  char *pc = new char; 
  char *pc2 = new char; 
  char c, c2; 
  static char sc, sc2; 
  printf("heap =   %p\n", pc);
  printf("heap2 =  %p\n", pc2);  
  printf("stack =  %p\n", &c); 
  printf("stack2 = %p\n", &c2); 
  printf("static = %p\n", &sc); 
  printf("static2 =%p\n", &sc2); 

  //cout << "heap =   " << pc << endl
  //     << "stack =  " << &c << endl
  //     << "static = " << &sc << endl; 
}

int main()
{
  //UPNumber n; 
  UPNumber *p = new UPNumber(); 
  //delete p; 
  p->destroy(); 

  NegativeUPNumber n; 
  NegativeUPNumber *n2 = new NegativeUPNumber; 
  delete n2;

  testAddress();  
  return 0; 
}
