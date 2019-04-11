#ifndef NEAT_UTILITIES_H_
#define NEAT_UTILITIES_H_

#include "Node.h"
#include "Connection.h"
#include "Genome.h"
#include "InnovationMap.h"

// Functions involving randomness
namespace neat_random {
  double uniform(double min, double max);
  int randint(int min, int max);
}

namespace neat_node {
  double calculate_output(Node *node);
}

namespace neat_math {
  double activate(double x);
}

namespace neat_mutate {
  void add_node(Genome *g, InnovationMap *node_map, InnovationMap *conn_map);
  void add_connection(Genome *g, InnovationMap *node_map, InnovationMap *conn_map);
  void perturb_connections(Genome *g);
  void replace_connection(Genome *g);
  void toggle_connection(Genome *g);
}

#endif
