//https://stackoverflow.com/questions/39668561/allocate-n-bytes-by-new-and-fill-it-with-any-type

#include <vector>
#include <iostream>

#include "warrior.hpp"
#include "constants.hpp"

int main(){

  std::vector<Warrior> warrior_pool(Constants::kWarriorsPool);
  warrior::GenWarriors(warrior_pool);
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
