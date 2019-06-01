
#include <string> 
//#include <tr1> 

template <class T>
class NamedObject {
public:
  NamedObject(std::string& name, const T& value) : 
    nameValue(name), 
    objectValue(value) {}
private:
  std::string& nameValue; 
  const T objectValue; 
}; 

int main()
{
  std::string newDog("Persephone"); 
  std::string oldDog("Satch"); 
  NamedObject<int> p(newDog, 2); 
  //NamedObject<int> s(p); 
  //s = p; 
  //std::tr1::unordered_map map<int, int> a; 
  return 0; 
}
