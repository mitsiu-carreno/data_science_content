#ifndef TRAVEL_PATH_HPP
#define TRAVEL_PATH_HPP

#include <set>    /* std::set */
#include <vector> /* std::vector */

namespace travel_path{
  // Creamos una estructura que une el recorrido de ciudades (path)
  // y el valor de distancia para dicho recorrido (distance)
  struct Solution{
    std::vector<int> path;
    float distance;
  };

  // Definimos el método de comparación entre soluciones para ordenarlas (basados en reducir distancia) (requerido para std::set)
  struct SolutionCompare{
    bool operator()(const Solution &left, const Solution &right) const{
      return left.distance < right.distance;
    }
  };
  
  void GenRandomSol(const int &, const int &, std::set<travel_path::Solution, travel_path::SolutionCompare> &);
  int GenNeighborSolutions(std::vector<int>, std::set<travel_path::Solution, travel_path::SolutionCompare> &, const int &, const int &, int);
  float EvalSolution(const std::vector<int> &); 
  float GetDistance(int, int, float*, int); 
  void PrintSolution(const travel_path::Solution &);
  void PrintSolutions(const std::set<travel_path::Solution, travel_path::SolutionCompare> &);
}

#endif
