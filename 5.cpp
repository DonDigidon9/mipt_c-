#include <iostream>
#include <vector>
#include <cassert>

class Vector {
 private:
  int size;
  std::vector<double> mas = {1, 2, 3, 4, 5};
 public:
  Vector(int length) : size(length) {
    assert(size > 0);
    mas.reserve(size);
  }

  Vector(const Vector& origin) : size(origin.size), mas(origin.mas) {}

  double& operator[](int x) {
    assert(x >= 0 and x < size);
    return mas[x];
  }

  Vector& operator=(Vector a) {
    assert(a.size() == size);
    mas = a.mas;
    return *this;
  }
};

int main() {
  Vector a(5);

  a[3] = 2;

  std::cout << a[3] << "\n";
  std::cout << "Hello World" << "\n";

  return 0;
}
