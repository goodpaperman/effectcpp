
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
class const_auto_ptr
{
public:
  const_auto_ptr(const T *ptr = 0) : pointee(const_cast<T*>(ptr)){ 
    cout << "const_auto_ptr ctor." << endl; 
  }
  const_auto_ptr(const_auto_ptr<T> &rhs) { 
    pointee = rhs.pointee; 
    rhs.pointee = 0; 
  }
  ~const_auto_ptr() { 
    cout << "del " << pointee << endl; 
    delete pointee; 
  }
  const_auto_ptr<T>& operator= (const_auto_ptr<T> &rhs); 

  //const T& operator* () const { return *pointee; }
  const T* operator* () const { return pointee; } 
  operator const T* () const { return pointee; }

protected:
    T *pointee; 
}; 

template <class T>
const_auto_ptr<T>& const_auto_ptr<T>::operator= (const_auto_ptr<T> &rhs)
{
  if(this == &rhs)
    return *this; 

  cout << "const_auto_ptr assign ctor." << endl; 
  delete pointee; 
  pointee = rhs.pointee; 
  rhs.pointee = 0; 
  return *this; 
}

template <class T>
class auto_ptr : public const_auto_ptr<T>
{
public:
  auto_ptr(T *ptr = 0) : const_auto_ptr<T>(ptr) {}
  auto_ptr(auto_ptr<T> &rhs) : const_auto_ptr<T>(rhs) {} 
  ~auto_ptr() {} 
  auto_ptr<T>& operator= (auto_ptr<T> &rhs); 

  T& operator* () const { return *const_auto_ptr<T>::pointee; }  
  T* operator-> () const { return const_auto_ptr<T>::pointee; } 
  operator T* () const { return const_auto_ptr<T>::pointee; } 
}; 

template <class T>
auto_ptr<T>& auto_ptr<T>::operator= (auto_ptr<T> &rhs)
{
  const_auto_ptr<T>::operator= (rhs); 
  return *this; 
}


class MusicProduct 
{
public:
  MusicProduct(const string &title) : title_(title) {}; 
  virtual void play() const { cout << "music playing..." << endl; } 
  virtual void displayTitle() const { cout << title_ << endl; } 
  virtual ~MusicProduct() { }

private:
  string title_; 
}; 

class Cassette : public MusicProduct
{
public:
  Cassette(const string &title) : MusicProduct(title) {} 
  virtual void play() const { cout << "Cassette playing..." << endl; }
  virtual void displayTitle() const 
  {
    cout << "Cassette "; 
    MusicProduct::displayTitle(); 
  }
}; 

class CasSingle : public Cassette
{
public:
  CasSingle(const string &title) : Cassette(title) {}
  virtual void play() const { cout << "CasSingle playing..." << endl; }
  virtual void displayTitle() const 
  {
    cout << "CasSingle "; 
    Cassette::displayTitle(); 
  }
}; 

class CD : public MusicProduct
{
public:
  CD(const string &title) : MusicProduct(title) { cout<< "ctor" << endl; }
  virtual void play() const { cout << "CD playing..." << endl; }
  virtual void displayTitle() const 
  { 
    cout << "CD "; 
    MusicProduct::displayTitle(); 
  }

  virtual ~CD() { cout << "dtor" << endl; } 
}; 


int main()
{
  auto_ptr<CD> pCD(new CD("Famous Movie Themes")); 
  const_auto_ptr<CD> pConstCD;
  pConstCD = pCD; 
  return 0; 
} 

