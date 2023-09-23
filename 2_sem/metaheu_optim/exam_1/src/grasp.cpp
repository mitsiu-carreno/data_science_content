#include <iostream>

#include "grasp.hpp"

namespace grasp{
  void Solve(const ProblemMetadata &p_meta, std::set<travel_path::Solution, travel_path::SolutionCompare> &solutions){
    /*
      Función para resolver el problema del viajero mediante el método GRASP
      Input:
        const ProblemMetadata & - Estructura con los metadatos del problema
        std::set<travel_path::Solution, travel_path::SolutionCompare> & - Conjunto que almacena los recorridos así como su distancia
      Output:
        
    */
    
    // Creamos un iterador que apunta al inicio de las soluciones
    auto first = solutions.begin();
    // Extraemos el primer elemento (el mejor recorrido) 
    travel_path::Solution global_best_solution = {first->path, first->distance};

    std::cout << "Mejor solución\n";
    travel_path::PrintSolution(global_best_solution); 
 
    // Guardamos el número de iteración para continuar nuestra búsqueda a traves de iteraciones si no hay mejoría global
    int acc = 1; 
    for(int i=0; i< p_meta.n_iters; ++i){
      // Borramos soluciones anteriorres
      solutions.clear();
      // Generamos nuevas soluciones vecinas de nuestra mejor solución global
      acc = GenNeighborSolutions(global_best_solution.path, solutions, p_meta.n_solutions, p_meta.n_cities, acc);
    
      // Imprimimos las soluciones vecinas de nuestra mejor solución global
      std::cout << "Iteración " << i +1 << "\n";
      travel_path::PrintSolutions(solutions); 
      std::cout << "\n\n";

      // Comparamos la nueva solución con el global_best
      auto iter_first = solutions.begin();
      // Si el vecino es mejor, actualizamos global_best
      if(global_best_solution.distance > iter_first->distance){
        global_best_solution = {iter_first->path, iter_first->distance};
      } 
    }
    
    std::cout << "Solución encontrada:\n";
    travel_path::PrintSolution(global_best_solution);
  }  
}
