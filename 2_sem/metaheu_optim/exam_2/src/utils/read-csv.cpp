#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "ships.hpp"
#include "read-csv.hpp"


namespace utils{

  void ReadCsv(std::string path, utils::ParseEntities entity){
    std::ifstream read_file(path);
    std::string line;

    while(std::getline(read_file, line)){
      std::stringstream lineStream(line);
      std::string value;
      int index = 0;
      while(std::getline(lineStream, value, ',')){
        utils::ParseCsv(entity, index, value);
        ++index;
      }
    }
  }

  void ParseCsv(utils::ParseEntities entity, int data_index, std::string value){
    if(entity == utils::ParseEntities::kShip){
      switch(data_index){
        case static_cast<int>(ShipAttr::kCode):
          std::cout << "0Code\n";
          break;
        case static_cast <int>(ShipAttr::kCost):
          std::cout << "1cost\n";
          break;
        default:
          std::cout << "Not recongnized " << data_index << "\n";
          break;
      }
    } 
  }
}

