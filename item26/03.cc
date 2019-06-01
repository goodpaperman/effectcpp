
#include <iostream> 
#include <string> 
#include <vector> 

using std::cout; 
using std::endl; 
using std::string; 
using std::vector; 
using std::ostream; 

template <class T>
class CountedObj
{
public:
  static T* makeInstance(); 
  ~CountedObj() { 
    -- numObjects; 
    cout << "objects " << numObjects << " after dtor." << endl; 
  } 

  static size_t numObjects; 
  static size_t maxObjects; 
}; 

template <class T>
size_t CountedObj<T>::numObjects = 0; 

template <class T>
size_t CountedObj<T>::maxObjects = 10; 

class Printer : public CountedObj<Printer>
{
friend Printer* CountedObj<Printer>::makeInstance(); 
private:
  Printer() {}
  Printer(const Printer &rhs) {} 
}; 

template <class T>
T* CountedObj<T>::makeInstance()
{
  if(numObjects >= maxObjects)
  {
    cout << "objects " << numObjects << " exceed limit " << maxObjects << endl; 
    return 0; 
  }
  
  ++ numObjects; 
  cout << "objects " << numObjects << " after ctor." << endl; 
  return new T(); 
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
