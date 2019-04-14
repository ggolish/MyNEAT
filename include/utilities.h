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
  bool compare(Node *n1, Node *n2);
}

namespace neat_connection {
  bool compare(Connection *c1, Connection *c2);
}

namespace neat_genome {
  bool compare(Genome *g1, Genome *g2);
}

namespace neat_math {
  double activate(double x);
}

namespace neat_genetics {
  void add_node(Genome *g, InnovationMap *node_map, InnovationMap *conn_map);
  void add_connection(Genome *g, InnovationMap *conn_map);
  void perturb_connection(Genome *g);
  void replace_connection(Genome *g);
  void toggle_connection(Genome *g);
  Genome *crossover(Genome *g1, Genome *g2);
}

#endif
