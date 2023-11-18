#include <vector>
#include <iostream>

#include "ship.hpp"
#include "container.hpp"
#include "read-csv.hpp"



int main(){
  std::vector<Ship> ships; 
  utils::ReadCsv("data/ships.csv", utils::ParseEntities::kShip, ships);
  std::cout << ships.size() << "\n";

  std::vector<Container> containers;
  utils::ReadCsv("data/containers.csv", utils::ParseEntities::kContainer, containers);
  std::cout << containers.size() << "\n";
  
  return 0;
}
