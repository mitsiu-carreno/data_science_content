#ifndef PROBLEM_META_HPP
#define PROBLEM_META_HPP

#include <vector>

struct ProblemMetadata{
  int k;  // Num groups
  int ni;  // Num example
  int N;  // Total exampes
  std::vector<std::vector<float>> data;
  std::vector<float> avgs;
  float total_avg;
};

#endif
