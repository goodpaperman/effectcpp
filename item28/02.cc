
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

  T& operator* () const { return *pointee; }  
  T* operator-> () const { return pointee; } 
  operator T* () const { return pointee; } 

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


int main()
{
  auto_ptr<int> pti1(new int(42)); 
  auto_ptr<int> pti2 = pti1; 
  auto_ptr<int> pti3; 
  pti3 = pti2; 

  cout << *pti3 << endl; 
  cout << (pti1 == pti2) << endl; 
  cout << (pti1 == pti3) << endl; 

  auto_ptr<float> ptf1(new float(42)); 
  auto_ptr<float> ptf2(ptf1); 
  //cout << (pti3 == ptf1) << endl; 
  //cout << (pti3 == ptf2) << endl; 
  //cout << (pti1 == ptf1) << endl; 
  //cout << (pti1 == ptf2) << endl; 
  cout << (ptf1 == ptf2) << endl; 

  //delete ptf2; 
  return 0; 
} 

