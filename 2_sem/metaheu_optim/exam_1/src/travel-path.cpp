#include <random>     /* std::mt19937 std::random_device */ 
#include <algorithm>  /* std::shuffle std::swap*/
#include <vector>     /* std::vector */
#include <stdexcept>  /* std::runtime_error */

#include "travel-path.hpp"

namespace travel_path{
  
  void GenRandomSol(int &n_cities, int &n_solutions, std::set<travel_path::Solution, travel_path::SolutionCompare> &solutions){
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
    std::vector<int> base_solution(n_cities);
    for(int i=0; i<n_cities; ++i){
      base_solution.at(i) = i+1;
    }

    // Partiendo de la solución base, generaremos nuevas soluciones random 
    
    // Generamos un número aleatorio básado en hardware o una implementación de software 
    // si el hardware no tiene una implementación disponible
    std::random_device rd;
    
    // Generamos un número aleatorio con el algoritmo Mersenne Twister PRNG
    // con el seed del random_device
    std::mt19937 g(rd()); 

    while(static_cast<int>(solutions.size()) < n_solutions){
      // Aleatorizamos los elementos de la solución base [start, end, función de randomizado)
      std::shuffle(base_solution.begin(), base_solution.end(), g);

      solutions.insert({std::vector<int>(base_solution), EvalSolution(base_solution)});

    }
  }

  float EvalSolution(const std::vector<int> &path){
    /*
      Función para obtener la distancia dado un camino recibido
      Input:
        const std::vector<int> & - Referencia al vector que contiene la ruta de ciudades
      Output:
        float - Distancia después de recorrer la ruta de ciudades
    */
    
    // Acumulamos la distancia recorrida
    float acc = 0;
    // Iteramos del principo del vector a la penúltima ciudad
    for (auto i = path.begin(); i < path.end()-1; ++i) {
      // Evaluamos la distancia entre la ciudad actual y la siguiente ciudad en la ruta
      acc +=GetDistance(i[0], i[1], nullptr, 1);
    }
    return acc;
  }

  float GetDistance(int city_A, int city_B, float *pcity_distances = nullptr, int pn_cities = 1){
    /*
      Función para obtener la distancia entre dos ciudades dadas
      Input:
        int city_A - Identificador de ciudad A [1, n_cities]
        int city_B - Identificador de ciudad B [1, n_cities]
        float *city_distances - Arreglo unidimensional de todas las distancias entre ciudades
        int &n_cities - Total de ciudades existentes
      Output:
        float  - Distancia entre las ciudades ingresadas
    */

    // Store array in internal function state
    static const float *city_distances = pcity_distances;
    static const int n_cities = pn_cities;
    
    if(city_A == city_B){
      return 0;
    }
  
    // Búscamos de la ciudad menor a la mayor por lo que city_A debe ser menor
    if(city_A > city_B){
      //std::swap(city_A,city_B);
      int tmp = city_A;
      city_A = city_B;
      city_B = tmp;
    }

    // Validamos que valores esten dentro del rango de ciudades disponibles
    if(city_B > n_cities || city_A <= 0){
      throw std::runtime_error("Error: Petición con ciudad inválida");
    }
   
    // Por almacenar las distancias en un arreglo unidimensional, 
    // debemos calcular el offset para cada city_A 
    int offset = 0;
    for(int i=1; i<city_A; ++i){
      offset += n_cities - i;
    }
 
    // Obtenemos la posición que representa la distancia entre city_A y city_B 
    return city_distances[offset + (city_B - city_A -1 )];  
  }
}
