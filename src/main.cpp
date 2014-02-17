#include "template.h"
#include "construct.h"

int main() {
  struct Application {
  };

  construct(literal(Application()));

  return 0;
}
