#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>

#include "problem-metadata.hpp"
#include "utils.hpp"

float VectorAverage(std::vector<float> const& v){
  if(v.empty()){
    return 0;
  }

  auto const count = static_cast<float>(v.size());
  return std::reduce(v.begin(), v.end()) / count;
}

void DefineProblem(ProblemMetadata &p_meta){
  utils::AskValue("\nIngresa la cantidad de grupos", &p_meta.k, utils::kInteger);
  p_meta.data.resize(p_meta.k);

  utils::AskValue("\nIngresa la cantidad de ejemplos por grupo", &p_meta.ni, utils::kInteger);

  p_meta.N = p_meta.k * p_meta.ni;
 
  for(int group {0}; group < p_meta.k; group++){
    p_meta.data.at(group).resize(p_meta.ni);
    for(int example {0}; example < p_meta.ni; example++){
      std::string prompt = std::string("\nIngresa el dato del grupo ") 
        + std::to_string(group+1)
        + std::string(", renglon ")
        + std::to_string(example+1); 

      utils::AskValue(prompt, &(p_meta.data.at(group).at(example)), utils::kFloat);
    }
  }
}

int main(){
  
  try{
    ProblemMetadata p_meta;
    DefineProblem(p_meta);

    p_meta.avgs.resize(p_meta.k);

    for(int group{0}; group < p_meta.k; group++){
      p_meta.avgs.at(group) = VectorAverage(p_meta.data.at(group));
    }

    p_meta.total_avg = VectorAverage(p_meta.avgs);


    for(int group{0}; group < p_meta.k; group++){
      std::cout << "Promedio grupo " << group +1 << ": " << p_meta.avgs.at(group);
    }
    std::cout << "Promedio general: " << p_meta.total_avg << "\n";

    std::cout << "\n------------------------------------\nFactor: \n";
 
    float factor_suma = 0;
    for(int group {0}; group < p_meta.k; group++){
      factor_suma += p_meta.ni * std::pow((p_meta.avgs.at(group) - p_meta.total_avg), 2);
    }
  
    std::cout << "Factor. Suma de cuadrados: " << factor_suma << "\n";

    std::cout << "Factor. Grados de libertad: " << p_meta.k -1 << "\n";

    std::cout << "Factor. Cuadrado medio: " << factor_suma/(p_meta.k - 1) << "\n";

    float error_suma = 0;
    for(int group {0}; group < p_meta.k; group++){
      for(int example {0}; example < p_meta.ni; example++){
        error_suma += std::pow((p_meta.data.at(group).at(example) - p_meta.avgs.at(group)), 2);
      }
    }

    
    std::cout << "\n------------------------------------\nError: \n";

    std::cout << "Error. Suma de cuadrados: " << error_suma << "\n";

    std::cout << "Error. Grados de libertad: " << p_meta.N - p_meta.k << "\n";
    
    std::cout << "Error. Cuadrado medio: " << error_suma/(p_meta.N - p_meta.k) << "\n";

    std::cout << "Factor. F: " << (factor_suma/(p_meta.k -1))/(error_suma/(p_meta.N - p_meta.k)) << "\n";


    std::cout << "\n------------------------------------\nTotal: \n";
    
    float total_suma = 0;

    for(int group {0}; group < p_meta.k; group++){
      for(int example {0}; example < p_meta.ni; example++){
        total_suma += std::pow((p_meta.data.at(group).at(example) -  p_meta.total_avg), 2);
      }
    }
    
    std::cout << "Total. Suma de cuadrados: " << total_suma << "\n";
  
    std::cout << "Total. Grados de libertad: " << p_meta.N - 1 << "\n";

  }catch(const std::exception &e){
    std::cout << "Ha ocurrido un error:\n" << e.what() << "\n Terminando programa\n";
  }
  
  return 0;
}
