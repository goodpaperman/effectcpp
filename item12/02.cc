
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
  Widget()
  {
    cout << "Widget ctor." << endl; 
  }

  Widget(const Widget &w)
  {
    cout << "Widget copy ctor." << endl; 
  }

  ~Widget() 
  { 
    cout << "Widget dtor." << endl; 
  } 

private:
  bool bval; 
  char cval; 
  short sval; 
  int ival; 
  long lval; 
  float fval; 
  double dval; 
  double *pval; 
}; 

class WidgetEx : public Widget
{
public: 
  WidgetEx() { cout << "WidgetEx ctor." << endl; } 
  WidgetEx(const WidgetEx &w) { cout << "WidgetEx copy ctor." << endl; } 
  ~WidgetEx() { cout << "WidgetEx dtor." << endl; } 
}; 

void ThrowIt()
{
  WidgetEx w; 
  Widget &rw = w; 
  cout << "before throw " << endl; 
  throw rw; 
  //throw w; 
}

int main()
{
  try 
  {
    ThrowIt(); 
  }
  catch(Widget &w)
  {
    cout << "catch a Widget!!!" << endl; 
  }
  

  cout << endl; 
  return 0; 
}
