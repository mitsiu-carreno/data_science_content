#include <algorithm>  /* std::swap*/
#include <stdexcept>  /* std::runtime_error */

#include "cities.hpp"

namespace cities{
  float GetDistance(int city_A, int city_B, float *city_distances, int &n_cities){
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
