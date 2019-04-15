#ifndef NEAT_SPECIES_H_
#define NEAT_SPECIES_H_

#include <iostream>
#include <vector>

#include "Genome.h"

class Species
{
  private:
    double fitness;

  public:
    Genome *rep;
    std::vector<Genome *> population;
    double portion;
    Genome *champion;
    double best_fitness;
    int unimprovement_counter;

    Species(Genome *rep);
    ~Species();
    void reset();
    void append(Genome *g);
    double distance(Genome *g);
    double get_fitness() const;
    double get_fitness();
    Genome *tournament();
    friend std::ostream &operator<<(std::ostream &os, const Species &species);
};

#endif
