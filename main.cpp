#include <iostream>
#include <vector>

#include "NEAT.h"

int main()
{
  NEAT neat(3, 2, 1);
  std::vector<double> inputs{ 1, 1 };
  auto output_list = neat.feed_forward_all(inputs);
  int i = 0;
  for(auto outputs = output_list.begin(); outputs != output_list.end(); ++outputs) {
    std::cout << "Genome " << i++ << std::endl;
    for(auto output = outputs->begin(); output != outputs->end(); ++output) {
      std::cout << "  - " << (*output) << std::endl;
    }
    std::cout << std::endl;
  }
  return 0;
}
