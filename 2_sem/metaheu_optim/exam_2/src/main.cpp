#include <vector>
#include <iostream>

#include "ships.hpp"
#include "read-csv.hpp"



int main(){
  std::vector<Ship>* ships = static_cast<std::vector<Ship>*>(utils::ReadCsv("data/ships.csv", utils::ParseEntities::kShip));
  std::cout << ships->size() << "\n";

  return 0;
}
