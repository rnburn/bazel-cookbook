#include <iostream>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
  auto line = readline("> ");
  add_history(line);
  std::cout << "line: " << line << "\n";
  return 0;
}
