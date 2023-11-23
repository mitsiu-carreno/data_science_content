#ifndef ATTR_RANGE_HPP
#define ATTR_RANGE_HPP

#include <string>

enum class AttrRangeDescrip{
  kAttr,
  kMin,
  kMax
};

struct AttrRange{
  //std::string attr;
  WarriorAttr attr;
  int min;
  int max;
};

#endif
