
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
  Widget(const Widget &w) { cout << "Widget copy ctor." << endl; bval = w.bval;}
  ~Widget() { cout << "Widget dtor." << endl; } 
  bool val() const { return bval; } 
  void val(bool v) { bval = v; } 

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
  //static WidgetEx w; 
  //throw &w; 
  throw new WidgetEx(); 
}

void ThrowItEx()
{
  try
  {
    ThrowIt(); 
  }
  catch(Widget *w)
  {
    cout << "catch a Widget, bool = " << w->val() << endl; 
    w->val(1); 
    throw; 
  }
}

int main()
{
  try 
  {
    ThrowItEx(); 
  }
  catch(const WidgetEx *w)
  {
    cout << "catch a WidgetEx, bool = " << w->val()  << endl; 
    delete const_cast<WidgetEx*>(w); 
  }
  

  cout << endl; 
  return 0; 
}
