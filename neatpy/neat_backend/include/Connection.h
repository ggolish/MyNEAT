#ifndef NEAT_CONNECTION_H_
#define NEAT_CONNECTION_H_

#include <iostream>

class Node;
class Genome;

// Represents a weighted connection between two nodes of a network
class Connection {
 public:
  Node *from_node, *to_node; // from_node --weight--> to_node
  int innovation_number;     // Histroical marker
  double weight;             // The weight of this connection
  bool disabled;             // Boolean that determines whether this connection is enabled or not

  // Constructor, weight is randomly generated
  Connection(Node *fnode, Node *tnode, int innov);
  // Constructor, weight is assigned
  Connection(Node *fnode, Node *tnode, int innov, double weight);
  // Returns a copy of this in relation to a new genome
  Connection *copy(Genome *new_g);
  // Outputs a connection, for debugging purposes
  friend std::ostream &operator<<(std::ostream &os, const Connection &conn);
};

#endif
