#include <random>     /* std::mt19937 std::random_device */ 
#include <algorithm>  /* std::shuffle */
#include "travel-path.hpp"

#include <iostream> // debug

namespace travel_path{
  
  void GenRandomSol(int &n_cities, int &n_solutions){
    /*
      Función para generar n distintas soluciones de camino
      Input: 
        int &n_cities - Cantidad de ciudades disponibles
        int &n_solutions - Cantidad de soluciones distintas esperadas
      Output:
    */
  
    // Generamos una solución ordenada (1,2,3,4,5 ... n_cities)
    // Hasta ahora suponemos que cada ciudad se conecta con todas las demás
    // y que el caminó de ida tiene la misma distancia que el camino de regreso
    int *base_solution = new int[n_cities];
    for(int i=0; i<n_cities; ++i){
      base_solution[i] = i+1;
    }

    // Partiendo de la solución base, generamos nuevas soluciones random 
    
    // Generamos un número aleatorio básado en hardware o una implementación de software 
    // si el hardware no tiene una implementación disponible
    std::random_device rd;
    
    // Generamos un número aleatorio con el algoritmo Mersenne Twister PRNG
    // con el seed del random_device
    std::mt19937 g(rd()); 


    // Aleatorizamos los elementos de la solución base [start, end, función de randomizado)
    std::shuffle(&base_solution[0], &base_solution[n_cities], g);

    std::cout << "Base solution:\n";
    for(int i=0; i<n_cities; ++i){
      std::cout << base_solution[i] << "\t";
    }
    
    // Guardar en unordered set
    // Sort parcial
  }
}
