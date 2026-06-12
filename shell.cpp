#include <iostream>
#include <string>

void prompt() {
  char *cmd = new char[128];
  std::cout << "> ";
  std::cin.getline(cmd, 128);
}

int main() {
  prompt();
  return 0;
}
