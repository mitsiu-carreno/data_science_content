#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>   /* std::cin */
#include <string>
#include <random>     /* std::mt19937 std::random_device */ 

#include "problem-metadata.hpp"

namespace utils{
  // Enumerador de tipos de datos validos para que ingrese el usuario
  enum kDataTypes{
    kInteger,
    kString,
    kFloat
  };

  bool CheckValidInput();
  void AskValue(std::string, void*, kDataTypes);
  int GetFactorial(int);
  std::mt19937 RandomFunction();
  int RandomInInterval(int, int);
}

#endif
