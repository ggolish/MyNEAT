
#include <cstdlib>
#include <cstdio>

#include "Node.h"
#include "Connection.h"

Node::Node(int innov, NodeType type) :
  innovation_number(innov), type(type)
{
  // A bias node will always have a value of 1
  if(type == NodeType::BIAS) {
    value = 1.0;
  } else {
    value = 0.0;
  }
}

// Returns the type of the node as a string
// May move this function to utilities
std::string Node::get_type() const
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

std::ostream &operator<<(std::ostream &os, const Node &node)
{
  os << "<Node type='" << node.get_type() << "' ";
  os << "innov=" << node.innovation_number << " ";
  os << "value=" << node.value << " ";
  os << "in_connections={";
  for(auto conn = node.in_connections.begin(); conn != node.in_connections.end(); ++conn) {
    os << (*conn);
    if(conn != node.in_connections.end() - 1) os << ",";
  }
  os << "} ";
  os << "out_connections={";
  for(auto conn = node.out_connections.begin(); conn != node.out_connections.end(); ++conn) {
    os << (*conn);
    if(conn != node.out_connections.end() - 1) os << ",";
  }
  os << "} ";
  os << ">";
  return os;
}
