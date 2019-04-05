
#include "Connection.h"
#include "Node.h"
#include "utilities.h"
#include "options.h"

// Creates a new connection from fnode to tnode, with a random
// weight 
Connection::Connection(Node *fnode, Node *tnode, int innov) :
  from_node(fnode), to_node(tnode), innovation_number(innov)
{
  // Ensure each nodes' connection pointers are correct
  from_node->out_connections.push_back(this);
  to_node->in_connections.push_back(this);
  // Generate a random weight for this connection from a uniform distribution
  weight = neat_random::uniform(neat_options::MIN_CONNECTION_WEIGHT,
                                neat_options::MAX_CONNECTION_WEIGHT);
}

// Creates a new connection from fnode to tnode with a weight
// equal to weight
Connection::Connection(Node *fnode, Node *tnode, int innov, double weight) :
  from_node(fnode), to_node(tnode), innovation_number(innov), weight(weight)
{
  // Ensure each nodes' connection pointers are correct
  from_node->out_connections.push_back(this);
  to_node->in_connections.push_back(this);
}
