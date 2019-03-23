
#include "NEAT.h"

NEAT::NEAT(int population_size, int ninputs, int noutputs) :
  population_size(population_size)
{
  for(int i = 0; i < population_size; ++i)
    population.emplace_back(ninputs, noutputs);
}
