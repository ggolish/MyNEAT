#include <iostream>
#include <vector>

#include "NEAT.h"
#include "utilities.h"

int main()
{
  NEAT neat(3, 2, 1);
  std::vector<double> fitnesses {0.54, 0.32, 0.98};
  std::cout << neat.population_size << std::endl;
  neat.repopulate(fitnesses);
  std::cout << neat.population_size << std::endl;
  return 0;
}
