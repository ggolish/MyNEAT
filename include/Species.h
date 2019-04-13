#ifndef NEAT_SPECIES_H_
#define NEAT_SPECIES_H_

#include <vector>

#include "Genome.h"

class Species
{
  private:
    double fitness;
  public:
    std::vector<Genome *> population;

    Species();
    void append(Genome *g);
    double distance(Genome *g);
    double get_fitness();
};

#endif
