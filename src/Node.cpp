
#include <cstdlib>

#include "Node.h"
#include "Connection.h"

Node::Node(int innov, NodeType type) :
  in_connection(NULL), out_connection(NULL), innovation_number(innov), type(type)
{
}

// Returns the type of the node as a string
// May move this function to utilities
std::string Node::get_type()
{
  switch(type) {
    case NodeType::INPUT:
      return std::string("INPUT");
    case NodeType::OUTPUT:
      return std::string("OUTPUT");
    case NodeType::HIDDEN:
      return std::string("HIDDEN");
    case NodeType::BIAS:
      return std::string("BIAS");
  }

  return std::string("INVALID");
}
