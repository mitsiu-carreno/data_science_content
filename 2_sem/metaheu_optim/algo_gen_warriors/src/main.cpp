#include <vector>
#include <iostream>
#include <set>

#include "warrior.hpp"
#include "constants.hpp"
#include "army.hpp"
#include "csv.hpp"

int main(){

  std::vector<Warrior> warrior_pool(Constants::kWarriorsPool);
  warrior::GenWarriors(warrior_pool);

  std::set<ArmyT, ArmyComparator> armies;
  Army::Generate(Constants::kArmyPopulation, Constants::kWarriorsInArmy, armies, warrior_pool);

  
  utils::Export(warrior_pool);
  
  int tot_armies_selection = Constants::kArmyPopulation 
    * (Constants::kPercentagePopulationSelection / 100.0);

  tot_armies_selection = tot_armies_selection % 2 == 0 ? 
    tot_armies_selection 
    : tot_armies_selection + 1;

  std::vector<double> all_scores;
  for(int n_gen {0}; n_gen < Constants::kNGenerations; ++n_gen){


    std::cout << "////////////////////////////////////////////\nGen " << n_gen << "\n";
    std::cout << "Current armies\n";
    for(ArmyT army : armies){
      std::cout << army.score << " - ";
      for(int w_id : army.warriors){
        std::cout << w_id << "\t";
      }
      std::cout << "\n";
    }

    std::cout << "Seleccionando y cruzando mejores parejas\n"; 
    // Iteramos por par nuestros indices seleccionados
    std::set<ArmyT, ArmyComparator>::iterator last_selected = armies.begin();
    std::advance(last_selected, tot_armies_selection);

    std::set<ArmyT, ArmyComparator> new_gen_armies;

    for(std::set<ArmyT, ArmyComparator>::iterator it = armies.begin(); it != last_selected; std::advance(it, 2)){

      // Generamos una nueva solución combinando las anteriores seleccionadas
      Army::Crossover(it->warriors, std::next(it)->warriors, Constants::kWarriorsInArmy, new_gen_armies, warrior_pool);
    }

    std::cout << "New gen armies\n";
    for(ArmyT army : new_gen_armies){
      std::cout << army.score << " - ";
      for(int w_id : army.warriors){
        std::cout << w_id << "\t";
      }
      std::cout << "\n";
    }
  
    std::cout << "Uniendo nueva generación a la población previa (elitismo)...\n";
    armies.insert(new_gen_armies.begin(), new_gen_armies.end());

    std::cout << "Borrando peores ejercitos...\n";

    std::set<ArmyT, ArmyComparator>::iterator cut_it = armies.begin();
    std::advance(cut_it, Constants::kArmyPopulation);

    armies.erase(cut_it, armies.end());

    std::cout << "Tamaño de población: " << armies.size() << "\n";

    all_scores.push_back(armies.begin()->score);
  }
  

  utils::SaveScores(all_scores);
  std::cout << "Resultado final: \n";
  std::set<ArmyT, ArmyComparator>::iterator best_it = armies.begin();

  std::cout << best_it->score << " - ";
  for(int w_id : best_it->warriors){
    std::cout << w_id << "\t";
  }
  std::cout << "\n";
  return 0;
}
