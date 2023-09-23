#include "utils.hpp"

namespace utils{

  void AskValue(std::string prompt, void *variable, kDataTypes type){
    /*
      Función para solicitar un input al usuario
      Input: 
        std::string - Mensaje describiendo la información requerida
        void * - Apuntador a la variable para almacenar el input
        kDataTypes - Tipo de dato que se solicita
    */

    while(true){
      // Se crea una variable local para cada tipo de dato permitido
      int n_value;
      std::string s_value;
      float f_value;
      
      // Se muestra en pantalla la descripción provista
      std::cout << prompt << ": ";
      switch(type){
        case kInteger:
          std::cin >> n_value;
          // Para valores númericos se verifica el input
          if(!utils::CheckValidInput()){
            std::cout << "Número invalido\n";
            continue;
          }
          // Se guarda el dato en el apuntador provisto
          *static_cast<int*>(variable) = n_value;
          break;
        case kString:
          std::getline(std::cin, s_value);
          // Se guarda el dato en el apuntador provisto
          *static_cast<std::string*>(variable) = s_value;
          break;
        case kFloat:
          std::cin >> f_value;
          // Para valores númericos se verifica el input
          if(!utils::CheckValidInput()){
            std::cout << "Número invalido\n";
            continue;
          }
          // Se guarda el dato en el apuntador provisto
          *static_cast<float*>(variable) = f_value;
          break;
        default:
          std::cout << "Error interno\n";
      }
      return;
    }
  }
}
