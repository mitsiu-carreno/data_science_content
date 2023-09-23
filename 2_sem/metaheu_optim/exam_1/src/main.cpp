#include <iostream>   /* std::cout */
#include <set>        /* std::set */

#include "utils.hpp"
#include "travel-path.hpp"
#include "problem-metadata.hpp"
#include "grasp.hpp"
#include "tabu.hpp"
#include "scatter-search.hpp"

bool DefineProblem(ProblemMetadata &p_meta){
  /*
    Función para preguntar los parametros generales del problema
    Input:
      ProblemMetadata * - Variable donde guardar los valores ingresados
    Output:
      bool - Responde si el usuario desea ingresar las distancias de ciudades a mano
  */


  // Número de ciudades
  int *n_cities = new int;
  utils::AskValue("\nIngresa la cantidad de ciudades", n_cities, utils::kInteger);

  // Ingresar distancias de ciudades
  int *dynamic =new int;
  utils::AskValue("\nDeseas ingresar las distancias entre ciudades de manera manual o tomar los valores de moodle [Manual-1 Moodle-0]", dynamic, utils::kInteger);
  if(*dynamic != 1){
    std::cout << "Tomando distancias predefinidas, se tomarán las 8 ciudades de moodle como base\n";
  }

  // Número de soluciones
  int *n_solutions = new int;
  while(true){
    utils::AskValue("\nIngresa la cantidad de soluciones a crear", n_solutions, utils::kInteger);
    // El número de soluciones no puede ser mayor al número máximo de permutaciones dadas n_ciudades
    if(*n_solutions <= utils::GetFactorial(*n_cities)){
      break;
    }
    std::cout << "Se solicitan más soluciones de las posibles, intenta un número más chico\n\n";
  }

  // Número de iteraciones
  int *n_iters = new int;
  utils::AskValue("\nIngresa la cantidad de iteraciones", n_iters, utils::kInteger);

  // Algoritmo solución
  int *n_algorithm = new int;
  while(true){
    utils::AskValue("\nSelecciona algoritmo (ingresa número)\nGrasp->1\nTabu->2\nDispersa->3", n_algorithm, utils::kInteger);
    if(*n_algorithm >= 1 && *n_algorithm <= 3){
      *n_algorithm -=1;
      break;
    }
    std::cout << "Opción incorrecta\n\n";
  }

  // Si algoritmo seleccionado es tabú, solicitar tamaño de arreglo tabú 
  int *tabu_size = new int;
  int *scatter_pairs = new int;
  int *scatter_percen = new int;

  if(static_cast<Algorithms>(*n_algorithm) == Algorithms::tabu){
    // Solicitar tamaño de conjunto tabu
    utils::AskValue("\nIngresa el tamaño del conjunto tabú", tabu_size, utils::kInteger);
  }else if(static_cast<Algorithms>(*n_algorithm) == Algorithms::scatter_search){
    while(true){
      // Solicitar cantidad de pares  a combinar
      utils::AskValue("\nIngresa la cantidad de pares a combinar", scatter_pairs, utils::kInteger);
      if(*scatter_pairs <= (*n_solutions/2)){
        break;
      }
      std::cout << "La cantidad de pares debe ser menor a la canitdad de pares de soluciones (" << *n_solutions/2 << ")\n\n";
    }
    
    while(true){
      // Solicitar porcentaje de selección
      utils::AskValue("\nIngresa el porcentaje de selección [0-100]", scatter_percen, utils::kInteger);
      if(*scatter_percen >= 0 && *scatter_percen <= 100){
        break;
      }
      std::cout << "Ingresa un porcentaje entero entre 0 y 100\n\n";
    }
    
  }

  // Guardamos todos los resultados en la estructura ProblemMetadata (en header ProblemMetadata) 
  p_meta.n_cities       = *n_cities;
  p_meta.n_solutions    = *n_solutions;
  p_meta.n_iters        = *n_iters;
  p_meta.algo           = static_cast<Algorithms>(*n_algorithm); 
  p_meta.tabu_size      = tabu_size ? *tabu_size : 0;
  p_meta.scatter_pairs  = scatter_pairs ? *scatter_pairs : 0;
  p_meta.scatter_percen = scatter_percen ? *scatter_percen : 0;
  
  // Limpiamos los apuntadores (requeridos para utils/ask-value.cpp)
  delete n_cities;
  delete n_solutions;  
  delete n_iters;
  delete n_algorithm;
  
  return *dynamic;
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
      std::string prompt = std::string("\nIngresa la distancia entre ciudad ") 
        + std::to_string(city_a) 
        + std::string(" (")
        + static_cast<char>(city_a + ascii_start)
        + std::string(") y ") 
        + std::to_string(city_b%n_cities +1)
        + std::string(" (")
        + static_cast<char>(city_b + 1 + ascii_start)
        + std::string(")");

      utils::AskValue(prompt, &city_distances[i], utils::kFloat);
      // Verificar si aun quedan conexiones de ciudades con la ciudad actual
      if((city_b+1)%n_cities == 0){
        ++city_a;
        city_b = city_a;
        continue;
      }
      ++city_b;
    }
  }else{
    // Valores predefinidos en moodle
    city_distances[0] = 15; 
    city_distances[1] = 11;
    city_distances[2] = 21; 
    city_distances[3] = 9;
    city_distances[4] = 18;
    city_distances[5] = 22;
    city_distances[6] = 25;
    city_distances[7] = 10;
    city_distances[8] = 15;
    city_distances[9] = 28;
    city_distances[10] = 22;
    city_distances[11] = 21;
    city_distances[12] = 31;
    city_distances[13] = 21;
    city_distances[14] = 13;
    city_distances[15] = 17;
    city_distances[16] = 20;
    city_distances[17] = 28;
    city_distances[18] = 18;
    city_distances[19] = 11;
    city_distances[20] = 31;
    city_distances[21] = 22;
    city_distances[22] = 31;
    city_distances[23] = 23;
    city_distances[24] = 18;
    city_distances[25] = 26;
    city_distances[26] = 21;
    city_distances[27] = 16;
  }
  return city_distances;
}

int main(){
  // Punto de inicio de la ejecución del programa

  float *city_distances;
  try{
    // Preguntamos valores generales para saber el problema y como resolverlo
    ProblemMetadata p_meta;
    bool dynamic = DefineProblem(p_meta);
    
    // Si elige los datos de moodle seteamos a 8 ciudades
    if(!dynamic){
      p_meta.n_cities = 8;
    }

    // Generamos arreglo con distancias entre ciudades
    city_distances = ConnectCities(p_meta.n_cities, dynamic);

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
    
    // Evaluamos bajo que algoritmo se desea resolver el problema
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
        std::cout << "\nBúsqueda dispersa\n";
        scatter::Solve(p_meta, solutions);
        break;
      default: 
        std::cout << "Algoritmo no soportado\n";
    }

  }catch(const std::exception &e){
    std::cout << "Ha ocurrido un error:\n" << e.what() << "\n Terminando programa\n";
  }
  
  // Liberamos la memoria del arreglo de distancias entre ciudades
  delete[] city_distances;

  return 0;
}
