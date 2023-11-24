#include "warrior.hpp"
#include "attr-range.hpp"
#include "csv.hpp"
#include "constants.hpp"
#include "gen-random.hpp"

namespace warrior{
  WarriorAttr MapAttr(std::string attr_str){
    if(attr_str == "attack"){
      return WarriorAttr::kAttack;
    }else if(attr_str == "defense"){
      return WarriorAttr::kDefense;
    }else if(attr_str == "shield"){
      return WarriorAttr::kShield;
    }else if(attr_str == "health"){
      return WarriorAttr::kHealth;
    }else if(attr_str == "health_reg"){
      return WarriorAttr::kHealthReg;
    }else if(attr_str == "aggressive"){
      return WarriorAttr::kAggressive;
    }else if(attr_str == "intel"){
      return WarriorAttr::kIntel;
    }else if(attr_str == "control_resis"){
      return WarriorAttr::kControlResis;
    }else if(attr_str == "control"){
      return WarriorAttr::kControl;
    }else if(attr_str == "build"){
      return WarriorAttr::kBuild;
    }
    std::cout << "Unknown attribute " << attr_str << "\n";
    return WarriorAttr::kAttack;
  }

  void ParseWarriorAttributeRange(int data_index, std::string value, AttrRange &attr_range){
    switch(data_index){
      case static_cast<int>(AttrRangeDescrip::kAttr):
        attr_range.attr = MapAttr(value);
        //attr_range.attr = value;
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

  void GenWarriors(std::vector<Warrior> &warrior_pool){
    std::cout << "Leyendo rangos de atributos...\n";
    std::vector<AttrRange> warrior_attrs_range;
    utils::ReadCsv("data/ranges.csv", warrior_attrs_range, warrior::ParseWarriorAttributeRange);
    
    std::cout << "Generando gerreros...\n";
    for(AttrRange attr_range : warrior_attrs_range){
      for(int i{0}; i < Constants::kWarriorsPool; ++i){
        if(attr_range.attr == WarriorAttr::kAttack){
          warrior_pool.at(i).attack = 
            utils::RandomInInterval(attr_range.min, attr_range.max);
          // Debug
          warrior_pool.at(i).final_attack = warrior_pool.at(i).attack;

        }else if(attr_range.attr == WarriorAttr::kDefense){
          warrior_pool.at(i).defense = 
            utils::RandomInInterval(attr_range.min, attr_range.max);
          // Debug
          warrior_pool.at(i).final_defense = warrior_pool.at(i).defense;

        }else if(attr_range.attr == WarriorAttr::kShield){
          warrior_pool.at(i).shield = 
            utils::RandomInInterval(attr_range.min, attr_range.max);
          // Debug
          warrior_pool.at(i).final_shield = warrior_pool.at(i).shield;
          
        }else if(attr_range.attr == WarriorAttr::kHealth){
          warrior_pool.at(i).health = 
            utils::RandomInInterval(attr_range.min, attr_range.max);

        }else if(attr_range.attr == WarriorAttr::kHealthReg){
          warrior_pool.at(i).health_reg = 
            utils::RandomInInterval(attr_range.min, attr_range.max);

        }else if(attr_range.attr == WarriorAttr::kAggressive){
          warrior_pool.at(i).aggressive = 
            utils::RandomInInterval(attr_range.min, attr_range.max);

        }else if(attr_range.attr == WarriorAttr::kIntel){
          warrior_pool.at(i).intel = 
            utils::RandomInInterval(attr_range.min, attr_range.max);

        }else if(attr_range.attr == WarriorAttr::kControlResis){
          warrior_pool.at(i).control_resis = 
            utils::RandomInInterval(attr_range.min, attr_range.max);

        }else if(attr_range.attr == WarriorAttr::kControl){
          warrior_pool.at(i).control = 
            utils::RandomInInterval(attr_range.min, attr_range.max);

        }else if(attr_range.attr == WarriorAttr::kBuild){
          warrior_pool.at(i).build = 
            utils::RandomInInterval(attr_range.min, attr_range.max);
        }
      }
    }
  }
}
