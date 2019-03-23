#ifndef NEAT_NODE_H_
#define NEAT_NODE_H_

#include <string>

class Connection;

enum class NodeType { INPUT, BIAS, HIDDEN, OUTPUT };

// Represents a node in a network
class Node {
 public:
  Connection *in_connection, *out_connection; // --in--> this --out-->
  int innovation_number;                      // Historical marker
  NodeType type;                              // Denotes what type of Node this is

  // Constructor, sets the innovation number
  Node(int innov, NodeType type);
  std::string get_type();
};

#endif
