
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

template <typename T>
class Array2D
{
public:
  class Array1D
  {
  public:
    Array1D() : arr(0) {}
    ~Array1D() { delete[] arr; }
    void SetDim(int dim) { arr = new T[dim]; }
    T& operator[] (int index) { return arr[index]; }
    const T& operator[] (int index) const { return arr[index]; }
  private:
    T *arr;
  };

public:
  Array2D(int dim1, int dim2) {
    arr = new Array1D[dim1]; 
    for(int i=0; i<dim1; ++ i)
      arr[i].SetDim(dim2); 
  }

  ~Array2D() { delete []arr; }
  Array1D& operator[] (int index) { return arr[index]; } 
  const Array1D& operator[] (int index) const 
  { return arr[index]; } 

private:
  Array1D *arr; 
}; 

int main()
{
  Array2D<int> arr(10, 20); 
  for(int i=0; i<10; ++ i)
    for(int j=0; j<20; ++ j)
      arr[i][j] = i * j; 

  cout << arr[3][6] << endl; 
  return 0; 
}
