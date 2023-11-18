#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

#include "ships.hpp"
#include "read-csv.hpp"


namespace utils{

  void* ReadCsv(std::string path, utils::ParseEntities entity){
    std::ifstream read_file(path);
    std::string line;
    std::vector<Ship>* ships = new std::vector<Ship>;
    int row = 1;
   
    while(std::getline(read_file, line)){
      if(row == 1){
        ++row;
        continue;
      }
      std::stringstream lineStream(line);
      std::string value;
      Ship new_ship;

      int index = 0;
      while(std::getline(lineStream, value, ',')){
        try{
          utils::ParseCsv(entity, index, value, new_ship);
        }catch(const std::exception &e){
          std::cout << "Error al leer " << row << ":" << index  << " con valor "<< value << "\n";
        }
        ++index;
      }

      std::cout << "Summary Code" << new_ship.code << " cost " << new_ship.cost << "\n";
      ships->push_back(new_ship);
      ++row;
    }
    return static_cast<void*>(ships);
  }

  void ParseCsv(utils::ParseEntities entity, int data_index, std::string value, Ship &ship){
    if(entity == utils::ParseEntities::kShip){
      switch(data_index){
        case static_cast<int>(ShipAttr::kCode):
          ship.code = value;
          break;
        case static_cast <int>(ShipAttr::kCost):
          ship.cost = std::stof(value);
          break;
        default:
          std::cout << "Columna " << data_index << " no reconocida\n";
          break;
      }
    } 
  }
}

