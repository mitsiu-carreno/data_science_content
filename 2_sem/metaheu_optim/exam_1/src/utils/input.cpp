#include "utils.hpp"

namespace utils{
  bool CheckValidInput(){
    /*
      Función para validar que el input ingresado por el usuario corresponda con el tipo de dato esperado
    */
    bool pass = true;
    if(std::cin.fail()){
      pass = false;
      // Se recupera el modo insert de stdin
      std::cin.clear();
    }
    // Se limpia el buffer de stdin
    std::cin.ignore(32767, '\n');
    return pass;
  }
}
