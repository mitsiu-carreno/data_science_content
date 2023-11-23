#ifndef GEN_RANDOM_HPP
#define GEN_RANDOM_HPP

#include <random>   /* std::mt19937 std::random_device */

namespace utils{
  std::mt19937 GenRandomFunction();
  int RandomInInterval(int, int);
}

#endif
