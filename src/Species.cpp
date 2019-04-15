
#include <cstdlib>
#include <algorithm>

#include "Species.h"
#include "options.h"
#include "utilities.h"

Species::Species(Genome *rep) : fitness(0.0), portion(0.0), champion(NULL), best_fitness(0.0), unimprovement_counter(0)
{
  this->rep = rep->copy();
}

Species::~Species()
{
  if(population.size() > 0) {
    for(auto g = population.begin(); g != population.end(); g++) {
      delete (*g);
    }
  }

  if(rep) delete rep;
  if(champion) delete champion;
}

void Species::reset()
{
  fitness = 0.0;
  portion = 0.0;
  if(champion->fitness > best_fitness) {
    best_fitness = champion->fitness;
  } else {
    unimprovement_counter++;
    if(unimprovement_counter >= neat_options::UNIMPROVEMENT_LIMIT) {
      portion = -1.0;
    }
  }
  champion = NULL;
  int index = neat_random::randint(0, population.size() - 1);
  delete rep;
  rep = population[index]->copy();
  for(auto g = population.begin(); g != population.end(); g++) {
    delete (*g);
  }
  population.clear();
}

void Species::append(Genome *g)
{
  population.push_back(g);
  fitness += g->fitness;
  if(champion == NULL || g->fitness > champion->fitness)
    champion = g;
}

double Species::distance(Genome *g)
{
  double E = 0.0, D = 0.0, W = 0.0, n = 0;

  if(population.size() == 0) return 0.0;

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
  unsigned int N = 1.0;
  double C1 = neat_options::EXCESS_CONSTANT;
  double C2 = neat_options::DISJOINT_CONSTANT;
  double C3 = neat_options::WEIGHTDIFF_CONSTANT;

  return ((C1 * E) / N) + ((C2 * D) / N) + (C3 * W);
}

double Species::get_fitness() const
{
  return fitness / population.size();
}

double Species::get_fitness()
{
  return fitness / population.size();
}

// Chooses a genome from the population of the species via a tournament
Genome *Species::tournament()
{
  Genome *best = NULL;
  for(int i = 0; i < neat_options::TOURNAMENT_ROUNDS; ++i) {
    int index = neat_random::randint(0, population.size() - 1);
    Genome *curr = population[index];
    if(best == NULL || curr->fitness > best->fitness) {
      best = curr;
    }
  }
  return best->copy();
}

std::ostream &operator<<(std::ostream &os, const Species &species)
{
  os << "<Species " << &species << " ";
  os << "fitness=" << species.get_fitness() << " ";
  os << "size=" << species.population.size() << " ";
  os << "portion=" << species.portion;
  os << ">";
  return os;
}
