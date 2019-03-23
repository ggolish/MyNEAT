#ifndef NEAT_NEAT_H_
#define NEAT_NEAT_H_

#include <vector>

#include "Genome.h"

class NEAT {
 public:
  int population_size;
  std::vector<Genome> population;

  NEAT(int population_size, int ninputs, int noutputs);
};

#endif
