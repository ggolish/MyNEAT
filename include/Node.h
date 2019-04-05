#ifndef NEAT_NODE_H_
#define NEAT_NODE_H_

#include <iostream>
#include <string>
#include <vector>

class Connection;

enum class NodeType { INPUT, BIAS, HIDDEN, OUTPUT };

// Represents a node in a network
class Node {
 public:
  std::vector<Connection *> in_connections, out_connections; // --in--> this --out-->
  int innovation_number;                                     // Historical marker
  NodeType type;                                             // Denotes what type of Node this is
  double value;                                              // The value that will be fed forward

  // Constructor, sets the innovation number
  Node(int innov, NodeType type);
  // Returns the type of the node as a string
  std::string get_type() const;
  // Overload for output operator
  friend std::ostream &operator<<(std::ostream &os, const Node &node);
};

#endif
