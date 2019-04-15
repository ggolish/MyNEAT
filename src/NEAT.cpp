
#include <algorithm>
#include <cstdio>
#include <cmath>

#include "NEAT.h"
#include "utilities.h"
#include "options.h"

NEAT::NEAT(unsigned int population_size, int ninputs, int noutputs) :
  population_size(population_size), ninputs(ninputs), noutputs(noutputs)
{
  for(unsigned int i = 0; i < population_size; ++i)
    population.push_back(new Genome(ninputs, noutputs));

  node_innov = new InnovationMap(ninputs + noutputs + 1);
  conn_innov = new InnovationMap(ninputs * noutputs + noutputs + 1);
}

NEAT::~NEAT()
{
  for(auto g = population.begin(); g != population.end(); ++g) {
    delete (*g);
  }

  for(auto s = species_list.begin(); s != species_list.end(); ++s) {
    delete (*s);
  }

  delete node_innov;
  delete conn_innov;
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
void NEAT::speciate()
{
  for(auto g = population.begin(); g != population.end(); ++g) {
    bool new_species = true;
    for(auto s = species_list.begin(); s != species_list.end(); ++s) {
      double distance = (*s)->distance((*g));
      if(distance < neat_options::DISTANCE_THRESHOLD) {
        (*s)->append((*g));
        new_species = false;
        break;
      }
    }
    if(new_species == true) {
      Species *s = new Species((*g));
      s->append((*g));
      species_list.push_back(s);
    }
  }

  // Empty the population array
  population.clear();

  // Calculate total fitness
  double total_fitness = 0.0;
  for(auto s = species_list.begin(); s != species_list.end();) {
    if((*s)->population.size() > 0) {
      if((*s)->portion != -1.0)
        total_fitness += (*s)->get_fitness();
      s++;
    } else {
      species_list.erase(s);
    }
  }

  // Assign portions of next population to each species
  for(auto s = species_list.begin(); s != species_list.end(); ++s) {
    if((*s)->portion == -1.0) {
      (*s)->portion = 0.0;
    } else {
      (*s)->portion = ceil(((*s)->get_fitness() / total_fitness) * population_size);
    }
  }
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
  speciate();

  // Repopulate using the species
  for(auto s = species_list.begin(); s != species_list.end(); ++s) {
    // Eliteism, copy best from each sufficiently large species
    if((*s)->population.size() > 5 && (*s)->portion != -1) {
      population.push_back((*s)->champion->copy());
      (*s)->portion--;
    }
    for(int i = 0; i < (*s)->portion; ++i) {
      double prob = neat_random::uniform(0, 1);
      Genome *g = (*s)->tournament();

      // Mutate connection weights
      prob = neat_random::uniform(0, 1);
      if(prob < neat_options::CONNECTION_MUTATION_RATE) {
        prob = neat_random::uniform(0, 1);
        if(prob < neat_options::PERTURB_MUTATION_RATE) {
          neat_genetics::perturb_connection(g);
        } else {
          neat_genetics::replace_connection(g);
        }
      }

      // Toggle connection weight
      prob = neat_random::uniform(0, 1);
      if(prob < neat_options::TOGGLE_MUTATION_RATE) {
        neat_genetics::toggle_connection(g);
      }

      // Structural mutations
      prob = neat_random::uniform(0, 1);
      if(prob < neat_options::ADDNODE_MUTATION_RATE) {
        neat_genetics::add_node(g, node_innov, conn_innov);
      }

      prob = neat_random::uniform(0, 1);
      if(prob < neat_options::ADDCONN_MUTATION_RATE) {
        neat_genetics::add_connection(g, conn_innov);
      }

      prob = neat_random::uniform(0, 1);
      if(prob > neat_options::MUTATION_RATE) {
        Genome *g2 = (*s)->tournament();
        Genome *child = neat_genetics::crossover(g, g2);
        population.push_back(child);
        delete g;
        delete g2;
      } else {
        population.push_back(g);
      }
    }
  }

  // Fix population size
  while(population.size() < population_size) {
    population.push_back(new Genome(ninputs, noutputs));
  }

  for(auto s = species_list.begin(); s != species_list.end(); ++s) {
    (*s)->reset();
  }
}

