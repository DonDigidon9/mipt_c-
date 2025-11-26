#include <iostream>
#include <array>
#include <cstdint>
#include <cassert>

class IPv4 {
 public:
  IPv4() : adress{0, 0, 0, 0} {}
  
  IPv4(std::uint8_t a, std::uint8_t b, std::uint8_t c, std::uint8_t d) 
    : adress{a, b, c, d} {}


  IPv4& operator++() {
    for (int i = 3; i >= 0; --i) {
      if (adress[i] < 255) {
        ++adress[i];
        return *this;
      } else {
        adress[i] = 0;
      }
    }
    return *this;
  }

  IPv4 operator++(int) {
    IPv4 temp = *this;
    ++(*this);
    return temp;
  }

  IPv4& operator--() {
    for (int i = 3; i >= 0; --i) {
      if (adress[i] > 0) {
        --adress[i];
        return *this;
      } else {
        adress[i] = 255;
      }
    }
    return *this;
  }

  IPv4 operator--(int) {
    IPv4 temp = *this;
    --(*this);
    return temp;
  }

  friend bool operator==(const IPv4& first, const IPv4& second) {
    return first.adress == second.adress;
  }

  friend bool operator!=(const IPv4& first, const IPv4& second) {
    return !(first == second);
  }

  friend bool operator<(const IPv4& first, const IPv4& second) {
    return first.adress < second.adress;
  }

  friend bool operator>(const IPv4& first, const IPv4& second) {
    return second < first;
  }

  friend bool operator<=(const IPv4& first, const IPv4& second) {
    return !(second < first);
  }

  friend bool operator>=(const IPv4& first, const IPv4& second) {
    return !(first < second);
  }

  friend std::ostream& operator<<(std::ostream& os, const IPv4& ip);

  friend std::istream& operator>>(std::istream& is, IPv4& ip);
 private:
  std::array<std::uint8_t, 4> adress;
};

std::ostream& operator<<(std::ostream& os, const IPv4& ip) {
  os << int(ip.adress[0]) << '.' 
    << int(ip.adress[1]) << '.' 
    << int(ip.adress[2]) << '.' 
    << int(ip.adress[3]);
  return os;
}

std::istream& operator>>(std::istream& is, IPv4& ip) {
  int a, b, c, d;
  char dot1, dot2, dot3;
  
  is >> a >> dot1 >> b >> dot2 >> c >> dot3 >> d;

  assert(dot1 == '.' and dot2 == '.' and dot3 == '.' and
         a >= 0 and a <= 255 and b >= 0 and b <= 255 and 
         c >= 0 and c <= 255 and d >= 0 and d <= 255);

  ip.adress[0] = static_cast<std::uint8_t>(a);
  ip.adress[1] = static_cast<std::uint8_t>(b);
  ip.adress[2] = static_cast<std::uint8_t>(c);
  ip.adress[3] = static_cast<std::uint8_t>(d);
  
  return is;
}

int main() {
    IPv4 ip1;
    std::cout << "Default IP: " << ip1 << '\n' << '\n';
    
    IPv4 ip2(123, 234, 1, 255);
    std::cout << "Initialized IP: " << ip2 << '\n' << '\n';
    
    ++ip2;
    std::cout << "Prefix increment: " << ip2 << '\n';
    
    IPv4 ip3 = ip2++;
    std::cout << "Postfix increment - returned: " << ip3 << '\n';
    std::cout << "Postfix increment - current: " << ip2 << '\n' << '\n';

    --ip2;
    std::cout << "Prefix dicrement: " << ip2 << '\n';
    
    IPv4 ip5 = ip2--;
    std::cout << "Postfix dicrement - returned: " << ip5 << '\n';
    std::cout << "Postfix dicrement - current: " << ip2 << '\n' << '\n';
    
    IPv4 ip4;
    std::cout << "Enter IP adress: ";
    std::cin >> ip4;
    std::cout << "You entered: " << ip4 << '\n';
    
    return 0;
}

// cd Рабочий\ стол/mipt_c++/Education/homework/hw_3
// g++ -std=c++20 03.09.cpp
// ./a.out
