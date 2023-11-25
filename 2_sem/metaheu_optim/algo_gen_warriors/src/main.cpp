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
  Army::Generate(Constants::kArmyPopulation, Constants::kWarriorsInArmy, armies, warrior_pool);
  
  int tot_armies_selection = Constants::kArmyPopulation 
    * (Constants::kPercentagePopulationSelection / 100.0);

  tot_armies_selection = tot_armies_selection % 2 == 0 ? 
    tot_armies_selection 
    : tot_armies_selection + 1;

  std::cout << "Seleccionando y cruzando mejores parejas\n"; 
  // Iteramos por par nuestros indices seleccionados
  std::set<ArmyT, ArmyComparator>::iterator last_selected = armies.begin();
  std::advance(last_selected, tot_armies_selection);

  std::set<ArmyT, ArmyComparator> new_gen_armies;

  for(std::set<ArmyT, ArmyComparator>::iterator it = armies.begin(); it != last_selected; std::advance(it, 2)){

    // Generamos una nueva solución combinando las anteriores seleccionadas
    std::set<int> new_army;
    Army::Crossover(it->warriors, std::next(it)->warriors, Constants::kWarriorsInArmy, new_gen_armies, warrior_pool);

  }
  std::cout << "New gen armies\n";
  for(ArmyT army : new_gen_armies){
    std::cout << army.warriors.size() << " - " << army.score << "\n";
  }
  
  std::cout << "Uniendo nueva generación a la población (elitismo)...\n";
  armies.insert(new_gen_armies.begin(), new_gen_armies.end());

  std::cout << "Inter size " << armies.size() << "\n";

  std::cout << "Borrando peores ejercitos...\n";

  std::set<ArmyT, ArmyComparator>::iterator cut_it = armies.begin();
  std::advance(cut_it, Constants::kArmyPopulation);

  armies.erase(cut_it, armies.end());

  std::cout << armies.size();

  for(auto army : armies){
    std::cout << army.warriors.size() << "\n";
  }


  /*POC

    merged.insert(y.begin(), y.end()); //add contents of y to merged

      // Creamos un iterador apuntando a donde comienza el corte de poblaci├│n
      auto cut_it = solutions.begin();
      std::advance(cut_it, new_pob_leng);
      
      std::cout << "Mantenemos top " << new_pob_leng << " soluciones y generamos nuevas aleatorias\n";
 
      // Borramos las soluciones fuera del porcentaje seleccionado
      solutions.erase(cut_it, solutions.end());

  
    */

  /*
  std::set<ArmyT, ArmyComparator>::iterator it = armies.begin();
  long mega_tot = 0;
  for(auto index : it->warriors){
    long tot = warrior_pool.at(index).final_attack + warrior_pool.at(index).final_defense + warrior_pool.at(index).final_shield;
    mega_tot +=tot;
    std::cout << index << " - " << tot << "\n";
  }
  std::cout << "Stored: " << it->score << " Computed: " << mega_tot << "\n"; 
  */
  /*

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
  */
  return 0;
}
