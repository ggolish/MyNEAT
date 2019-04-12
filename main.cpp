#include <iostream>
#include <vector>

#include "NEAT.h"
#include "utilities.h"

int main()
{
  NEAT neat(3, 2, 1);
  neat_genetics::add_node(neat.population[0], neat.node_innov, neat.conn_innov);
  neat_genetics::add_connection(neat.population[0], neat.conn_innov);
  neat.population[0]->fitness = 10.0;
  neat.population[1]->fitness = 1.0;
  Genome *baby = neat_genetics::crossover(neat.population[0], neat.population[1]);
  std::cout << *neat.population[0] << std::endl;
  std::cout << *neat.population[1] << std::endl;
  std::cout << *baby << std::endl;
  return 0;
}
