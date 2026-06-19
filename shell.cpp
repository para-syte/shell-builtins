/*
  basic replica of bash shell
  to do: need to convert parsed vector into char array to be able to pass into execvp
 */

#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <cstring>

// function used to execute commands given
// right now can only execute first command and not arguments
void execCommand(char *cmd, char *ptr[]) {
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

// function used to parse the command initially typed into a vector
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
    // HERE: convert vector to char array
    auto *ptr = parsed_cmd.data();
    execCommand(ptr[0], ptr);
  }

  delete[] cmd;

  return 0;
}
