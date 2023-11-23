//https://stackoverflow.com/questions/39668561/allocate-n-bytes-by-new-and-fill-it-with-any-type

#include <vector>
#include <iostream>

#include "warrior.hpp"
#include "constants.hpp"

int main(){

  std::vector<Warrior> army;
  warrior::GenWarriors(army);
  std::cout << army.at(0).control <<"\n";
  
  return 0;
}
