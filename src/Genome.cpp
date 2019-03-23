
#include <iostream>

#include "Genome.h"

Genome::Genome(int ninputs, int noutputs)
{
  // Create the nodes for the network
  int n = ninputs + noutputs;
  for(int i = 0; i < n + 1; ++i) {
    if(i < ninputs) {
      nodes.emplace_back(i, NodeType::INPUT);
      input_nodes.push_back(&nodes.back());
    } else if(i < n) {
      nodes.emplace_back(i, NodeType::OUTPUT);
      output_nodes.push_back(&nodes.back());
    } else {
      nodes.emplace_back(i, NodeType::BIAS);
    }
  }

  // Create connections between the nodes, except bias
  std::vector<Node *>::iterator in, out;
  int i = 0;
  for(in = input_nodes.begin(); in != input_nodes.end(); ++in) {
    for(out = output_nodes.begin(); out != output_nodes.end(); ++out) {
      connections.emplace_back((*in), (*out), i++);
      std::cout << connections.back().weight << std::endl;
    }
  }
}
