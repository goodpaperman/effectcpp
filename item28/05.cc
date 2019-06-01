
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
  auto_ptr(T *ptr = 0) : pointee(ptr) { cout << "ctor" << endl; }
  auto_ptr(auto_ptr<T> &rhs) { pointee = rhs.pointee; rhs.pointee = 0; 
    cout << "copy ctor" << endl; } 
  ~auto_ptr() { /*delete pointee; */cout << "dtor" << endl; } 
  auto_ptr<T>& operator= (auto_ptr<T> &rhs); 

  T& operator* () const { return *pointee; }  
  T* operator-> () const { return pointee; } 
  operator T* () const { return pointee; } 
  
  template <class U>
  operator auto_ptr<U> () { 
    cout << "converting..." << endl; 
    //T *tmp = pointee; 
    //pointee = 0; 
    //return auto_ptr<U>(tmp); 
    return auto_ptr<U>(pointee); 
  }

private:
  T *pointee; 
}; 

template <class T>
auto_ptr<T>& auto_ptr<T>::operator= (auto_ptr<T> &rhs)
{
  if(this == &rhs)
    return *this; 

  cout << "assign ctor" << endl; 
  delete pointee; 
  pointee = rhs.pointee; 
  rhs.pointee = 0; 
  return *this; 
}


class MusicProduct 
{
public:
  MusicProduct(const string &title) : title_(title) {}; 
  virtual void play() const { cout << "music playing..." << endl; } 
  virtual void displayTitle() const { cout << title_ << endl; } 
  virtual ~MusicProduct() { cout << "Music dtor for " << title_  << endl; }

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
  virtual ~Cassette() { cout << "Cassette dtor" << endl; } 
}; 

class CD : public MusicProduct
{
public:
  CD(const string &title) : MusicProduct(title) {}
  virtual void play() const { cout << "CD playing..." << endl; }
  virtual void displayTitle() const 
  { 
    cout << "CD "; 
    MusicProduct::displayTitle(); 
  }

  virtual ~CD() { cout << "CD dtor" << endl; } 
}; 

void displayAndPlay(const auto_ptr<MusicProduct> &pmp, int num)
{
  for(int i=1; i<=num; ++ i)
  {
    pmp->displayTitle(); 
    pmp->play(); 
  }
}

int main()
{
  auto_ptr<Cassette> funMusic(new Cassette("Alapalooza")); 
  auto_ptr<CD> nightmareMusic(new CD("Disco Hits of the 70s")); 

  displayAndPlay(funMusic, 2); 
  displayAndPlay(nightmareMusic, 3);

  delete funMusic; 
  delete nightmareMusic; 
  return 0; 
} 

