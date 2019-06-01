
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


class String
{
public:
  String(const char *initValue = ""); 
  String(const String &rhs); 
  String& operator= (const String &rhs); 
  ~String(); 

  char& operator[] (int index); 
  const char& operator[] (int index) const; 

private:
  struct StringValue
  {
    int refCount; 
    char *data; 

    StringValue(const char *initValue); 
    ~StringValue(); 
  }; 

  StringValue *value; 
}; 

String::StringValue::StringValue(const char *initValue) : refCount(1)
{
  cout << "init " << initValue << endl; 
  data = new char[strlen(initValue)+1]; 
  strcpy(data, initValue); 
}

String::StringValue::~StringValue()
{
  cout << "fini " << data << endl; 
  delete []data; 
}

String::String(const char *initValue) : value(new StringValue(initValue)) 
{
  cout << "ctor = " << value->refCount << endl; 
}

String::String(const String &rhs) : value(rhs.value)
{
  ++ value->refCount; 
  cout << "copy ctor = " << value->refCount << endl; 
}

String::~String()
{
  cout << "dtor = " << value->refCount-1 << endl; 
  if(-- value->refCount == 0)
    delete value; 
}

String& String::operator= (const String &rhs)
{
  if(value == rhs.value)
    return *this; 

  if(-- value->refCount == 0)
    delete value; 

  value = rhs.value; 
  ++ value->refCount; 
  cout << "assign = " << value->refCount << endl; 
  return *this; 
}

char& String::operator[] (int index) 
{
  if(value->refCount > 1)
  {
    -- value->refCount; 
    value = new StringValue(value->data); 
  }

  return value->data[index]; 
}

const char& String::operator[] (int index) const
{
  return value->data[index]; 
}

int main()
{
  String a = "Hello", b = a, c = b, d = c, e = d; 
  a[1] = 'x'; 
  
  return 0; 
}
