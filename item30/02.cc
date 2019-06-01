
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
class RCPtr
{
public:
  RCPtr(T *ptr = 0) : pointee(ptr) { init(); } 
  RCPtr(const RCPtr &rhs) : pointee(rhs.pointee) { init(); } 
  ~RCPtr() { if(pointee) pointee->removeRef(); } 

  RCPtr& operator= (const RCPtr &rhs); 
  T* operator->() const { return pointee; } 
  T* operator*() const { return *pointee; } 

private:
  T *pointee; 
  void init(); 
}; 

template <class T>
void RCPtr<T>::init()
{
  if(pointee == 0)
    return; 

  if(!pointee->isShareable())
    pointee = new T(*pointee); 
  pointee->addRef(); 
}

template <class T>
RCPtr<T>& RCPtr<T>::operator= (const RCPtr &rhs)
{
  if(pointee != rhs.pointee)
  {
    if(pointee)
      pointee->removeRef(); 
    pointee = rhs.pointee; 
    init(); 
  }

  return *this; 
}


class String
{
  friend ostream& operator<< (ostream &os, const String &s); 
public:
  class CharProxy
  {
  public:
    CharProxy(String &str, int index):theString(str),charIndex(index) {}
    CharProxy& operator= (const CharProxy &rhs) { 
      update(rhs.theString.value->data[rhs.charIndex]); 
      return *this; 
    }
    CharProxy& operator= (char c) { update(c); return *this; }
    operator char() const { return theString.value->data[charIndex]; }
  private:
    String &theString; 
    int charIndex; 
    void update(char c); 
  }; 

public:
  String(const char *initValue = ""); 

  CharProxy operator[] (int index); 
  const CharProxy operator[] (int index) const; 

private:
  struct StringValue : public RCObject
  {
    char *data; 

    StringValue(const char *initValue); 
    StringValue(const StringValue &rhs); 
    ~StringValue(); 
    void init(const char *initValue); 
  }; 

  RCPtr<StringValue> value; 
}; 

void String::StringValue::init(const char *initValue)
{
  data = new char[strlen(initValue)+1]; 
  strcpy(data, initValue); 
}

String::StringValue::StringValue(const char *initValue)
{
  cout << "init " << initValue << endl; 
  init(initValue); 
}

String::StringValue::StringValue(const StringValue &rhs)
{ 
  cout << "copy " << rhs.data << endl; 
  init(rhs.data); 
}

String::StringValue::~StringValue()
{
  cout << "fini " << data << endl; 
  delete []data; 
}

void String::CharProxy::update(char c)
{
  if(theString.value->isShared())
    theString.value = new StringValue(theString.value->data); 

  theString.value->data[charIndex] = c; 
}

String::String(const char *initValue) : value(new StringValue(initValue)) 
{
}

String::CharProxy String::operator[] (int index) 
{
  return String::CharProxy(*this, index); 
}

const String::CharProxy String::operator[] (int index) const
{
  return CharProxy(const_cast<String&>(*this), index); 
}

ostream& operator<< (ostream& os, const String &s)
{
  os << s.value->data << endl; 
}

int main()
{
  String a = "Hello", b = a, c = b; 
  a[1] = 'x'; 
  cout << "a = " << a << " b = " << b << endl; 
  const String::CharProxy& p = a[1]; 
  b = a; 
  cout << "a = " << a << " b = " << b << endl; 
  const_cast<String::CharProxy&>(p) = 'y'; 
  cout << "a = " << a << " b = " << b << endl; 
  return 0; 
}
