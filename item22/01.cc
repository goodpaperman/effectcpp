
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

  Rational& operator+=(const Rational &rhs)
  {
    cout << "Rational +=" << endl; 
    numerator_ += rhs.numerator(); 
    denominator_ += rhs.denominator(); 
  }

private:
  int numerator_; 
  int denominator_;  
};


template <typename T>
const T operator+(const T &lhs, 
                  const T &rhs)
{
  cout << "T + " << endl; 
  //return T(lhs) += rhs;  
  T result(lhs); 
  return result += rhs; 
} 

const Rational operator+(const Rational &lhs, 
                         const Rational &rhs)
{
  cout << "Rational +" << endl; 
  return Rational(lhs) += rhs; 
}

int main()
{
  Rational a(10); 
  Rational b(1, 2); 
  Rational c = a + b; 
  cout << c.numerator() << "," << c.denominator() << endl; 
  Rational d = a + b + c; 
  //a = a * b; 
  cout << endl; 
  return 0; 
}
