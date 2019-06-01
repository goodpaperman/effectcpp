
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

void ThrowIt()
{
  Widget w; 
  //static Widget w; 
  throw w; 
}

int main()
{
  try 
  {
    ThrowIt(); 
  }
  catch(Widget &w)
  {
    cout << "catch it!!!" << endl; 
  }

  cout << endl; 
  return 0; 
}
