#include <vector>
#include <iostream>
#include <set>

#include "warrior.hpp"
#include "constants.hpp"
#include "army.hpp"

int main(){

  std::vector<Warrior> warrior_pool(Constants::kWarriorsPool);
  std::cout << warrior_pool.size() << "\n";
  warrior::GenWarriors(warrior_pool);

  std::set<ArmyT, ArmyComparator> armies;
  Army::Generate(Constants::kArmyPopulation, Constants::kWarrirosInArmy, armies, warrior_pool);

  

  for(int i{Constants::kWarriorsPool - 10}; i < Constants::kWarriorsPool -1; ++i){
  
    std::cout << 
      warrior_pool.at(i).attack 
      << ",\t" <<
      warrior_pool.at(i).defense
      << ",\t" <<
      warrior_pool.at(i).shield 
      << ",\t" <<
      warrior_pool.at(i).health 
      << ",\t" <<
      warrior_pool.at(i).health_reg 
      << ",\t" <<
      warrior_pool.at(i).aggressive
      << ",\t" <<
      warrior_pool.at(i).intel
      << ",\t" <<
      warrior_pool.at(i).control_resis 
      << ",\t" <<
      warrior_pool.at(i).control
      << ",\t" <<
      warrior_pool.at(i).build
      <<"\n";
  }
  
  return 0;
}
