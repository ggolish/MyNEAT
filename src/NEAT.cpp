
#include <cstdio>
#include <cmath>

#include "NEAT.h"
#include "options.h"

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

// Splits the current population into species based on the genome
// distance function
std::vector<Species *> NEAT::speciate()
{
  std::vector<Species *> species_list;
  for(auto g = population.begin(); g != population.end(); ++g) {
    bool new_species = true;
    for(auto s = species_list.begin(); s != species_list.end(); ++s) {
      double distance = (*s)->distance((*g));
      if(distance < neat_options::DISTANCE_THRESHOLD) {
        (*s)->append((*g));
        new_species = false;
      }
    }
    if(new_species == true) {
      Species *s = new Species();
      s->append((*g));
      species_list.push_back(s);
    }
  }

  // Empty the population array
  population.clear();

  // Calculate total fitness
  double total_fitness = 0.0;
  for(auto s = species_list.begin(); s != species_list.end(); ++s) {
    total_fitness += (*s)->get_fitness();
  }

  // Assign portions of next population to each species
  double x = 0.0;
  for(auto s = species_list.begin(); s != species_list.end() - 1; ++s) {
    (*s)->portion = floor(((*s)->get_fitness() / total_fitness) * population_size);
    x += (*s)->portion;
  }
  species_list.back()->portion = population_size - x;

  return species_list;
}


void NEAT::repopulate(const std::vector<double> &fitnesses)
{
  // Set the fitness for each genome
  if(fitnesses.size() != population_size) {
    std::cerr << "Error: Invalid fitness array size." << std::endl;
    return;
  }

  for(unsigned int i = 0; i < population_size; ++i) {
    population[i]->fitness = fitnesses[i];
  }

  // Split the population into species
  std::vector<Species *> species_list = speciate();

  // Repopulate using the species
  for(auto s = species_list.begin(); s != species_list.end(); ++s) {
    std::cout << *(*s) << std::endl;
    for(int i = 0; i < (*s)->portion; ++i) {
      Genome *g = (*s)->tournament();
      // Mutations / Crossover will happen here
      population.push_back(g);
    }
    // The old genomes can be destroyed here
  }

  // The species objects can be destroyed here
}
