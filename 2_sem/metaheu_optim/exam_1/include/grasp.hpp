#ifndef GRASP_HPP
#define GRASP_HPP

#include <set>  /* std::set */
#include "travel-path.hpp"
#include "problem-metadata.hpp"

namespace grasp{
  void Solve(const ProblemMetadata &, std::set<travel_path::Solution, travel_path::SolutionCompare> &); 
}

#endif
