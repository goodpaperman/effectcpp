
#include <iostream> 
#include <string> 
#include <vector> 
#include <list> 

using std::cout; 
using std::endl; 
using std::string; 
using std::vector; 
using std::list; 
using std::ostream; 

class SpaceShip; 
class SpaceStation; 
class Asteriod; 
class GameObject
{
public:
  virtual ~GameObject() { }
  virtual void collide(GameObject &rhs) = 0; 
  virtual void collide(SpaceShip &rhs) = 0; 
  virtual void collide(SpaceStation &rhs) = 0; 
  virtual void collide(Asteriod &rhs) = 0;   
}; 

class SpaceShip : public GameObject
{
public:
  virtual void collide(GameObject &rhs) { rhs.collide(*this); }
  virtual void collide(SpaceShip &rhs) 
  { cout << "SpaceShip collide with SpaceShip" << endl; }
  virtual void collide(SpaceStation &rhs) 
  { cout << "SpaceShip collide with SpaceStation" << endl; }
  virtual void collide(Asteriod &rhs) 
  { cout << "SpaceShip collide with Asteriod" << endl; }

}; 

class SpaceStation : public GameObject
{
public:
  virtual void collide(GameObject &rhs) { rhs.collide(*this); }
  virtual void collide(SpaceShip &rhs) 
  { cout << "SpaceStation collide with SpaceShip" << endl; }
  virtual void collide(SpaceStation &rhs) 
  { cout << "SpaceStation collide with SpaceStation" << endl; }
  virtual void collide(Asteriod &rhs) 
  { cout << "SpaceStation collide with Asteriod" << endl; }

}; 

class Asteriod : public GameObject
{
public:
  virtual void collide(GameObject &rhs) { rhs.collide(*this); }
  virtual void collide(SpaceShip &rhs) 
  { cout << "Asteriod collide with SpaceShip" << endl; } 
  virtual void collide(SpaceStation &rhs) 
  { cout << "Asteriod collide with SpaceStation" << endl; } 
  virtual void collide(Asteriod &rhs) 
  { cout << "Asteriod collide with Asteriod" << endl; }
}; 

void processCollision(GameObject *lhs, GameObject *rhs)
{
  //cout << lhs << " collide with " << rhs << endl; 
  rhs->collide(*lhs); 
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
