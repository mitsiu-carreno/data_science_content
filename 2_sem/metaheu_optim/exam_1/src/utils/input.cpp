#include "utils.hpp"

namespace utils{
  bool CheckValidInput(){
    bool pass = true;
    if(std::cin.fail()){
      pass = false;
      std::cin.clear();
    }
    std::cin.ignore(32767, '\n');
    return pass;
  }
}
