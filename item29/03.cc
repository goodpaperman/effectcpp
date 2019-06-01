
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
  friend ostream& operator<< (ostream &os, const String &s); 
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
    bool shareble; 
    int refCount; 
    char *data; 

    StringValue(const char *initValue); 
    ~StringValue(); 
  }; 

  StringValue *value; 
}; 

String::StringValue::StringValue(const char *initValue)
 : shareble(true), refCount(1)
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

String::String(const String &rhs)
{
  if(rhs.value->shareble)
  {
    value = rhs.value; 
    ++ value->refCount;
  } 
  else 
   value = new StringValue(rhs.value->data); 
 
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

  if(rhs.value->shareble)
  {
    value = rhs.value; 
    ++ value->refCount; 
  }
  else 
    value = new StringValue(rhs.value->data); 

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

  value->shareble = false; 
  return value->data[index]; 
}

const char& String::operator[] (int index) const
{
  return value->data[index]; 
}

ostream& operator<< (ostream& os, const String &s)
{
  os << s.value->data << endl; 
}

int main()
{
  String a = "Hello", b = a, c = b, d = c, e = d; 
  a[1] = 'x'; 
  cout << "a = " << a << endl; 
  char *p = &a[1]; 
  b = a; 
  cout << "b = " << b << endl; 
  *p = 'y'; 
  cout << "a = " << a << endl; 
 
  const string str1 = "hello"; 
  const char *q = &str1[1]; 
  string str2 = str1; 
  *const_cast<char*>(q) = 'o'; 
  cout << str1 << " " << str2 << endl; 
  return 0; 
}
