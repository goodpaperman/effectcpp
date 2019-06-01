
#include <iostream> 
#include <string> 
#include <vector> 

using std::cout; 
using std::endl; 
using std::string; 
using std::vector; 

class Widget
{
public:
  Widget() { cout << "Widget ctor." << endl; } 
  ~Widget() { cout << "Widget dtor." << endl; } 

  static void* operator new(size_t size) 
  {
    cout << "Widget::operator new(" << size << ")" << endl; 
    //return malloc(size); 
    return ::operator new(size); 
  }

  static void* operator new(size_t size, void *location)
  {
    cout << "Widget::operator new(" << size << "," << location << ")" << endl; 
    return location; 
  }

  static void* operator new[](size_t size)
  {
    cout << "Widget::operator new[](" << size << ")" << endl; 
    return ::operator new[](size); 
  }

  static void* operator new[](size_t size, void *location)
  {
    cout << "Widget::operator new[](" << size << "," << location << ")" << endl; 
    int *p = reinterpret_cast<int*>(location); 
    *p = size; 
    return p+1; 
  }

  static void operator delete(void *buffer)
  {
    cout << "Widget::operator delete(" << buffer << ")" << endl; 
    //free(buffer); 
    ::operator delete(buffer); 
  }

  static void operator delete[](void *buffer)
  {
    cout << "Widget::operator delete[](" << buffer << ")" << endl; 
    ::operator delete[](buffer); 
  }

private:
  bool bval; 
  char cval; 
  short sval; 
  int ival; 
  long lval; 
  float fval; 
  double dval; 
}; 

void* operator new(size_t size)
{
  cout << "operator new(" << size << ")" << endl; 
  //return new char(size); //::operator new(size); 
  return malloc(size); 
}

//void* operator new(size_t size, void *location)
//{
//  cout << "operator new(" << size << "," << location << ")" << endl; 
//  return location; 
//}

void* operator new[](size_t size)
{
  cout << "operator new[](" << size << ")" << endl; 
  return malloc(size); 
}


void operator delete(void *buffer)
{
  cout << "operator delete(" << buffer << ")" << endl; 
  //::operator delete(buffer); 
  free(buffer); 
}

void operator delete[](void *buffer)
{
  cout << "operator delete[](" << buffer << ")" << endl; 
  free(buffer); 
}

int main()
{
  Widget *pw = new Widget(); 
  delete pw; 
  cout << endl; 

  void *buf = operator new(sizeof(Widget)); 
  pw = new(buf) Widget(); 
  pw->~Widget(); 
  operator delete(buf); 
  cout << endl; 

  pw = new Widget[10](); 
  int *p  = reinterpret_cast<int*>(pw); 
  cout << "buffer size: " << *(p-1) << endl;   
  delete []pw; 
  cout << endl; 

  buf = operator new[](sizeof(Widget)*5+sizeof(int)); 
  pw = new(buf) Widget[5](); 
  p = reinterpret_cast<int*>(pw); 
  cout << "buffer size: " << *(p-1) << endl; 
  for(int i=0; i<5; ++ i)
    pw[i].~Widget(); 
  operator delete[](buf);   
  cout << endl; 

  p = new int[3]; 
  cout << "buffer size: " << *(p-1) << endl; 
  delete []p; 
  cout << endl; 
  return 0; 
}
