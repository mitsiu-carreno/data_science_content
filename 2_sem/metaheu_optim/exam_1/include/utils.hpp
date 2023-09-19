#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <string>

namespace utils{
  enum kDataTypes{
    kInteger,
    kString,
    kFloat
  };

  bool CheckValidInput();
  void AskValue(std::string, void*, kDataTypes);
  int GetFactorial(int);
}

#endif
