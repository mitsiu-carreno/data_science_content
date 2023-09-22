#ifndef SCATTER_SEARCH_HPP
#define SCATTER_SEARCH_HPP

#include <set>  /* std::set */
#include "problem-metadata.hpp"
#include "travel-path.hpp"

namespace scatter{
  void Solve(const ProblemMetadata &, std::set<travel_path::Solution, travel_path::SolutionCompare> &);
}

#endif
