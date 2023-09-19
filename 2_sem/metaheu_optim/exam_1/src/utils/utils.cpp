#include "utils.hpp"

namespace utils{
  int GetFactorial(int n){
    /*  
      Función para obtener el factorial de un número n
      Input:
        int n - Número del que queremos obtener su factorial
      Output:
        int - Número factorial de n
    */

    if(n==0){
      return 1;
    }
    // Recursividad is in the house
    return n * GetFactorial(n-1);
  } 
}
