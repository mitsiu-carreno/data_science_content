#include <iostream>

#include "tabu.hpp"

namespace tabu{
  void Solve(const ProblemMetadata &p_meta, std::set<travel_path::Solution, travel_path::SolutionCompare> &solutions){
    /*
      Función para resolver el problema dado con el algoritmo tabú
      Input:
        const ProblemMetadata & - Estructura con los metadatos del problema
        std::set<travel_path::Solution, travel_path::SolutionCompare> & - Conjunto de soluciones (recorrido y distancia), ordenadas y sin duplicación
    */
  
    // Generamos estructura para almacenar soluciones tabu
    std::set<travel_path::Solution, travel_path::SolutionCompare> tabu;

    // Guardamos en el conjunto tabú el mejor resultado de nuestra población inicial
    auto first = solutions.begin();
    tabu.insert({std::vector<int>(first->path), first->distance});
    
    std::cout << "Lista tabu\n";
    travel_path::PrintSolutions(tabu);
    std::cout << "\n";

    // Guardamos el número de iteración para continuar nuestra búsqueda a traves de iteraciones si no hay mejoría global
    int acc = 1;
    for(int i=0; i<p_meta.n_iters; ++i){
      // Borramos soluciones anteriores
      solutions.clear();

      // Usamos el mejor tabu para generar vecinos
      auto tabu_first = tabu.begin();
      // Generamos nuevas soluciones vecinas de nuestra mejor solución tabú
      acc = GenNeighborSolutions(tabu_first->path, solutions, p_meta.n_solutions, p_meta.n_cities, acc);
      
      std::cout << "Iteración " << i + 1 << "\n";
      travel_path::PrintSolutions(solutions);
      std::cout << "\n\n";
    
      // Comparamos las nuevas soluciones con la lista tabú
      for (std::set<travel_path::Solution, travel_path::SolutionCompare>::iterator j = solutions.begin(); j != solutions.end(); ++j) {
        // Contamos los elementos en tabu
        int n_pre = tabu.size();
        // Intentamos insertar mejor solución (set elimina duplicados)
        tabu.insert({j->path, j->distance});
        // Contabilizamos los elementos después del intento de inserción
        int n_post = tabu.size();

        // Si la cantidad de elementos cambio 
        if(n_pre < n_post){
          // Verificar si tabú se llenó
          if(n_post > p_meta.tabu_size){
            tabu.erase(std::prev(tabu.end()));
          }
          // Dejamos de intentar insertar elementos
          break;
        }
      }
      std::cout << "Lista tabu\n";
      travel_path::PrintSolutions(tabu);
      std::cout << "--------------------------------\n";
            
    }
    
  }
}
