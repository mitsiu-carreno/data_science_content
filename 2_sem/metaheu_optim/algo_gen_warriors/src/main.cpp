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
  
  int tot_armies_selection = Constants::kArmyPopulation 
    * (Constants::kPercentagePopulationSelection / 100.0);

  tot_armies_selection = tot_armies_selection % 2 == 0 ? 
    tot_armies_selection 
    : tot_armies_selection + 1;
  
  // Iteramos por par nuestros indices seleccionados
  std::set<ArmyT, ArmyComparator>::iterator last_selected = armies.begin();
  std::advance(last_selected, tot_armies_selection);

  for(std::set<ArmyT, ArmyComparator>::iterator it = armies.begin(); it != last_selected; std::advance(it, 2)){
    std::cout << "In\n";

    std::set<ArmyT, ArmyComparator>::iterator next_it = std::next(it);
    
    // Resetamos nuestos iteradores al inicio de las soluciones
    //std::set<ArmyT, ArmyComparator>::iterator first_army = armies.begin();
    //std::set<ArmyT, ArmyComparator>::iterator second_army = armies.begin();

    // Adelantamos el apuntador a la posici├│n del primer indice seleccionado
    //std::advance(first_army, it);
    //std::advance(second_army, *next_it);
    
    // Generamos una nueva solución combinando las anteriores seleccionadas
    std::set<int> new_army;
    Army::Crossover(it->warriors, next_it->warriors, new_army);
    //new_gen.insert()
  }


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
