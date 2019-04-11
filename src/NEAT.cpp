
#include <cstdio>

#include "NEAT.h"

NEAT::NEAT(unsigned int population_size, int ninputs, int noutputs) :
  population_size(population_size)
{
  for(unsigned int i = 0; i < population_size; ++i)
    population.push_back(new Genome(ninputs, noutputs));

  node_innov = new InnovationMap(ninputs + noutputs + 1);
  conn_innov = new InnovationMap(ninputs * noutputs);
}

// Feeds inputs to a single network and returns outputs
std::vector<double> NEAT::feed_forward(unsigned int index, const std::vector<double> &inputs)
{
  std::vector<double> outputs;
  
  if(index >= population_size) {
    std::fprintf(stderr, "Error: Invalid population index: %u\n", index);
    return outputs;
  }

  outputs = population[index]->feed_forward(inputs);
  return outputs;
}

// Feeds inputs to all networks and returns outputs
std::vector<std::vector<double>> NEAT::feed_forward_all(const std::vector<double> &inputs)
{
  std::vector<std::vector<double>> output_list;

  std::vector<Genome *>::iterator g;
  for(g = population.begin(); g != population.end(); ++g) {
    output_list.push_back((*g)->feed_forward(inputs));
  }
  
  return output_list;
}
