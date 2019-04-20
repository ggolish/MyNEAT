
#include <cstdio>

#include "Genome.h"
#include "utilities.h"
#include "options.h"

Genome::Genome(int ninputs, int noutputs) :
  fitness(0.0)
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
  for(out = output_nodes.begin(); out != output_nodes.end(); ++out) {
    connections.push_back(new Connection(nodes.back(), (*out), i++));
  }

}

Genome::Genome() : fitness(0.0)
{
}

Genome::~Genome()
{
  for(auto n = nodes.begin(); n != nodes.end(); ++n) {
    delete (*n);
  }
  for(auto n = connections.begin(); n != connections.end(); ++n) {
    delete (*n);
  }
}

Genome *Genome::copy()
{
  Genome *new_g = new Genome();
  for(auto n = nodes.begin(); n != nodes.end(); ++n) {
    Node *new_node = (*n)->copy();
    if((*n)->type == NodeType::INPUT) new_g->input_nodes.push_back(new_node);
    else if((*n)->type == NodeType::OUTPUT) new_g->output_nodes.push_back(new_node);
    new_g->nodes.push_back(new_node);
  }
  for(auto c = connections.begin(); c != connections.end(); ++c) {
    new_g->connections.push_back((*c)->copy(new_g));
  }
  return new_g;
}

std::vector<double> Genome::feed_forward(const std::vector<double> &inputs)
{
  std::vector<double> outputs;

  if(inputs.size() != input_nodes.size()) {
    std::fprintf(stderr, "Error: Invalid input size: %ld\n", inputs.size());
    return outputs;
  }
  
  // Set the values of the input nodes
  int input_count = 0;
  for(auto n = nodes.begin(); n != nodes.end(); ++n) {
    if((*n)->type == NodeType::INPUT) {
      (*n)->value = inputs[input_count++];
    } else if((*n)->type != NodeType::BIAS) {
      (*n)->value = 0.0;
    }
  }

  // Perform a depth first search from output nodes to calculate values
  for(int i = 0; i < neat_options::NOUTPUT_CALCS; ++i) {
    outputs.clear();
    for(auto n = nodes.begin(); n != nodes.end(); ++n) 
      (*n)->visited = false;
    std::vector<Node *>::const_iterator n;
    for(n = output_nodes.cbegin(); n != output_nodes.cend(); ++n) {
      double output = neat_node::calculate_output((*n));
      outputs.push_back(output);
    }
  }

  return outputs;
}

std::ostream &operator<<(std::ostream &os, const Genome &g)
{
    os << "<Genome " << &g << " nodes={" << std::endl;
    for(auto n = g.nodes.begin(); n != g.nodes.end(); ++n) {
        os << "  " << *(*n) << std::endl;
    }

    os << "} connections={" << std::endl;
    for(auto conn = g.connections.begin(); conn != g.connections.end(); ++conn) {
        os << "  " << *(*conn) << std::endl;
    }

    os << "}>";

    return os;
}

void Genome::summary()
{
  std::cout << *this << std::endl;
}
