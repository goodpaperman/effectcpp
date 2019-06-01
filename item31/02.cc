
#include <iostream> 
#include <string> 
#include <vector> 
#include <list>
#include <map> 

using std::cout; 
using std::endl; 
using std::string; 
using std::vector; 
using std::list; 
using std::map; 
using std::pair; 
using std::ostream; 

class SpaceShip; 
class SpaceStation; 
class Asteriod; 
class GameObject
{
public:
  virtual ~GameObject() { }
}; 

class SpaceShip : public GameObject
{
public:
}; 

class SpaceStation : public GameObject
{
public:
}; 

class Asteriod : public GameObject
{
public:
}; 

void ShipAsteriod(GameObject&, GameObject&)
{ cout << "Ship collide with Asteriod" << endl; }
void ShipStation(GameObject&, GameObject&)
{ cout << "Ship collide with Station" << endl; }
void ShipShip(GameObject&, GameObject&)
{ cout << "Ship collide with Ship" << endl; }
void StationShip(GameObject&, GameObject&)
{ cout << "Station collide with Ship" << endl; }
void StationAsteriod(GameObject&, GameObject&)
{ cout << "Station collide with Asteriod" << endl; }
void StationStation(GameObject&, GameObject&)
{ cout << "Station collide with Station" << endl; }
void AsteriodShip(GameObject&, GameObject&)
{ cout << "Asteriod collide with Ship" << endl; }
void AsteriodStation(GameObject&, GameObject&)
{ cout << "Asteriod collide with Station" << endl;}
void AsteriodAsteriod(GameObject&, GameObject&)
{ cout << "Asteriod collide with Asteriod" << endl; }

typedef void (*HitFunctionPtr)(GameObject &, GameObject &); 
typedef map< pair<string, string>, HitFunctionPtr> HitMap; 

pair<string, string> makeStringPair(const char *s1, const char *s2)
{ return pair<string, string>(s1, s2); }

HitMap* initializeCollisionMap()
{
  HitMap *phm = new HitMap; 
  (*phm)[makeStringPair("9SpaceShip","8Asteriod")] = &ShipAsteriod; 
  (*phm)[makeStringPair("9SpaceShip","12SpaceStation")] = &ShipStation; 
  (*phm)[makeStringPair("9SpaceShip", "9SpaceShip")] = &ShipShip; 
  (*phm)[makeStringPair("12SpaceStation", "8Asteriod")] = &StationAsteriod; 
  (*phm)[makeStringPair("12SpaceStation", "9SpaceShip")] = &StationShip; 
  (*phm)[makeStringPair("12SpaceStation", "12SpaceStation")] = &StationStation; 
  (*phm)[makeStringPair("8Asteriod", "9SpaceShip")] = &AsteriodShip; 
  (*phm)[makeStringPair("8Asteriod", "12SpaceStation")] = &AsteriodStation; 
  (*phm)[makeStringPair("8Asteriod", "8Asteriod")] = &AsteriodAsteriod; 
  return phm; 
}

HitFunctionPtr lookup(const string &class1, const string &class2)
{
  static std::auto_ptr<HitMap> collisionMap(initializeCollisionMap()); 
  HitMap::iterator mapEntry = collisionMap->find(std::make_pair(class1, class2)); 
  if(mapEntry == collisionMap->end())
    return 0; 

  return mapEntry->second; 
}

void processCollision(GameObject *lhs, GameObject *rhs)
{
  //cout << lhs << " collide with " << rhs << endl; 
  HitFunctionPtr phf = lookup(typeid(*lhs).name(), typeid(*rhs).name()); 
  if(phf)
    phf(*lhs, *rhs); 
  else 
    cout << "unknown object collision: " << lhs << " and " << rhs << endl; 
}

int main()
{
  GameObject **from = new GameObject*[3]; 
  GameObject **to = new GameObject*[3]; 
  from[0] = to[0] = new SpaceShip(); 
  from[1] = to[1] = new SpaceStation(); 
  from[2] = to[2] = new Asteriod(); 

  for(int i=0; i<3; ++ i)
    for(int j=0; j<3; ++ j)
      processCollision(from[i], to[j]); 

  for(int i=0; i<3; ++ i)
    delete from[i]; 
  return 0; 
}
