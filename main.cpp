#include <iostream>
#include <vector>

#include "NEAT.h"
#include "utilities.h"

int main()
{
  NEAT neat(3, 2, 1);
  neat_genetics::add_node(neat.population[0], neat.node_innov, neat.conn_innov);
  neat_genetics::add_connection(neat.population[0], neat.conn_innov);
  std::vector<double> inputs {0.67, 0.93};
  std::vector<double> outputs = neat.population[0]->feed_forward(inputs);
  std::cout << *neat.population[0] << std::endl;
  return 0;
}
