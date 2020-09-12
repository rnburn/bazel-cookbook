#include <cassert>

void remove_gator() {
  assert(false && "won't move");
}

void remove_animals() {
  remove_gator();
}
