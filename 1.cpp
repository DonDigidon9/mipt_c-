#include <iostream>
#include <stack>
#include <cmath>
#include <regex>
#include <cassert>
#include <unordered_map>

bool isDouble(const std::string& str) {
  // Регулярное выражение для double
  std::regex double_regex(R"(^[-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?$)");
  return std::regex_match(str, double_regex);
}

class Operation {
 protected:
  int args_count;
  
 public:
  Operation(int count) : args_count(count) {}
  
  virtual double calculate(std::stack<std::string>& st) const = 0;
  virtual ~Operation() = default;
  
  int getArgsCount() const {
    return args_count;
  }
};

class Sin : public Operation {
 public:
  Sin() : Operation(1) {}
  
  double calculate(std::stack<std::string>& st) const override final {
    assert(std::size(st) >= args_count);
    double a = std::stod(st.top());
    st.pop();
    return std::sin(a);
  }
};

class Cos : public Operation {
 public:
  Cos() : Operation(1) {}
  
  double calculate(std::stack<std::string>& st) const override final {
    assert(std::size(st) >= args_count);
    double a = std::stod(st.top());
    st.pop();
    return std::cos(a);
  }
};

class Tg : public Operation {
 public:
  Tg() : Operation(1) {}
  
  double calculate(std::stack<std::string>& st) const override final {
    assert(std::size(st) >= args_count);
    double a = std::stod(st.top());
    st.pop();
    return std::tan(a);
  }
};

class Ctg : public Operation {
 public:
  Ctg() : Operation(1) {}
  
  double calculate(std::stack<std::string>& st) const override final {
    assert(std::size(st) >= args_count);
    double a = std::stod(st.top());
    st.pop();
    return 1.0 / std::tan(a);
  }
};

class Exp : public Operation {
 public:
  Exp() : Operation(1) {}
  
  double calculate(std::stack<std::string>& st) const override final {
    assert(std::size(st) >= args_count);
    double a = std::stod(st.top());
    st.pop();
    return std::exp(a);
  }
};

class Log : public Operation {
 public:
  Log() : Operation(1) {}
  
  double calculate(std::stack<std::string>& st) const override final {
    assert(std::size(st) >= args_count);
    double a = std::stod(st.top());
    st.pop();
    return std::log(a);
  }
};

class Sqrt : public Operation {
 public:
  Sqrt() : Operation(1) {}
  
  double calculate(std::stack<std::string>& st) const override final {
    assert(std::size(st) >= args_count);
    double a = std::stod(st.top());
    st.pop();
    return std::sqrt(a);
  }
};

class Sum : public Operation {
 public:
  Sum() : Operation(2) {}
  
  double calculate(std::stack<std::string>& st) const override final {
    assert(std::size(st) >= args_count);
    double a = std::stod(st.top());
    st.pop();
    double b = std::stod(st.top());
    st.pop();
    return a + b;
  }
};

class Diff : public Operation {
 public:
  Diff() : Operation(2) {}
  
  double calculate(std::stack<std::string>& st) const override final {
    assert(std::size(st) >= args_count);
    double a = std::stod(st.top());
    st.pop();
    double b = std::stod(st.top());
    st.pop();
    return b - a;
  }
};

class Prod : public Operation {
 public:
  Prod() : Operation(2) {}
  
  double calculate(std::stack<std::string>& st) const override final {
    assert(std::size(st) >= args_count);
    double a = std::stod(st.top());
    st.pop();
    double b = std::stod(st.top());
    st.pop();
    return a * b;
  }
};

class Div : public Operation {
 public:
  Div() : Operation(2) {}
  
  double calculate(std::stack<std::string>& st) const override final {
    assert(std::size(st) >= args_count);
    double a = std::stod(st.top());
    st.pop();
    double b = std::stod(st.top());
    st.pop();
    return b / a;
  }
};

class Atan2 : public Operation {
 public:
  Atan2() : Operation(2) {}
  
  double calculate(std::stack<std::string>& st) const override final {
    assert(std::size(st) >= args_count);
    double a = std::stod(st.top());
    st.pop();
    double b = std::stod(st.top());
    st.pop();
    return std::atan2(b, a);
  }
};

class Pow : public Operation {
 public:
  Pow() : Operation(2) {}
  
  double calculate(std::stack<std::string>& st) const override final {
    assert(std::size(st) >= args_count);
    double a = std::stod(st.top());
    st.pop();
    double b = std::stod(st.top());
    st.pop();
    return std::pow(b, a);
  }
};

class Median : public Operation {
 public:
  Median() : Operation(3) {}
  
  double calculate(std::stack<std::string>& st) const override final {
    assert(std::size(st) >= args_count);
    double a = std::stod(st.top());
    st.pop();
    double b = std::stod(st.top());
    st.pop();
    double c = std::stod(st.top());
    st.pop();
    if ((a <= b && b <= c) || (c <= b && b <= a)) return b;
    if ((b <= a && a <= c) || (c <= a && a <= b)) return a;
    return c;
  }
};

class Calculator {
 private:
  std::unordered_map<std::string, std::unique_ptr<Operation>> operations_;
  std::stack<std::string> st;
  
 public:
  Calculator() {
    operations_["sin"] = std::unique_ptr<Operation>(new Sin());
    operations_["cos"] = std::unique_ptr<Operation>(new Cos());
    operations_["tg"] = std::unique_ptr<Operation>(new Tg());
    operations_["ctg"] = std::unique_ptr<Operation>(new Ctg());
    operations_["exp"] = std::unique_ptr<Operation>(new Exp());
    operations_["log"] = std::unique_ptr<Operation>(new Log());
    operations_["sqrt"] = std::unique_ptr<Operation>(new Sqrt());
    operations_["+"] = std::unique_ptr<Operation>(new Sum());
    operations_["-"] = std::unique_ptr<Operation>(new Diff());
    operations_["*"] = std::unique_ptr<Operation>(new Prod());
    operations_["/"] = std::unique_ptr<Operation>(new Div());
    operations_["atan2"] = std::unique_ptr<Operation>(new Atan2());
    operations_["pow"] = std::unique_ptr<Operation>(new Pow());
    operations_["median"] = std::unique_ptr<Operation>(new Median());
  }
  
  double calculate(const std::string& expression) {
    size_t start = 0;
    size_t end = 0;
    
    while (end < expression.size()) {
      while (start < expression.size() && expression[start] == ' ') {
        start++;
      }
      
      if (start >= expression.size()) break;
      
      end = start;
      while (end < expression.size() && expression[end] != ' ') {
        end++;
      }
      
      std::string token = expression.substr(start, end - start);
      auto it = operations_.find(token);
      if (it != operations_.end()) {
        assert(std::size(st) >= it->second->getArgsCount());
        double result = it->second->calculate(st);
        st.push(std::to_string(result));
      } else {
        assert(isDouble(token));
        st.push(token);
      }
      
      start = end;
    }
    
    assert(std::size(st) == 1);
    double result = std::stod(st.top());
    
    return result;
  }
};

bool equal(double x, double y) {
  return fabs(x - y) < 0.0001;
}

void test1() {
  Calculator calc;
  double result = calc.calculate("5 3 +");
  assert(equal(result, 8.0));
}

void test2() {
  Calculator calc;
  double result = calc.calculate("10 4 -");
  assert(equal(result, 6.0));
}

void test3() {
  Calculator calc;
  double result = calc.calculate("3 7 *");
  assert(equal(result, 21.0));
}

void test4() {
  Calculator calc;
  double result = calc.calculate("15 3 /");
  assert(equal(result, 5.0));
}

void test5() {
  Calculator calc;
  double result = calc.calculate("2 3 4 + *");
  assert(equal(result, 14.0));
}

int main() {
  // Calculator calculator;
  // std::string expression;
  // std::cout << "Введите выражение: ";
  // std::getline(std::cin, expression);
  // double result = calculator.calculate(expression);
  // std::cout << "Результат: " << result << '\n';

  test1();
  test2();
  test3();
  test4();
  test5();
  
  return 0;
}
