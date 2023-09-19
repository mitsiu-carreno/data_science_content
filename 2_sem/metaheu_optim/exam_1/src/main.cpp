#include <iostream>
#include "utils.hpp"
#include "problem-metadata.hpp"

void DefineProblem(ProblemMetadata *p_meta){
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

  // Guardamos todos los resultados en la estructura ProblemMetadata (en header ProblemMetadata) 
  //p_meta {*n_cities, *n_solutions, *n_iters, static_cast<Algorithms>(*n_algorithm)};
  p_meta->n_cities    = *n_cities;
  p_meta->n_solutions = *n_solutions;
  p_meta->n_iters     = *n_iters;
  p_meta->algo        = static_cast<Algorithms>(*n_algorithm); 
  
  // Limpiamos los apuntadores (requeridos para utils/ask-value.cpp)
  delete n_cities;
  delete n_solutions;  
  delete n_iters;
  delete n_algorithm;

}

float* ConnectCities(int &n_cities){
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
  
  return city_distances;
}

int main(){
  // Preguntamos valores generales para saber el problema y como resolverlo
  ProblemMetadata *p_meta = new ProblemMetadata;
  DefineProblem(p_meta);

  std::cout << "cit: " << p_meta->n_cities << " sol:" << p_meta->n_solutions << " inters:" << p_meta->n_iters << " algo" << static_cast<int>(p_meta->algo) << "\n";

  float *city_distances = ConnectCities(p_meta->n_cities);
  for(int i=0; i<10; ++i){
    std::cout << city_distances[i] << "\n";
  }
  
  delete[] city_distances;
  return 0;
}
