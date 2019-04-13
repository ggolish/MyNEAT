#ifndef NEAT_NEAT_H_
#define NEAT_NEAT_H_

#include <vector>

#include "Genome.h"
#include "Species.h"
#include "InnovationMap.h"

class NEAT {
 public:
  unsigned int population_size;
  std::vector<Genome *> population;
  InnovationMap *node_innov, *conn_innov;

  NEAT(unsigned int population_size, int ninputs, int noutputs);
  std::vector<double> feed_forward(unsigned int index, const std::vector<double> &inputs);
  std::vector<std::vector<double>> feed_forward_all(const std::vector<double> &inputs);
  std::vector<Species *> speciate();
  void repopulate(const std::vector<double> &fitnesses);
};

#endif
