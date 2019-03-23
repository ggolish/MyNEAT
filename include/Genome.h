#ifndef NEAT_GENOME_H_
#define NEAT_GENOME_H_

#include <vector>

#include "Node.h"
#include "Connection.h"

class Genome {
 public:
  std::vector<Connection> connections;
  std::vector<Node> nodes;
  std::vector<Node *> input_nodes;
  std::vector<Node *> output_nodes;

  // Constructor, creates fully connected network, no hidden layer
  Genome(int ninputs, int noutputs);
};

#endif
