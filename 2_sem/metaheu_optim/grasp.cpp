/*
File: 
  grasp.cpp
Compile with:
  $ g++ -Wall -Werror -o grasp grasp.cpp && ./grasp
*/
#include <iostream>
#include <stdlib.h>   /* srand, rand*/
#include <time.h>     /* time */
#include <utility>    /* swap */
#include <algorithm>  /* std::copy*/
#include <iterator>   /* std::begin std::end*/
#include <math.h>       /* ceil */

const int n_cities = 5;
const int n_solutions = 5;
const int max_iterations = 10;

int GetFactorial(int n){
  if(n ==0){
    return 1;
  }
  return n * GetFactorial(n-1);
}

int GetDistancesArrayLen(int n_cities){
  //combination formula nCr = n!/(r!(n-r)!)
  int r = 2; //(joining two cities)
  
  return GetFactorial(n_cities)/(GetFactorial(r)*GetFactorial(n_cities - r));  
}

float* CreateMap(int n_cities){
   
  int size = GetDistancesArrayLen(n_cities);
  // todo interactive mode to input distances  
  //float *city_distances = new float[size] {4,7,2,5,10,5,3,11,7,4};
  float *city_distances = new float[size] {12, 5, 11, 42, 31, 23, 17, 6, 8, 3};
  return city_distances;
}

float GetCitiesDistance(int city_A, int city_B, float *city_distances){
  if(city_A == city_B){
    return 0;
  }
  
  if(city_A > city_B){
    int tmp = city_A;
    city_A = city_B;
    city_B = tmp;
  }

  if(city_B > n_cities){
    throw std::runtime_error("Error: Invalid city request");
  }

  int offset = 0;
  for(int i=1; i<city_A; ++i){
    offset += n_cities - i;
  }
  return city_distances[offset + (city_B - city_A -1)];
}

void GenSolutions(int solutions[n_solutions][n_cities + 1]){
  // Fill solutions ordered  1,2,3,4,5
  for(int i = 0; i< n_solutions; ++i){
    for(int j=0; j< n_cities; ++j){
      solutions[i][j] = j + 1 ;
    } 
  }

  // Randomize solutions
  int swaps_per_sol = 20;
  for(int i = 0; i < n_solutions; ++i){
    for(int j = 0; j < swaps_per_sol; ++j){
      int rnd_1 = rand() % n_cities;  // (max value);
      int rnd_2 = rand() % n_cities; 
      std::swap(solutions[i][rnd_1], solutions[i][rnd_2]);
    }
  }
}

void GenNeighborSolutions(int solutions[n_solutions][n_cities + 1], int best_solution_pos){
  // Copy best solution to start of solutions array
  std::copy(std::begin(solutions[best_solution_pos]), std::end(solutions[best_solution_pos]), std::begin(solutions[0]));

  for(int i=1; i < n_solutions; ++i){
    for(int j=0; j < n_cities; ++j){

      // First half of solutions    
      if(i <= ceil((float)(n_solutions-1)/2)){
        // Increment each city by one from the best one
        solutions[i][j] = (solutions[i-1][j] % 5) + 1; 
      }else{ 
        // Copy best solution and randomly swap two cities
        std::copy(std::begin(solutions[0]), std::end(solutions[0]), std::begin(solutions[i]));
        int rnd_1 = rand() % n_cities;  // (max value);
        int rnd_2 = rand() % n_cities; 
        std::swap(solutions[i][rnd_1], solutions[i][rnd_2]);
      }
    }
  }
}

int EvalSolutions(int solutions[n_solutions][n_cities + 1], float *city_distances){
  int best_solution_pos = 0;
  for(int i = 0; i < n_solutions; ++i){

    float total_distance = 0;

    for(int j = 0; j < n_cities -1; ++j){
      total_distance += GetCitiesDistance(solutions[i][j], solutions[i][j+1], city_distances);
    }

    if(total_distance < solutions[best_solution_pos][n_cities]){
      best_solution_pos = i;
    }

    solutions[i][n_cities] = total_distance;
  }
  return best_solution_pos;
}

void PrintSolutions(int solutions[n_solutions][n_cities + 1]){

  for(int i = 0; i< n_solutions; ++i){
    for(int j=0; j<= n_cities; ++j){
      std::cout << solutions[i][j] << "\t";
    }
    std::cout << "\n";
  }
  std::cout << "\n\n";
}

int main(){
  // Rand seed
  srand(time(NULL));
  
  float *city_distances = nullptr;  

  try{
    // Generate distance vector based on n cities
    city_distances = CreateMap(n_cities);

    int solutions [n_solutions][n_cities + 1];  // Last position per solution is for distance for that solution

    GenSolutions(solutions);
    int  best_solution_pos = EvalSolutions(solutions, city_distances);
    std::cout << "Initial random solutions\n";
    PrintSolutions(solutions);

    for(int i = 0; i < max_iterations; ++i){
      GenNeighborSolutions(solutions, best_solution_pos);
      best_solution_pos = EvalSolutions(solutions, city_distances);
      std::cout << "Solutons iteration " << i+1 << "\n";
      PrintSolutions(solutions);
    }

    std::cout << "Final solution\n";
    for(int i=0; i <= n_cities; ++i){
      std::cout << solutions[best_solution_pos][i] << "\t";
    }
    std::cout << "\n";
  }
  catch(const std::exception& e){
    std::cout << e.what() << "\n";
  }

  delete[] city_distances;
  return 0;
}
