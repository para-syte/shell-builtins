#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void execCommand(char *cmd, char *argv[]) {
  pid_t pid = fork();

  if (pid < 0) {
    std::cerr << "fork failed\n";
  } else if (pid == 0) {
    execvp(cmd, argv);
    std::cerr << "execvp failed\n";
    exit(1);
  }
  waitpid(pid, NULL, 0);
}

int main(int argc, char *argv[]) {
  char *cmd = new char;
  char *args = new char[32];
  
  while (1) {
    std::cout << "> ";
    std::cin.getline(cmd, 128);
    execCommand(cmd, argv);
  }

  delete cmd;

  return 0;
}
