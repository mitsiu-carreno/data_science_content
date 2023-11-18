#ifndef SHIPS_HPP
#define SHIPS_HPP

enum class ShipAttr{
  kCode,
  kCost,
  kMax_weight,
  kMax_n_containers
};

struct Ship{
  std::string code;
  float cost;
  float max_weight;
  float max_n_containers;
};

#endif
