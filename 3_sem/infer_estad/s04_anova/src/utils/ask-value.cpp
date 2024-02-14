#include "utils.hpp"

namespace utils{
  void AskValue(std::string prompt, void *variable, kDataTypes type){
    while(true){
      int n_value;
      std::string s_value;
      float f_value;

      std::cout << prompt << ": ";
      switch(type){
        case kInteger:
          std::cin >> n_value;
          if(!utils::CheckValidInput()){
            std::cout << "Número entero invalido\n";
            continue;
          }
          *static_cast<int*>(variable) = n_value;
          break;

        case kString:
          std::getline(std::cin, s_value);
          *static_cast<std::string*>(variable) = s_value;
          break;
        
        case kFloat:
          std::cin >> f_value;
          if(!utils::CheckValidInput()){
            std::cout << "Número decimal inválido\n";
            continue;
          }
          *static_cast<float*>(variable) = f_value;
          break;
        default:
          std::cout << "Error interno\n";
      }
      return;
    }
  }
}
