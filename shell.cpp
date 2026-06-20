/*
  basic replica of bash shell
  to do: add simple builtins (cd), add tab completion, and add command history
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <cstring>

// function used to execute commands
void execCommand(char *cmd, char *ptr[]) {
  if (strcmp(cmd, "exit") == 0) {
    exit(EXIT_SUCCESS);
  }
    
  pid_t pid = fork();

  if (pid < 0) {
    std::cerr << "fork failed\n";
  } else if (pid == 0) {
    execvp(cmd, ptr);
    std::cerr << "execvp failed\n";
    exit(1);
  }
  waitpid(pid, NULL, 0);
}

// function used to parse the command into a vector
std::vector<char*> parseCommand(char *cmd) {
  char *token = std::strtok(cmd, " ");
  std::vector<char *> random_vec;
  while (token != nullptr) {
    random_vec.push_back(token);
    token = std::strtok(nullptr, " ");
  }

  // null terminate vector before converting
  random_vec.push_back(nullptr);

  return random_vec;
}

int main() {
  char *cmd = new char[128];
  
  while (1) {
    std::cout << "> ";
    std::cin.getline(cmd, 128);
    std::vector<char *> parsed_cmd = parseCommand(cmd);
    auto *ptr = parsed_cmd.data(); // converting vect into pointer (char array) to pass to execvp in execCommand
    execCommand(ptr[0], ptr);
  }

  delete[] cmd;

  return 0;
}
