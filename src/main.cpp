#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <unistd.h>

std::vector<std::string> split(std::string str, std::string delimiter) {
  size_t start = 0, pos_end, delime_length = delimiter.length();
  std::string token;
  std::vector<std::string> res;

  while((pos_end = str.find(delimiter, start)) != std::string::npos){
    token = str.substr(start, pos_end - start);
    start = pos_end + delime_length;
    res.push_back(token);
  }

  res.push_back(str.substr(start));
  return res;
}

void typeCommand(std::string &input) {
  auto command = input.substr(5);
  if(command == "echo" || command == "exit" || command == "type") {
    std::cout << command <<" is a shell builtin" << std::endl;
    return;
  } else {
    std::string pathVar = std::getenv("PATH");
    std::vector<std::string> paths = split(pathVar, ":");

    for(auto path: paths){
      std::string execPath = path + "/" + command;
      if (access(execPath.c_str(), X_OK) == 0) {
        std::cout << command << " is " << execPath << std::endl;
        return;
      }
    }
  }
  std::cout << command << ": not found" << std::endl;
}

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
  std::string PS1 = "$ ";

  while(true) {
    std::cout << PS1;

    std::string input;
    std::getline(std::cin, input);

    if(input.substr(0, 5) == "type ") {
      typeCommand(input);
    }
    else if (input == "exit") {
      break;
    } else if (input.substr(0, 5) == "echo ") {
      std::cout << input.substr(5) << std::endl;
    } else {
      std::cout << input << ": command not found" << std::endl;
    }
  }
}
