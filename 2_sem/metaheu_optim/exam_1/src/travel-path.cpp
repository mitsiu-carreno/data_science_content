#include <algorithm>  /* std::shuffle std::swap*/
#include <vector>     /* std::vector */
#include <stdexcept>  /* std::runtime_error */
#include <iostream>   /* std::cout */

#include "travel-path.hpp"
#include "utils.hpp"

namespace travel_path{
  
  void GenRandomSol(const int &n_cities, const int &n_solutions, std::set<travel_path::Solution, travel_path::SolutionCompare> &solutions){
    /*
      Función para generar n distintas soluciones de camino
      Input: 
        const int &n_cities - Cantidad de ciudades disponibles
        const int &n_solutions - Cantidad de soluciones distintas esperadas
        std::set<travel_path::Solution, travel_path::SolutionCompare> & - Conjunto para guardar las soluciones creadas
    */
  
    // Generamos una solución ordenada (1,2,3,4,5 ... n_cities)
    // Hasta ahora suponemos que cada ciudad se conecta con todas las demás
    // y que el caminó de ida tiene la misma distancia que el camino de regreso
    std::vector<int> base_solution(n_cities);
    for(int i=0; i<n_cities; ++i){
      base_solution.at(i) = i+1;
    }

    // Partiendo de la solución base, generaremos nuevas soluciones random 
    while(static_cast<int>(solutions.size()) < n_solutions){
      // Aleatorizamos los elementos de la solución base [start, end, función de randomizado)
      std::shuffle(base_solution.begin(), base_solution.end(), utils::RandomFunction());
  
      // Insertamos la nueva solución en set (si esta duplicada la ignora de automático)
      solutions.insert({std::vector<int>(base_solution), travel_path::EvalSolution(base_solution)});

    }
  }

  int GenNeighborSolutions(std::vector<int> base_solution, std::set<travel_path::Solution, travel_path::SolutionCompare> &solutions, const int &n_solutions, const int &n_cities, int acc){
    /*
      Función para generar n_soluciones vecinas dada una solución base
      Input:
        std::vector<int> - Solución base
        std::set<travel_path::Solution, travel_path::SolutionCompare> & - Conjunto para guardar las soluciones creadas
        const int & - Cantidad de soluciones distintas en total
        const int & - Cantidad de ciudades total en el problema
        int - Número de iteración actual
    */
    
    // Se van a generar n_solutions nuevas, todas únicas
    while(static_cast<int>(solutions.size()) < n_solutions){
      std::vector<int> base_solution_backup(base_solution);

      // Se emplean distintas estatégias para generar vecinos en un round robin allocation
      int round_turn = (acc + 1) % n_cities;
      switch(round_turn){
        case 0:
//std::cout << "0--";
          // Incrementar cada ciudad + acc
          std::for_each(base_solution_backup.begin(), base_solution_backup.end(), [acc, n_cities](int& city) { city = ((city+acc/2)%n_cities)+1;});
          break;
        case 1: 
//std::cout << "1--";
          // Rotar los últimos elementos al principio de la ruta
          std::rotate(base_solution_backup.rbegin(), base_solution_backup.rbegin() + (acc%n_cities)+1, base_solution_backup.rend());
          break;
        case 2:
//std::cout << "2--";
          // Rotar los primeros elementos al final de la ruta
          std::rotate(base_solution_backup.begin(), base_solution_backup.begin() + (acc%n_cities)+1, base_solution_backup.end());
          break;
        case 3:
//std::cout << "3--";
          // Intercambiar dos elementos
          std::swap(base_solution_backup.at(acc%n_cities), base_solution_backup.at((acc-1)%n_cities));
          break;
        default:
//std::cout << "4--";
          // Aleatorizar la posición de todos los elementos
          std::shuffle(base_solution_backup.begin(), base_solution_backup.end(), utils::RandomFunction());
      } 
      
      // Se inserta la nueva solución al conjunto
      solutions.insert({std::vector<int>(base_solution_backup), travel_path::EvalSolution(base_solution_backup)});
      ++acc;
    }
    return acc;
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
        float *pcity_distances - Arreglo unidimensional de todas las distancias entre ciudades
        int &pn_cities - Total de ciudades existentes
      Output:
        float  - Distancia entre las ciudades ingresadas
    */

    // Guardamos arreglo de distancias entre ciudades para no soliciarlo multiples veces
    static const float *city_distances = pcity_distances;
    // Guardamos cantidad de ciudades para no solicitarlo multipes veces
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

  void PrintSolution(const travel_path::Solution &solution){
    /*
      Función para imprimir en formato una solución (recorrido y distancia)
      Input:
        const travel_path::Solution - Estructura con el recorrido y distancia a imprimir
    */
    std::cout << "Ruta: [";
    for(auto &city: solution.path){
      std::cout << " " << city << " ";
    }
    std::cout << "] -> Distancia " << solution.distance << "\n";
  }

  void PrintSolutions(const std::set<travel_path::Solution, travel_path::SolutionCompare> &solutions){
    /*
      Función para imprimir en formato un conjunto de soluciones (recorridos y distancias)
      Input:
        const std::set<travel_path::Solution, travel_path::SolutionCompare> & - Conjunto de soluciones
    */
    for(auto &solution : solutions){
      PrintSolution(solution);
    }
  }
}
