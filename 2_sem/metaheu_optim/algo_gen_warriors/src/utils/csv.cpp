#include <fstream>

#include "csv.hpp"

namespace utils{
  void Export(const std::vector<Warrior> &warrior_pool){
    std::ofstream write_file;
    write_file.open("output/pool.csv", std::ofstream::trunc);
    write_file 
      << "index" << ","
      << "attack" << "," 
      << "defense" << "," 
      << "shield" << "," 
      << "health" << "," 
      << "health_reg" << "," 
      << "aggressive" << "," 
      << "intel" << "," 
      << "control_resis" << "," 
      << "control" << "," 
      << "build" << "," 
      << "final_attack" << "," 
      << "final_defense" << "," 
      << "final_shield" << "\n";

    int index = 1;
    for(Warrior w : warrior_pool){
      write_file 
        << index << ","
        << w.attack << "," 
        << w.defense << "," 
        << w.shield << "," 
        << w.health << "," 
        << w.health_reg << "," 
        << w.aggressive << "," 
        << w.intel << "," 
        << w.control_resis << "," 
        << w.control << "," 
        << w.build << "," 
        << w.final_attack << "," 
        << w.final_defense << "," 
        << w.final_shield << "\n";
      ++index;
    }
    write_file.close();   
  }

  void SaveScores(const std::vector<double> &scores){
    std::ofstream write_file;
    write_file.open("output/best.csv", std::ofstream::trunc);
    write_file << "gen,max_score\n";
    int index = 1;
    for(double score : scores){
      write_file << index << "," << score << "\n";
      ++index;
    }
    write_file.close();
  }
}

