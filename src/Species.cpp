
#include <cstdlib>

#include "Species.h"

Species::Species() : fitness(0.0)
{
}

void Species::append(Genome *g)
{
  population.push_back(g);
  fitness += g->fitness;
}

double Species::distance(Genome *g)
{
  double E = 0.0, D = 0.0, W = 0.0, n = 0;

  if(population.size() == 0) return 0.0;

  Genome *rep = population[0];

  std::sort(rep->connections.begin(), rep->connections.end(), neat_connection::compare);
  std::sort(g->connections.begin(), g->connections.end(), neat_connection::compare);

  auto c1 = rep->connections.begin();
  auto c2 = g->connections.begin();

  while(c1 != rep->connections.end() && c2 != g->connections.end()) {
    int innov1 = (*c1)->innovation_number;
    int innov2 = (*c2)->innovation_number;
    if(innov1 == innov2) {
      W += abs((*c1)->weight - (*c2)->weight);
      n++;
      c1++;
      c2++;
    } else if(innov1 < innov2) {
      D++;
      c1++;
    } else {
      D++;
      c2++;
    }
  }

  while(c1 != rep->connections.end()) {
    E++;
    c1++;
  }

  while(c2 != g->connections.end()) {
    E++;
    c2++;
  }

  W = W / n;
  
  unsigned int len1 = rep->connections.size();
  unsigned int len2 = g->connections.size();
  unsigned int N = (len1 < 20 && len2 < 20) ? 1.0 : len1 + len2;
  double c1 = neat_options::EXCESS_CONSTANT;
  double c2 = neat_options::DISJOINT_CONSTANT;
  double c3 = neat_options::WEIGHTDIFF_CONSTANT;

  return ((c1 * E) / N) + ((c2 * D) / E) + (c3 * W);
}

double Species::get_fitness()
{
  return fitness / population.size();
}
