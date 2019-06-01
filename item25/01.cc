
#include <iostream> 
#include <string> 
#include <vector> 

using std::cout; 
using std::endl; 
using std::string; 
using std::vector; 
using std::ostream; 


class NLComponent
{
public:
  virtual ostream& output(ostream &os) const 
  {
    cout << "NLComponent "; 
  }
}; 

class TextBlock : public NLComponent
{
public:
  virtual ostream& output(ostream &os) const
  {
    cout << "TextBlock "; 
  }
}; 

class Graphic : public NLComponent
{
public:
  virtual ostream& output(ostream &os) const
  {
    cout << "Graphic "; 
  }
}; 

inline ostream& operator<< (ostream &os, const NLComponent &c)
{
  return c.output(os); 
}

int main()
{
  NLComponent nlc; 
  TextBlock tb; 
  Graphic g; 
  cout << g << tb << nlc; 
  cout << endl; 
  return 0; 
}
