#include <iostream>
#include <string>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
  std::string PS1 = "$ ";

  while(true) {
    std::string command;
    std::cout << PS1;
    std::cin >> command;

    if(command == "exit") {
      // Exit the shell
      break;
    }

    std::cout << command << ": command not found" << std::endl;
  }
}