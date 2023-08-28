#include <iostream>
#include <vector>

//Forgive me god I have sinned
const int n_cities = 5;
const int n_solutions = 5;

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
  float *city_distances = new float[size] {4,7,2,5,10,5,3,11,7,4};
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

  int offset = 0;
  for(int i=1; i<city_A; ++i){
    offset += n_cities - i;
  }
  return city_distances[offset + (city_B - city_A -1)];
}

void GenSolutions(int *solutions[n_solutions][n_cities], bool random=false){
  int n = 1;
  for(int i = 0; i< n_solutions; ++i){
    for(int j=0; j< n_cities; ++j){
      *solutions[i][j] = n;
      ++n;
    }
  }
}

int main(){
  // Generate distance vector based on n cities
  float *city_distances = CreateMap(n_cities);

  int solutions [n_solutions][n_cities];
  GenSolutions(&solutions, true);
//Debug 
  for(int i = 0; i< n_solutions; ++i){
    for(int j=0; j< n_cities; ++j){
      std::cout << solutions[i][j] << "\n";
    }
  }
//Debug

  delete[] city_distances;
  return 0;
}
