
#include <iostream> 
#include <string> 
#include <vector> 
#include <list> 

using std::cout; 
using std::endl; 
using std::string; 
using std::vector; 
using std::list; 
using std::ostream; 


class UPNumber
{
public:
  UPNumber() { cout << "ctor" << endl; }
  ~UPNumber() {  cout << "dtor" << endl; } 

private:
  static void* operator new(size_t size); 
  static void* operator new[](size_t size); 
  static void operator delete(void *ptr); 
  static void operator delete[](void *ptr);
}; 

class NegativeUPNumber : public UPNumber
{
}; 

int main()
{
  UPNumber n; 
  //UPNumber *p = new UPNumber(); 
  //UPNumber *parr = new UPNumber[4](); 
  //delete []parr; 

  NegativeUPNumber n1; 
  //NegativeUPNumber *n2 = new NegativeUPNumber; 
  return 0; 
}
