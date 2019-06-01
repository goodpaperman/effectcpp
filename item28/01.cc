
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

template <class T>
class auto_ptr
{
public:
  auto_ptr(T *ptr = 0) : pointee(ptr) {}
  auto_ptr(auto_ptr<T> &rhs) { pointee = rhs.pointee; rhs.pointee = 0; } 
  ~auto_ptr() { delete pointee; } 
  auto_ptr<T>& operator= (auto_ptr<T> &rhs); 

  T& operator* () const; 
  T* operator-> () const; 

private:
  T *pointee; 
}; 

template <class T>
auto_ptr<T>& auto_ptr<T>::operator= (auto_ptr<T> &rhs)
{
  if(this == &rhs)
    return *this; 

  delete pointee; 
  pointee = rhs.pointee; 
  rhs.pointee = 0; 
  return *this; 
}

template <class T>
T& auto_ptr<T>::operator* () const 
{
  return *pointee; 
}

template <class T>
T* auto_ptr<T>::operator-> () const 
{
  return pointee; 
}

int main()
{
  auto_ptr<int> pti1(new int(42)); 
  auto_ptr<int> pti2 = pti1; 
  auto_ptr<int> pti3; 
  pti3 = pti2; 

  cout << *pti3 << endl; 
  return 0; 
}
