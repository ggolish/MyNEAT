#ifndef NEAT_GENOME_H_
#define NEAT_GENOME_H_

#include <iostream>
#include <vector>

#include "Node.h"
#include "Connection.h"

class Genome {
 public:
  std::vector<Connection *> connections;
  std::vector<Node *> nodes;
  std::vector<Node *> input_nodes;
  std::vector<Node *> output_nodes;
  double fitness;

  // Constructor, creates fully connected network, no hidden layer
  Genome(int ninputs, int noutputs);
  // Constructor, empty genome
  Genome();
  // Destructor, ensures all nodes and connections are destroyed
  ~Genome();
  // Makes an entirely new copy and returns it
  Genome *copy();

  // Feeds a list of inputs forward through the network and returns
  // the result
  std::vector<double> feed_forward(const std::vector<double> &inputs);
  // Outputs a genome, for debugging purposes
  friend std::ostream &operator<<(std::ostream &os, const Genome &g);
  void summary();
};

#endif
