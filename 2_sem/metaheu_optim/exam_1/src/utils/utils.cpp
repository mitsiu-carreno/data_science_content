
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
  
  std::mt19937 RandomFunction(){
    // Generamos un número aleatorio básado en hardware o una implementación de software 
    // si el hardware no tiene una implementación disponible
    std::random_device rd;
    
    // Generamos un número aleatorio con el algoritmo Mersenne Twister PRNG
    // con el seed del random_device
    std::mt19937 g(rd()); 
    return g;
  }

  int RandomInInterval(int lower, int upper){
    std::mt19937 g = utils::RandomFunction();
    std::uniform_int_distribution bounds{ lower, upper };
    return bounds(g);
    //return 3;
  }
}
