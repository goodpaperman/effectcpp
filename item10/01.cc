
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
  try : pval(new double(12.3))
  { 
    cout << "Widget ctor." << endl; 
    //pval = new double(12.3); 
    throw std::exception(); 
  }catch(...)
  {
    cout << "delete pval" << endl; 
    delete pval; 
  }

  ~Widget() { 
    cout << "delete pval" << endl; 
    delete pval; 
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


int main()
{
  try {
  Widget w; 
  }catch(std::exception &e)
  {
    cout << "catch it!!" << endl; 
  }

  cout << endl;
  Widget *pw = 0; 
  try { 
    pw = new Widget(); 
  }catch(std::exception &e)
  {
    cout << "catch it !!!" << endl; 
    cout << "pw = " << pw << endl; 
    delete pw; 
  }

  cout << endl; 
  return 0; 
}
