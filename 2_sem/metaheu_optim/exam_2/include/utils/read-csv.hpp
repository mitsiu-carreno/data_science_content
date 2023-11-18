#ifndef READ_CSV_HPP
#define READ_CSV_HPP

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <string>

#include "ship.hpp"
#include "container.hpp"

namespace utils{

  enum class ParseEntities{
    kShip,
    kContainer
  };
  
  void ParseEntity(int, std::string, Ship &);
  void ParseEntity(int, std::string, Container &);

  template <typename T> 
    void ReadCsv(std::string path, utils::ParseEntities entity, std::vector<T> &vec){
      
      std::ifstream read_file(path);
      std::string line;
      int row = 1;
   
      while(std::getline(read_file, line)){
        if(row == 1){
          ++row;
          continue;
        }
        std::stringstream lineStream(line);
        std::string value;
        
        T new_entity;
  
        int index = 0;
        while(std::getline(lineStream, value, ',')){
          try{
            //if(entity == ParseEntities::kShip){
              utils::ParseEntity(index, value, new_entity);
            //}
            //else if(entity == ParseEntities::kContainer){
              //utils::ParseContainer(index, value, new_entity);
            //}
          }catch(const std::exception &e){
            std::cout << "Error al importar " << static_cast<int>(entity) << " (0 barco, 1 container) " << row << ":" << index  << " con valor "<< value << "\n";
          }
          ++index;
        }

        vec.push_back(new_entity);
        ++row;
      }
    }
  // End-template
}

#endif
