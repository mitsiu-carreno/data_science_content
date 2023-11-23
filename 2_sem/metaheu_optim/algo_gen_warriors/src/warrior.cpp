#include "warrior.hpp"
#include "attr-range.hpp"
#include "csv.hpp"
#include "constants.hpp"

namespace warrior{
  void ParseWarriorAttributeRange(int data_index, std::string value, AttrRange &attr_range){
    switch(data_index){
      case static_cast<int>(AttrRangeDescrip::kAttr):
        attr_range.attr = value;
        break;
      case static_cast<int>(AttrRangeDescrip::kMin):
        attr_range.min = std::stoi(value);
        break;
      case static_cast<int>(AttrRangeDescrip::kMax):
        attr_range.max = std::stoi(value);
        break;
      default:
        std::cout << "Attr range: columna " << data_index << " no reconocida\n";
        break;
    }
  }

  void GenWarriors(std::vector<Warrior> &army){

    std::vector<AttrRange> warrior_attrs_range;
    utils::ReadCsv("data/ranges.csv", warrior_attrs_range, warrior::ParseWarriorAttributeRange);
  
    for(int i{0}; i< Constants::kWarriorsPool; ++i){
      //Warrior new_warrior;
      for(AttrRange attr_range : warrior_attrs_range){
        //switch(attr_range){
        //  case static_cast<int>(WarriorAttr::kAttack):
        //    new_warrior.attack = 10;
        //} 
      army.emplace_back(1,2,3,4,5,6,7,8,9,10);
      }
    }
  }
}
