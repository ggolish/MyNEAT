#ifndef NEAT_UTILITIES_H_
#define NEAT_UTILITIES_H_

#include "Node.h"
#include "Connection.h"

// Functions involving randomness
namespace neat_random {
  double uniform(double min, double max);
}

namespace neat_node {
  double calculate_output(Node *node);
}

namespace neat_math {
  double activate(double x);
}

#endif
