#ifndef ARMY_HPP
#define ARMY_HPP

#include <set>
#include <vector>
#include "warrior.hpp"

struct ArmyT{
  // Id warrior from warriors pool
  std::set<int> warriors;
  double score;
};

struct ArmyComparator{
  bool operator()(const ArmyT &left, const ArmyT &right) const{
    return left.score > right.score;
  }
};

namespace Army{
  double Score(const std::set<int> &, const std::vector<Warrior> &);
  void Generate(const int, const int, std::set<ArmyT, ArmyComparator> &, const std::vector<Warrior> &); 
  void Crossover(const std::set<int> &, const std::set<int> &, const int, std::set<ArmyT, ArmyComparator> &, const std::vector<Warrior> &);
}

#endif
