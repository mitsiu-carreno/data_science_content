#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <string>

enum class ContainerAttr{
  kCode,
  kCost,
  kCharge,
  kImmediacy,
  kPriority,
  kWeight
};

struct Container{
  std::string code;
  float cost;
  float charge;
  int immediacy;
  int priority;
  float weight;
};

#endif
