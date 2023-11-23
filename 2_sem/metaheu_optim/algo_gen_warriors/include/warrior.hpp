#ifndef WARRIOR_HPP
#define WARRIOR_HPP

#include <vector>

enum class WarriorAttr{
  kAttack,
  kDefense,
  kShield,
  kHealth,
  kHealthReg,
  kAggressive,
  kIntel,
  kControlResis,
  kControl,
  kBuild
};

struct Warrior{
  int attack;
  int defense;
  int shield;
  int health;
  int health_reg;
  int aggressive;
  int intel;
  int control_resis;
  int control;
  int build;

  Warrior(){}

  Warrior(int attack, int defense, int shield, int health, int health_reg, int aggressive, int intel, int control_resis, int control, int build) : 
    attack {attack},
    defense {defense},
    shield {shield},
    health {health},
    health_reg {health_reg},
    aggressive {aggressive},
    intel {intel},
    control_resis {control_resis},
    control {control},
    build {build}
  {}
};

namespace warrior{
  void GenWarriors(std::vector<Warrior> &);
}

#endif
