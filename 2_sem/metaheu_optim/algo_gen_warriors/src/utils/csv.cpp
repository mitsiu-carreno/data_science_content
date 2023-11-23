#include "attr-range.hpp"
#include "csv.hpp"

namespace utils{
  void ParseEntity(int data_index, std::string value, AttrRange &attr_range){
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
}

