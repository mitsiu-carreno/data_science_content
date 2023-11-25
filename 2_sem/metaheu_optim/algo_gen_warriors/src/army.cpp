#include <iostream>

#include "army.hpp"
#include "gen-random.hpp"
#include "constants.hpp"

namespace Army{
  long Score(const std::set<int> &army, const std::vector<Warrior> &warrior_pool){
    int score {0};
    for (std::set<int>::iterator it=army.begin(); it!=army.end(); ++it){
      score += warrior_pool.at(*it).final_attack 
        + warrior_pool.at(*it).final_defense
        + warrior_pool.at(*it).final_shield;
    }
    return score;
  }

  void Generate(const int n_armies, const int n_warriors, std::set<ArmyT, ArmyComparator> &armies, const std::vector<Warrior> &warrior_pool){
    std::cout << "Generando ejercitos aleatorios\n";
    while(static_cast<int>(armies.size()) < n_armies){
      ArmyT new_army;
      while(static_cast<int>(new_army.warriors.size()) < n_warriors){
        new_army.warriors.insert(utils::RandomInInterval(0, Constants::kWarriorsPool -1));
      }
      new_army.score = Score(new_army.warriors, warrior_pool);
      armies.insert(new_army);
    } 
  }

  void Crossover(const std::set<int> &parent_1, const std::set<int> &parent_2, std::set<int> &new_army){
    std::cout << "Parent_1\n";
    for(int w_id : parent_1){
      std::cout << w_id << "\t";
    }
    std::cout << "\nParent_2\n";
    for(int w_id : parent_2){
      std::cout << w_id << "\t";
    }
    std::cout << "\n";
  }
}
