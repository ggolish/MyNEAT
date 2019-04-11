#include <iostream>
#include <vector>

#include "NEAT.h"
#include "utilities.h"

int main()
{
  NEAT neat(3, 2, 1);
  neat_mutate::add_node(neat.population[0], neat.node_innov, neat.conn_innov);
  std::cout << *neat.population[0] << std::endl;
  return 0;
}
