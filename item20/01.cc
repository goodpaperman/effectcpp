
#include <iostream> 
#include <string> 
#include <vector> 

using std::cout; 
using std::endl; 
using std::string; 
using std::vector; 


class Rational
{
public:
  Rational(int numerator = 0, int denominator = 1)
    : numerator_(numerator), denominator_(denominator)
  {
    cout << "ctor(" << numerator << "," << denominator << ")" << endl; 
  }

  ~Rational()
  {
    cout << "dtor(" << numerator_ << "," << denominator_ << ")" << endl; 
  }

  int numerator() const { return numerator_; }
  int denominator() const { return denominator_; } 

private:
  int numerator_; 
  int denominator_;  
};


const Rational operator*(const Rational &lhs, 
                         const Rational &rhs)
{
  return Rational(lhs.numerator() * rhs.numerator(), 
                  lhs.denominator() * rhs.denominator()); 
  //return result; 
} 

int main()
{
  Rational a(10); 
  Rational b(1, 2); 
  Rational c = a * b; 
  cout << c.numerator() << "," << c.denominator() << endl; 
  Rational d = a * b * c; 
  //a = a * b; 
  cout << endl; 
  return 0; 
}
