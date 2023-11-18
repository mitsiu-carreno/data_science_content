#include "ship.hpp"
#include "container.hpp"
#include "read-csv.hpp"


namespace utils{
  void ParseEntity(int data_index, std::string value, Ship &ship){
    switch(data_index){
      case static_cast<int>(ShipAttr::kCode):
        ship.code = value;
        break;
      case static_cast<int>(ShipAttr::kCost):
        ship.cost = std::stof(value);
        break;
      case static_cast<int>(ShipAttr::kMax_weight):
        ship.max_weight = std::stof(value);
        break;
      case static_cast<int>(ShipAttr::kMax_n_containers):
        ship.max_n_containers = stoi(value);
        break;
      default:
        std::cout << "Barco: columna " << data_index << " no reconocida\n";
        break;
    } 
  }

  void ParseEntity(int data_index, std::string value, Container &container){
    switch(data_index){
      case static_cast<int>(ContainerAttr::kCode):
        container.code = value;
        break;
      case static_cast<int>(ContainerAttr::kCost):
        container.cost = std::stof(value);
        break;
      case static_cast<int>(ContainerAttr::kCharge):
        container.charge = std::stof(value);
        break;
      case static_cast<int>(ContainerAttr::kImmediacy):
        container.immediacy = std::stoi(value);
        break;
      case static_cast<int>(ContainerAttr::kPriority):
        container.priority = std::stoi(value);
        break;
      case static_cast<int>(ContainerAttr::kWeight):
        container.weight = std::stof(value);
        break;
      default:
        std::cout << "Contenedor: columna " << data_index << " no reconocida\n";
        break;
    } 
  }
}

