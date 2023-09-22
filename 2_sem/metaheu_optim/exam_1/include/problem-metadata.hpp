#ifndef PROBLEM_META_HPP
#define PROBLEM_META_HPP

enum class Algorithms{
  grasp,
  tabu,
  scatter_search
};

struct ProblemMetadata{
  int n_cities;
  int n_solutions;
  int n_iters;
  Algorithms algo;
  int tabu_size;
};

#endif
