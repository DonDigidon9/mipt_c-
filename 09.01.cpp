#include <iostream>
#include <source_location>

class Tracer {
 public:
  Tracer(const std::source_location loc = std::source_location::current()) : location(loc) {
    std::cout << "IN:   Function - " << location.function_name() 
              << "\nFile - " << location.file_name() 
              << "\nLine - " << location.line() << "\n\n";
  }

  ~Tracer() {
    std::cout << "OUT:   Function - " << location.function_name() 
              << "\nFile - " << location.file_name() 
              << "\nLine - " << location.line() << "\n\n";
  }
 private:
  std::source_location location;
};

int main() {
  Tracer tracer;
  std::cout << "Hello World!\n";
  return 0;
}


// cd Рабочий\ стол/mipt_c++/Education/homework/hw_3
// g++ -std=c++20 09.01.cpp
// ./a.out
