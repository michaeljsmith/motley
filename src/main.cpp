#include "template.h"
#include "construct.h"

#include <iostream>

int main() {
  struct Application {
    void run() {std::cout << "Application running\n";}
  };

  //auto app = construct(literal(Application()));

  Environment environment;
  push(environment, "var", Application());
  auto app = construct(environment, variableReference<Application>("var"));

  app.run();

  return 0;
}
