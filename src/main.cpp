#include "expression.h"
#include "construct.h"
#include "adhoc.h"

#include <iostream>
#include <memory>

using std::shared_ptr;
using std::make_shared;

template <typename F> struct A : F {
  A(F f): F(f) {}

  using F::operator();
};

template <typename F> A<F> foo(F f) {
  return A<F>(f);
}

int main() {

  //int result = 0;
  //auto x = foo([&result]() {result = 1; std::cout << "blah\n";});
  //x();
  //std::cout << result << "\n";

  auto f = adhoc(
      []() {std::cout << "foo\n";},
      [](int x) {std::cout << "integer " << x << "\n";},
      [](double x) {std::cout << "double " << x << "\n";},
      [](std::string x) {std::cout << "string " << x << "\n";});
  f();
  f("foo");
  f(4.0);
  f(3);

  struct Application {
    void run() {std::cout << "Application running\n";}
  };

  //auto app = construct(literal(Application()));

  Environment environment;
  push(environment, "var", make_shared<Application>());
  auto app = construct(environment, variableReference<shared_ptr<Application>>("var"));

  app->run();

  return 0;
}
