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
    std::cout << "Generando y evaluando ejercitos aleatorios\n";
    while(static_cast<int>(armies.size()) < n_armies){
      ArmyT new_army;
      while(static_cast<int>(new_army.warriors.size()) < n_warriors){
        new_army.warriors.insert(utils::RandomInInterval(0, Constants::kWarriorsPool -1));
      }
      new_army.score = Score(new_army.warriors, warrior_pool);
      armies.insert(new_army);
    } 
  }

  void Crossover(const std::set<int> &parent_1, const std::set<int> &parent_2, const int n_warriors, std::set<ArmyT, ArmyComparator> &new_gen_armies, const std::vector<Warrior> &warrior_pool){
    // Child getting one-one bite from parents front to back
    ArmyT child_1;
    std::set<int>::iterator it_p1 = parent_1.begin();
    std::set<int>::iterator it_p2 = parent_2.begin();
    
    while(static_cast<int>(child_1.warriors.size()) < n_warriors){
      // If parents still have positions to iterate [0, n_warriors]
      if(it_p1 != parent_1.end()){
        child_1.warriors.insert(*it_p1);
        if(static_cast<int>(child_1.warriors.size()) < n_warriors){
          child_1.warriors.insert(*it_p2);
        }
        std::advance(it_p1, 1);
        std::advance(it_p2, 1);
      }else{
        // If end of parents positions is reached, add rands
        child_1.warriors.insert(utils::RandomInInterval(0, Constants::kWarriorsPool -1));
      }
    }
    child_1.score = Score(child_1.warriors, warrior_pool);

    new_gen_armies.insert(child_1);

    // Child getting one-one bite from parents back to front
    ArmyT child_2;

    std::set<int>::reverse_iterator rit_p1 = parent_1.rbegin();
    std::set<int>::reverse_iterator rit_p2 = parent_2.rbegin();

    while(static_cast<int>(child_2.warriors.size()) < n_warriors){
      // If parents still have positions to iterate [n_warriors, 0]
      if(rit_p1 != parent_1.rend()){
        child_2.warriors.insert(*rit_p1);
        if(static_cast<int>(child_2.warriors.size()) < n_warriors){
          child_2.warriors.insert(*rit_p2);
        }
        std::advance(rit_p1, 1);
        std::advance(rit_p2, 1);
      }else{
        // If rend of parents position is reached, add rands
        child_2.warriors.insert(utils::RandomInInterval(0, Constants::kWarriorsPool -1));
      }
    }
    child_2.score = Score(child_2.warriors, warrior_pool);

    new_gen_armies.insert(child_2);


    std::cout << "Parent_1\n";
    for(int w_id : parent_1){
      std::cout << w_id << "\t";
    }
    std::cout << "\nParent_2\n";
    for(int w_id : parent_2){
      std::cout << w_id << "\t";
    }
    std::cout << "\nChild_forward\n";
    for(int w_id : child_1.warriors){
      std::cout << w_id << "\t";
    }
    std::cout << "\nChild backward\n";
    for(int w_id : child_2.warriors){
      std::cout << w_id << "\t";
    }
    std::cout << "\n\n";
  }
}
