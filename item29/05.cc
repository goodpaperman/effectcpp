
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

class RCObject
{
public:
  RCObject() : refCount(0), shareable(true) {}
  RCObject(const RCObject &rhs) : refCount(0), shareable(true) {}
  RCObject& operator= (const RCObject &rhs) { return *this; } 
  virtual ~RCObject() = 0; 
  void addRef() { ++ refCount; cout << "ref = " << refCount << endl; } 
  void removeRef() { if(--refCount == 0) delete this; } 
  void markUnshareable() { shareable = false; } 
  bool isShareable() const { return shareable; } 
  bool isShared() const { return refCount > 1; } 
 
private:
  int refCount; 
  bool shareable; 
}; 

RCObject::~RCObject() {}

template <class T>
class RCIPtr
{
public:
  RCIPtr(T *ptr = 0) : counter(new CountHolder(ptr)) { init(); } 
  RCIPtr(const RCIPtr &rhs) : counter(rhs.counter) { init(); } 
  ~RCIPtr() { counter->removeRef(); } 

  void markUnshareable() { makeCopy(); counter->markUnshareable(); }
  RCIPtr& operator= (const RCIPtr &rhs); 
  const T* operator->() const { return counter->pointee; } 
  T* operator->() { makeCopy(); return counter->pointee; } 
  const T& operator* () const { return *(counter->pointee); } 
  T* operator*() { makeCopy(); return *(counter->pointee); } 

private:
  struct CountHolder : public RCObject
  {
    CountHolder(T *ptr) : pointee(ptr) {}
    ~CountHolder() { delete pointee; } 
    T *pointee; 
  }; 

  CountHolder *counter; 
  void init(); 
  void makeCopy(); 
}; 

template <class T>
void RCIPtr<T>::init()
{
  if(!counter->isShareable())
  {
    T *oldValue = counter->pointee; 
    counter = new CountHolder(new T(*oldValue)); 
  }
  counter->addRef(); 
}

template <class T>
RCIPtr<T>& RCIPtr<T>::operator= (const RCIPtr &rhs)
{
  if(counter != rhs.counter)
  {
    counter->removeRef(); 
    counter = rhs.counter; 
    init(); 
  }

  return *this; 
}

template <class T>
void RCIPtr<T>::makeCopy()
{
  if(counter->isShared())
  {
    T *oldValue = counter->pointee; 
    counter->removeRef(); 
    counter = new CountHolder(new T(*oldValue)); 
    counter->addRef(); 
  }
}

class RCString; 
class String
{
  friend ostream& operator<< (ostream &os, const String &s); 
  friend ostream& operator<< (ostream &os, const RCString &s); 
public:
  String(const char *initValue = ""); 
  String(const String &rhs); 
  String& operator= (const String &rhs); 
  ~String(); 

  char& operator[] (int index); 
  const char& operator[] (int index) const; 

private:
  void init(const char *initValue); 
  char *data; 
}; 

void String::init(const char *initValue)
{
  data = new char[strlen(initValue)+1]; 
  strcpy(data, initValue); 
}

String::String(const char *initValue)
{
  cout << "init " << initValue << endl; 
  init(initValue); 
}

String::String(const String &rhs)
{ 
  cout << "copy " << rhs.data << endl; 
  init(rhs.data); 
}

String& String::operator= (const String &rhs)
{
  cout << "assign " << rhs.data << endl; 
  if(this != &rhs)
  {
    delete []data; 
    init(rhs.data); 
  }

  return *this; 
}

String::~String()
{
  cout << "fini " << data << endl; 
  delete []data; 
}


char& String::operator[] (int index) 
{
  return data[index]; 
}

const char& String::operator[] (int index) const
{
  return data[index]; 
}

ostream& operator<< (ostream& os, const String &s)
{
  os << s.data << endl; 
}


class RCString
{
  friend ostream& operator<<(ostream& os, const RCString &s); 
public:
  RCString(const char *initValue = "") : value(new String(initValue)) {}
  const char& operator[] (int index) const { return value->operator[](index); }
  char& operator[] (int index) { value.markUnshareable(); return value->operator[](index); }

private:
  RCIPtr<String> value; 
}; 

ostream& operator<< (ostream& os, const RCString &s)
{
  os << s.value->data << endl;
}



int main()
{
  RCString a = "Hello", b = a, c = b, d = c, e = d; 
  a[1] = 'x'; 
  cout << "a = " << a << endl; 
  char *p = &a[1]; 
  b = a; 
  cout << "b = " << b << endl; 
  *p = 'y'; 
  cout << "a = " << a << endl; 
  cout << "b = " << b << endl; 
  return 0; 
}
