
#include <iostream>
#include <cstdio>
#include <vector>

#include "Genome.h"
#include "utilities.h"

Genome::Genome(int ninputs, int noutputs)
{
  // Create the nodes for the network
  int n = ninputs + noutputs;
  for(int i = 0; i < n + 1; ++i) {
    if(i < ninputs) {
      Node *new_node = new Node(i, NodeType::INPUT);
      nodes.push_back(new_node);
      input_nodes.push_back(new_node);
    } else if(i < n) {
      Node *new_node = new Node(i, NodeType::OUTPUT);
      nodes.push_back(new_node);
      output_nodes.push_back(new_node);
    } else {
      Node *new_node = new Node(i, NodeType::BIAS);
      nodes.push_back(new_node);
    }
  }

  // Create connections between the nodes, except bias
  std::vector<Node *>::iterator in, out;
  int i = 0;
  for(in = input_nodes.begin(); in != input_nodes.end(); ++in) {
    for(out = output_nodes.begin(); out != output_nodes.end(); ++out) {
      connections.push_back(new Connection((*in), (*out), i++));
    }
  }

}

std::vector<double> Genome::feed_forward(const std::vector<double> &inputs)
{
  std::vector<double> outputs;

  if(inputs.size() != input_nodes.size()) {
    std::fprintf(stderr, "Error: Invalid input size: %ld\n", inputs.size());
    return outputs;
  }
  
  // Set the values of the input nodes
  for(unsigned int i = 0; i < input_nodes.size(); ++i) {
    input_nodes[i]->value = inputs[i];
  }

  // Perform a depth first search from output nodes to calculate values
  std::vector<Node *>::const_iterator n;
  for(n = output_nodes.cbegin(); n != output_nodes.cend(); ++n) {
    double output = neat_node::calculate_output((*n));
    outputs.push_back(output);
  }

  return outputs;
}
