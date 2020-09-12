#include "backtrace.h"
#include "runway.h"

static void fire_rocket() {
  clear_runway();
}

int main() {
  setup_backtrace();
  fire_rocket();
  return 0;
}
