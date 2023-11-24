#include "gen-random.hpp"

namespace utils{
  std::mt19937 GenRandomFunction(){
    // Generamos un número aleatorio básado en hardware o una implementación de software
    // si el hardware no tiene una implementación disponible
    std::random_device rd;

    // Generamos un número aleatorio con el algoritmo Mersenne Twister PRNG
    // con el seed del random_device
    std::mt19937 g(rd());
    return g;
  }

  int RandomInInterval(int lower, int upper){
    // Solictamos el algoritmo generador de aleatorios
    std::mt19937 g = utils::GenRandomFunction();
    // Restringimos el resultado al rango provisto
    std::uniform_int_distribution bounds{ lower, upper};
    return bounds(g);
  }
}
