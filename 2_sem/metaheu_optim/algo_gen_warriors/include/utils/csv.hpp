#ifndef CSV_HPP
#define CSV_HPP

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <string>

#include "attr-range.hpp"

namespace utils{
  
  //void ParseEntity(int, std::string, AttrRange &);

  template <typename T> 
    void ReadCsv(std::string path, std::vector<T> &vec, void (*parser)(int, std::string, T&)){
      
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
            parser(index, value, new_entity);
          }catch(const std::exception &e){
            std::cout << "Error al importar " << path << " " << row << ":" << index  << " con valor "<< value << "\n";
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
