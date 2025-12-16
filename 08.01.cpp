#include <iostream>
#include <cassert>

int log2(int x) {
  assert(x > 0);
  unsigned int num = static_cast<unsigned int>(x);
  int res{};
  while (num > 1) {
      num >>= 1;
      ++res;
  }
  return res;
}

int log2(float x) {
  assert(x > 0.0);
  union {
    float fractional;
    unsigned int integer;
  } num;

  num.fractional = x;
  unsigned int bits = num.integer;
  
  unsigned int exp = (bits & 0x7F800000) >> 23;
  
  if (exp == 0xFF) {
    if (bits & 0x007FFFFF) {
      std::cout << "NaN" << '\n';
      return 0;
    } else {
      std::cout << "Inf" << '\n';
      return 0;
    }
  }
  
  if (exp == 0) {
    int int_val = static_cast<int>(x);
    return log2(int_val);
  }
  return static_cast<int>(exp) - 127;
}

int main() {
  // assert(log2(-1));
  assert(log2(16) == 4);
  assert(log2(5) == 2);
  assert(log2(9.0f) == 3);
  assert(log2(0.25f) == -2);
  assert(log2(4.0f) == 2);
}
