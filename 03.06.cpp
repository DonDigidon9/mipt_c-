#include <iostream>
#include <cmath>
#include <vector>
#include <cassert>

const double pi = M_PI;
const double EPS = 1e-6;

bool equal(double a, double b) {
  return abs(a - b) < EPS;
}

class Shape {
 public:
  virtual double perimeter() const = 0;

  virtual double area() const = 0;

  virtual void getName() const = 0;

  virtual ~Shape() = default;
};


class Triangle : public Shape {
 public:
  Triangle(double x, double y, double z) : a(x), b(y), c(z) {}

  double perimeter() const override final {
    return a + b + c;
  }

  double area() const override final {
    double p = (a + b + c) / 2;
    return std::pow(p * (p - a) * (p - b) * (p - c), 0.5);
  }

  void getName() const override final {
    std::cout << "Triangle : ";
  }

 private:
  double a{}, b{}, c{};
};

class Square final : public Shape {
 public:
  Square(double x) : a(x) {}

  double perimeter() const override {
    return 4 * a;
  }

  double area() const override {
    return a * a;
  }

  void getName() const override {
    std::cout << "Square : ";
  }

 private:
  double a{};
};


class Circle final : public Shape {
 public:
  Circle(double value) : r(value) {}

  double perimeter() const override {
    return 2 * pi * r;
  }

  double area() const override {
    return pi * r * r;
  }

  void getName() const override {
    std::cout << "Circle : ";
  }

 private:
  double r{};
};

int main() {
  std::vector<Shape*> shapes;

  // Triangles
  shapes.push_back(new Triangle(3.0, 4.0, 5.0));
  shapes.push_back(new Triangle(5.0, 5.0, 5.0));
  shapes.push_back(new Triangle(6.0, 8.0, 10.0));
  shapes.push_back(new Triangle(7.0, 8.0, 9.0));
  shapes.push_back(new Triangle(2.0, 3.0, 4.0));

  // Squares
  shapes.push_back(new Square(1.0));
  shapes.push_back(new Square(5.0));
  shapes.push_back(new Square(2.5));
  shapes.push_back(new Square(10.0));
  shapes.push_back(new Square(0.5));

  // Circles
  shapes.push_back(new Circle(1.0));
  shapes.push_back(new Circle(5.0));
  shapes.push_back(new Circle(2.5));
  shapes.push_back(new Circle(10.0));
  shapes.push_back(new Circle(0.5));
  
  std::vector<std::pair<double, double>> test = {
    // Triangles
    {12.0, 6.0},
    {15.0, 10.825317},
    {24.0, 24.0},
    {24.0, 26.832815},
    {9.0, 2.904737},
    
    // Squares
    {4.0, 1.0},
    {20.0, 25.0},
    {10.0, 6.25},
    {40.0, 100.0},
    {2.0, 0.25},
    
    // Circles
    {6.283185, 3.141592},
    {31.415926, 78.539816},
    {15.707963, 19.634954},
    {62.831853, 314.159265},
    {3.141592, 0.785398}
  };

  for (size_t i = 0; i < shapes.size(); ++i) {
      double my_perimeter = shapes[i]->perimeter();
      double my_area = shapes[i]->area();
      double test_perimeter = test[i].first;
      double test_area = test[i].second;
      
      assert(equal(my_perimeter, test_perimeter));
      assert(equal(my_area, test_area));
  }

  // for (size_t i = 0; i < std::size(shapes); ++i) {
  //   Shape* shape = shapes[i];
  //   shape->getName();
  //   std::cout << "perimeter = " << shape->perimeter() << ", area = " << shape->area() << '\n';
  // }

  return 0;
}
