#include "read-csv.hpp"

int main(){
  utils::ReadCsv("data/ships.csv", utils::ParseEntities::kShip);

  return 0;
}
