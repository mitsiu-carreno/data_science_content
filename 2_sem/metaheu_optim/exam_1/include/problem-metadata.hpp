#ifndef PROBLEM_META_HPP
#define PROBLEM_META_HPP

// Enumerador con los distintos algoritmos soportados
enum class Algorithms{
  grasp,
  tabu,
  scatter_search
};

// Estructura para almacenar la información (metadata) general del problema
struct ProblemMetadata{
  int n_cities;
  int n_solutions;
  int n_iters;
  Algorithms algo;
  int tabu_size;
  int scatter_pairs;
  int scatter_percen;
};

#endif
