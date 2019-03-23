#ifndef NEAT_CONNECTION_H_
#define NEAT_CONNECTION_H_

class Node;

// Represents a weighted connection between two nodes of a network
class Connection {
 public:
  Node *from_node, *to_node; // from_node --weight--> to_node
  int innovation_number;     // Histroical marker
  double weight;             // The weight of this connection

  // Constructor, weight is randomly generated
  Connection(Node *fnode, Node *tnode, int innov);
  // Constructor, weight is assigned
  Connection(Node *fnode, Node *tnode, int innov, double weight);
};

#endif
