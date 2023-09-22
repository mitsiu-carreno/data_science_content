#include <iostream>   /* std::cout */
#include <set>        /* std::set */

#include "utils.hpp"
#include "travel-path.hpp"
#include "problem-metadata.hpp"
#include "grasp.hpp"
#include "tabu.hpp"

void DefineProblem(ProblemMetadata &p_meta){
  /*
    Función para preguntar los parametros generales del problema
    Input:
      ProblemMetadata * - Variable donde guardar los valores ingresados
  */

  // Número de ciudades
  int *n_cities = new int;
  utils::AskValue("Ingresa la cantidad de ciudades", n_cities, utils::kInteger);

  // Número de soluciones
  int *n_solutions = new int;
  utils::AskValue("Ingresa la cantidad de soluciones a crear", n_solutions, utils::kInteger);
  // El número de soluciones no puede ser mayor al número máximo de permutaciones dadas 
  // n_ciudades
  if(*n_solutions > utils::GetFactorial(*n_cities)){
    throw std::runtime_error("Error: Se solicitan más soluciones de las posibles");
  }

  // Número de iteraciones
  int *n_iters = new int;
  utils::AskValue("Ingresa la cantidad de iteraciones", n_iters, utils::kInteger);

  // Algoritmo solución
  int *n_algorithm = new int;
  while(true){
    utils::AskValue("Selecciona algoritmo (ingresa número)\nGrasp->1\nTabu->2\nDispersa->3", n_algorithm, utils::kInteger);
    if(*n_algorithm >= 1 && *n_algorithm <= 3){
      *n_algorithm -=1;
      break;
    }
    std::cout << "Opción incorrecta\n\n";
  }

  // Si algoritmo seleccionado es tabú, solicitar tamaño de arreglo tabú 
  int *tabu_size = new int;
  if(static_cast<Algorithms>(*n_algorithm) == Algorithms::tabu){
    utils::AskValue("Ingresa el tamaño del conjunto tabú", tabu_size, utils::kInteger);
  }

  // Guardamos todos los resultados en la estructura ProblemMetadata (en header ProblemMetadata) 
  //p_meta {*n_cities, *n_solutions, *n_iters, static_cast<Algorithms>(*n_algorithm)};
  p_meta.n_cities     = *n_cities;
  p_meta.n_solutions  = *n_solutions;
  p_meta.n_iters      = *n_iters;
  p_meta.algo         = static_cast<Algorithms>(*n_algorithm); 
  p_meta.tabu_size    = tabu_size ? *tabu_size : 0;
  
  // Limpiamos los apuntadores (requeridos para utils/ask-value.cpp)
  delete n_cities;
  delete n_solutions;  
  delete n_iters;
  delete n_algorithm;

}

float* ConnectCities(int &n_cities, bool interactive){
  /*
    Función para preguntar las distancias entre ciudades
    Input:
      int n_cities - Cantidad de ciudades
    Output:
      float * - Array de distancias entre n_cities conectando todas las ciudades
  */
    
  //Para obtener la cantidad de caminos para n_cities 
  // búscamos la combinatoria sin repetición de n_cities con dos caminos
  // nCr = n!/(r!(n-r)!)
  int r = 2;
  int combinations = utils::GetFactorial(n_cities) / (utils::GetFactorial(r) * (utils::GetFactorial(n_cities -r)));
  
  float *city_distances = new float[combinations];
  if(interactive){
    int ascii_start = 64;
    for(int i=0, city_a=1, city_b = 1; i<combinations; ++i){
      std::string prompt = std::string("Ingresa la distancia entre ciudad ") 
        + std::to_string(city_a) 
        + std::string(" (")
        + static_cast<char>(city_a + ascii_start)
        + std::string(") y ") 
        + std::to_string(city_b%n_cities +1)
        + std::string(" (")
        + static_cast<char>(city_b + 1 + ascii_start)
        + std::string(")");

      utils::AskValue(prompt, &city_distances[i], utils::kFloat);
      if((city_b+1)%n_cities == 0){
        ++city_a;
        city_b = city_a;
        continue;
      }
      ++city_b;
    }
  }else{
    city_distances[0] = 12; 
    city_distances[1] = 5;
    city_distances[2] = 11; 
    city_distances[3] = 42;
    city_distances[4] = 31;
    city_distances[5] = 23;
    city_distances[6] = 17;
    city_distances[7] = 6;
    city_distances[8] = 8;
    city_distances[9] = 3;
  }
  return city_distances;
}

int main(){
  try{
    // Preguntamos valores generales para saber el problema y como resolverlo
    ProblemMetadata p_meta;
    //DefineProblem(p_meta);    // debug
p_meta.n_cities = 5;
p_meta.n_solutions = 5;
p_meta.n_iters = 10;
p_meta.algo = Algorithms::tabu;
p_meta.tabu_size = 3;

    // Generamos arreglo con distancias entre ciudades
    float *city_distances = ConnectCities(p_meta.n_cities, false);

    // Guardar arrelgo de distancias en estado interno de cities::GetDistances
    // Probablemente OOP hubiera almacenado el estado de mejor manera pero por ahora lo 
    // manejaré así 
    travel_path::GetDistance(1,1, city_distances, p_meta.n_cities);

    // Generamos estructura (set) para almacenar las posibles soluciones así como su distancia
    std::set<travel_path::Solution, travel_path::SolutionCompare> solutions;

    // Generamos soluciones aleatorias y las guardamos en el set
    travel_path::GenRandomSol(p_meta.n_cities, p_meta.n_solutions, solutions);

    std::cout << "\n\nSoluciones iniciales:\n";
    travel_path::PrintSolutions(solutions);
    
    switch(p_meta.algo){
      case Algorithms::grasp:
        std::cout << "\nGrasp\n";
        grasp::Solve(p_meta, solutions);
        break;
      case Algorithms::tabu:
        std::cout << "\nTabu\n";
        tabu::Solve(p_meta, solutions);
        break;
      case Algorithms::scatter_search:
        std::cout << "Tabu Pending\n";
        break;
      default: 
        std::cout << "Algoritmo no soportado\n";
    }

    // Liberamos la memoria del arreglo de distancias entre ciudades
    delete[] city_distances;
  }catch(const std::exception &e){
    std::cout << "Ha ocurrido un error:\n" << e.what() << "\n Terminando programa\n";
  }
  
  return 0;
}
