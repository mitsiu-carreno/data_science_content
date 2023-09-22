#ifndef TABU_HPP
#define TABU_HPP
 
#include <set>  /* std::set */
#include "travel-path.hpp"
#include "problem-metadata.hpp"

namespace tabu{
  void Solve(const ProblemMetadata &, std::set<travel_path::Solution, travel_path::SolutionCompare> &);
}

#endif
