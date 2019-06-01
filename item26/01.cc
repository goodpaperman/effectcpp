
#include <iostream> 
#include <string> 
#include <vector> 

using std::cout; 
using std::endl; 
using std::string; 
using std::vector; 
using std::ostream; 



class Printer
{
public:
  static Printer* makePrinter(); 
  ~Printer() { 
    -- numObjects; 
    cout << "objects " << numObjects << " after dtor." << endl; 
  } 

private:
  Printer() {}
  Printer(const Printer &rhs) {}
  static size_t numObjects; 
  static size_t maxObjects; 
}; 

size_t Printer::numObjects = 0; 
size_t Printer::maxObjects = 10; 

Printer* Printer::makePrinter()
{
  if(numObjects >= maxObjects)
  {
    cout << "objects " << numObjects << " exceed limit " << maxObjects << endl; 
    return 0; 
  }
  
  ++ numObjects; 
  cout << "objects " << numObjects << " after ctor." << endl; 
  return new Printer(); 
}


int main()
{
  vector<Printer*> pvec; 
  for(int i=0; i<11; ++ i)
  {
    Printer *p = Printer::makePrinter(); 
    pvec.push_back(p); 
  }

  for(int i=0; i<pvec.size(); i += 2)
  {
    delete pvec[i]; 
    pvec[i] = 0; 
  }

  for(int i=0; i<11; ++ i)
  {
     Printer *p = Printer::makePrinter(); 
     pvec.push_back(p); 
  }

  for(int i=0; i<pvec.size(); ++ i)
  {
     delete pvec[i]; 
  }

  //Printer prt; 
  return 0; 
}
