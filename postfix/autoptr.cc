
#include <iostream> 
#include <string> 
#include <vector> 
#include <list>
#include <map> 

using std::cout; 
using std::endl; 
using std::string; 
using std::vector; 
using std::list; 
using std::map; 
using std::pair; 
using std::ostream; 

template <class T>
class auto_ptr
{
public:
  explicit auto_ptr(T *p = 0) : pointee(p) {}
  
  template <class U>
  auto_ptr(auto_ptr<U> &rhs) : pointee(rhs.release()) {}

  ~auto_ptr() { delete pointee; }

  template <class U>
  auto_ptr<T>& operator= (auto_ptr<U> &rhs)
  {
    if(this != &rhs) reset(rhs.release()); 
    return *this; 
  }

  T& operator* () const { return *pointee; }
  T* operator-> () const { return pointee; }
  T* get() const { return pointee; }
  T* release()
  {
    T *oldPointee = pointee; 
    pointee = 0; 
    return oldPointee; 
  }

  void reset(T *p = 0)
  {
    if(pointee != p)
    {
      delete pointee; 
      pointee = p; 
    }
  }

private:
  T *pointee; 
  
  //template <class U> friend class auto_ptr<U>; 
}; 

template class auto_ptr<int>; 
int main()
{
  auto_ptr<int> pint(new int(42)); 
  cout << *pint << endl; 
  //auto_ptr<double> pdbl; 
  //pdbl = pint; 
  //cout << *pdbl << endl; 
  return 0; 
}
