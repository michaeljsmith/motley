#include "template.h"
#include "construct.h"

#include <iostream>
#include <memory>

using std::shared_ptr;
using std::make_shared;

int main() {
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
