#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <iostream>

namespace utils{
  enum kDataTypes{
    kInteger,
    kString,
    kFloat
  };

  bool CheckValidInput();
  void AskValue(std::string, void*, kDataTypes);
}

#endif
