#ifndef READ_CSV_HPP
#define READ_CSV_HPP

#include <string>

namespace utils{

  enum class ParseEntities{
    kShip,
    kContainer
  };

  void ReadCsv(std::string, utils::ParseEntities);
  void ParseCsv(utils::ParseEntities, int, std::string);
}

#endif
