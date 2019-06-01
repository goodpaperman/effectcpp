
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

class HeapTracked
{
public:
  virtual ~HeapTracked(){ }
  static void* operator new(size_t size); 
  static void operator delete(void *ptr); 

  bool isOnHeap() const; 

private:
  static list<void*> address; 
}; 

list<void*> HeapTracked::address; 

void* HeapTracked::operator new(size_t size)
{
  void *p = ::operator new(size); 
  cout << "new " << p << endl; 
  address.push_front(p); 
  return p; 
}

void HeapTracked::operator delete(void *ptr)
{
  list<void*>::iterator it = std::find(
    address.begin(), address.end(), ptr); 
  if(it != address.end())
  {
    cout << "delete " << ptr << endl; 
    address.erase(it); 
    ::operator delete(ptr); 
  }
  else 
    cout << "missing address " << ptr << endl; 
}

bool HeapTracked::isOnHeap() const
{
  const void *p = dynamic_cast<const void*>(this); 
  list<void*>::iterator it = find(
    address.begin(), address.end(), p); 
  return it != address.end(); 
}

class UPNumber : public HeapTracked
{
public:
  UPNumber() { cout << "ctor" << endl; }
  void destroy() { if(isOnHeap()) delete this; } 
  ~UPNumber() {  cout << "dtor" << endl; } 
}; 

class NegativeUPNumber : public UPNumber
{
}; 

int main()
{
  UPNumber n; 
  UPNumber *p = new UPNumber(); 
  n.destroy(); 
  p->destroy(); 

  NegativeUPNumber n1; 
  NegativeUPNumber *n2 = new NegativeUPNumber; 
  n1.destroy(); 
  n2->destroy(); 
  return 0; 
}
