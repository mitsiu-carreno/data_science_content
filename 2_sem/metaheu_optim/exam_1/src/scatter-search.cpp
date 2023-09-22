#include <algorithm>

#include <iostream>

#include "travel-path.hpp"
#include "scatter-search.hpp"
#include "utils.hpp"


namespace scatter{
  void Solve(const ProblemMetadata &p_meta, std::set<travel_path::Solution, travel_path::SolutionCompare> &solutions){
    std::cout << "Scatter\n";
   
    // Generamos dos iteradores (posteriormente se acutalizarán para apuntar a indice de solución seleccionada (select_indexes))
    std::set<travel_path::Solution, travel_path::SolutionCompare>::iterator first_sol;
    std::set<travel_path::Solution, travel_path::SolutionCompare>::iterator second_sol;
 
    // Variable para almacenar la nueva solución después de combinar dos soluciones
    std::unordered_set<int> new_solution;

    for(int i=0; i<p_meta.n_iters; ++i){
    
      std::unordered_set<int> select_indexes;
      // Seleccionamos de manera aleatoría pares para diversificar la población
      while(static_cast<int>(select_indexes.size()) < p_meta.scatter_pairs * 2){
        select_indexes.insert(utils::RandomInInterval(0, p_meta.n_solutions -1));
      }
    

      // Iteramos por par nuestros indices seleccionados
      for(auto it = select_indexes.begin(); it != select_indexes.end(); std::advance(it, 2)){
        auto next_it = std::next(it);
        std::cout << "Combinando elementos " << *it + 1 << "-" << *next_it + 1<< "\n";

        // Resetamos nuestos iteradores al inicio de las soluciones
        first_sol = solutions.begin();
        second_sol = solutions.begin();
        // Reseteamos combinaciones de soluciones pasadas
        new_solution.clear();
      
        // Adelantamos el apuntador a la posición del primer indice seleccionado
        std::advance(first_sol, *it);
        std::advance(second_sol, *next_it);
        // Generamos una nueva solución combinando las anteriores seleccionadas
        scatter::CombineSolutions(first_sol->path, second_sol->path, new_solution);
        
        // Convertimos el unordered_set (elimina duplicados) en vector 
        std::vector<int>new_sol_v (new_solution.begin(), new_solution.end());
        // Invertimos el orden de todos los elementos
        std::reverse(new_sol_v.begin(), new_sol_v.end());
    
        // Agregamos las nuevas soluciones
        solutions.insert({std::vector<int>(new_sol_v), travel_path::EvalSolution(new_sol_v)});

      } 
      std::cout <<"\nPoblación extendida:\n";
      travel_path::PrintSolutions(solutions);
    }
  }
  
  void CombineSolutions(const std::vector<int> &a, const std::vector<int> &b, std::unordered_set<int> &new_solution){
    if(a.size() != b.size()){
      std::cout << "Error " << a.size() << "!=" << b.size() << "\n";
      throw std::runtime_error("Error: Las soluciones a combinar son de distintos tamaños");
    }
    
    for(int i=0; i<static_cast<int>(a.size()); ++i){
      new_solution.insert(a.at(i));
      new_solution.insert(b.at(i));
      //std::cout << a.at(i) << "-" << b.at(i) << "| ";
    }
  }
}
