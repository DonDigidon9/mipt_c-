#include <iostream>
#include <stack>
#include <cmath>
#include <regex>
#include <cassert>

bool isDouble(const std::string& str) {
    // Регулярное выражение для double
    std::regex double_regex(R"(^[-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?$)");
    return std::regex_match(str, double_regex);
}

class Operation {
 public:
  virtual double calculate(std::stack<std::string>& st) const = 0;
  virtual ~Operation() = default;
};

class Sin : public Operation {
 public:
  double calculate(std::stack<std::string>& st) const override final {
    assert(std::size(st) >= 1);
    double a;
    a = std::stod(st.top());
    st.pop();
    return std::sin(a);
  }
};

class Cos : public Operation {
 public:
  double calculate(std::stack<std::string>& st) const override final {
    assert(std::size(st) >= 1);
    double a;
    a = std::stod(st.top());
    st.pop();
    return std::cos(a);
  }
};

class Tg : public Operation {
 public:
  double calculate(std::stack<std::string>& st) const override final {
    assert(std::size(st) >= 1);
    double a;
    a = std::stod(st.top());
    st.pop();
    return std::tan(a);
  }
};

class Ctg : public Operation {
 public:
  double calculate(std::stack<std::string>& st) const override final {
    assert(std::size(st) >= 1);
    double a;
    a = std::stod(st.top());
    st.pop();
    return 1.0 / std::tan(a);
  }
};

class Exp : public Operation {
 public:
  double calculate(std::stack<std::string>& st) const override final {
    assert(std::size(st) >= 1);
    double a;
    a = std::stod(st.top());
    st.pop();
    return std::exp(a);
  }
};

class Log : public Operation {
 public:
  double calculate(std::stack<std::string>& st) const override final {
    assert(std::size(st) >= 1);
    double a;
    a = std::stod(st.top());
    st.pop();
    return std::log(a);
  }
};

class Sqrt : public Operation {
 public:
  double calculate(std::stack<std::string>& st) const override final {
    assert(std::size(st) >= 1);
    double a;
    a = std::stod(st.top());
    st.pop();
    return std::sqrt(a);
  }
};

class Sum : public Operation {
 public:
  double calculate(std::stack<std::string>& st) const override final {
    assert(std::size(st) >= 2);
    double a, b;
    a = std::stod(st.top());
    st.pop();
    b = std::stod(st.top());
    st.pop();
    return a + b;
  }
};

class Diff : public Operation {
 public:
  double calculate(std::stack<std::string>& st) const override final {
    assert(std::size(st) >= 2);
    double a, b;
    a = std::stod(st.top());
    st.pop();
    b = std::stod(st.top());
    st.pop();
    return b - a;
  }
};

class Prod : public Operation {
 public:
  double calculate(std::stack<std::string>& st) const override final {
    assert(std::size(st) >= 2);
    double a, b;
    a = std::stod(st.top());
    st.pop();
    b = std::stod(st.top());
    st.pop();
    return a * b;
  }
};

class Div : public Operation {
 public:
  double calculate(std::stack<std::string>& st) const override final {
    assert(std::size(st) >= 2);
    double a, b;
    a = std::stod(st.top());
    st.pop();
    b = std::stod(st.top());
    st.pop();
    return b / a;
  }
};

class Atan2 : public Operation {
 public:
  double calculate(std::stack<std::string>& st) const override final {
    assert(std::size(st) >= 2);
    double a, b;
    a = std::stod(st.top());
    st.pop();
    b = std::stod(st.top());
    st.pop();
    return std::atan2(b, a);
  }
};

class Pow : public Operation {
 public:
  double calculate(std::stack<std::string>& st) const override final {
    assert(std::size(st) >= 2);
    double a, b;
    a = std::stod(st.top());
    st.pop();
    b = std::stod(st.top());
    st.pop();
    return std::pow(b, a);
  }
};

int main() {
  Sin sin;
  Cos cos;
  Tg tg;
  Ctg ctg;
  Exp exp;
  Log log;
  Sqrt sqrt;
  Sum sum;
  Diff diff;
  Prod prod;
  Div div;
  Atan2 atan2;
  Pow pow;

  std::stack<std::string> st;
  std::string x;
  while (std::cin >> x) {
    if (x == "sin") {
      double t = sin.calculate(st);
      std::cout << t << '\n';
      st.push(std::to_string(t));
    } else if (x == "cos") {
      double t = cos.calculate(st);
      std::cout << t << '\n';
      st.push(std::to_string(t));
    } else if (x == "tg") {
      double t = tg.calculate(st);
      std::cout << t << '\n';
      st.push(std::to_string(t));
    } else if (x == "ctg") {
      double t = ctg.calculate(st);
      std::cout << t << '\n';
      st.push(std::to_string(t));
    } else if (x == "exp") {
      double t = exp.calculate(st);
      std::cout << t << '\n';
      st.push(std::to_string(t));
    } else if (x == "log") {
      double t = log.calculate(st);
      std::cout << t << '\n';
      st.push(std::to_string(t));
    } else if (x == "sqrt") {
      double t = sqrt.calculate(st);
      std::cout << t << '\n';
      st.push(std::to_string(t));
    } else if (x == "+") {
      double t = sum.calculate(st);
      std::cout << t << '\n';
      st.push(std::to_string(t));
    } else if (x == "-") {
      double t = diff.calculate(st);
      std::cout << t << '\n';
      st.push(std::to_string(t));
    } else if (x == "*") {
      double t = prod.calculate(st);
      std::cout << t << '\n';
      st.push(std::to_string(t));
    } else if (x == "/") {
      double t = div.calculate(st);
      std::cout << t << '\n';
      st.push(std::to_string(t));
    } else if (x == "atan2") {
      double t = atan2.calculate(st);
      std::cout << t << '\n';
      st.push(std::to_string(t));
    } else if (x == "pow") {
      double t = pow.calculate(st);
      std::cout << t << '\n';
      st.push(std::to_string(t));
    } else {
      assert(isDouble(x) and x.size() > 0);
      st.push(x);
    }
  }
  
  std::cout << sum.calculate(st) << '\n';

  return 0;
}
