
#include <iostream> 
#include <string> 
#include <vector> 

using std::cout; 
using std::endl; 
using std::string; 
using std::vector; 
using std::ostream; 


class Printer; 
class CountedObj 
{
public:
  static Printer* makeInstance(); 
  ~CountedObj() { 
    -- numObjects; 
    cout << "objects " << numObjects << " after dtor." << endl; 
  } 

  static size_t numObjects; 
  static size_t maxObjects; 
}; 

size_t CountedObj::numObjects = 0; 
size_t CountedObj::maxObjects = 10; 

class Printer : public CountedObj
{
friend Printer* CountedObj::makeInstance(); 
private:
  Printer() {}
  Printer(const Printer &rhs) {} 
}; 

Printer* CountedObj::makeInstance()
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
    Printer *p = Printer::makeInstance(); 
    pvec.push_back(p); 
  }

  for(int i=0; i<pvec.size(); i += 2)
  {
    delete pvec[i]; 
    pvec[i] = 0; 
  }

  for(int i=0; i<11; ++ i)
  {
     Printer *p = Printer::makeInstance(); 
     pvec.push_back(p); 
  }

  for(int i=0; i<pvec.size(); ++ i)
  {
     delete pvec[i]; 
  }

  //Printer p; 
  return 0; 
}
