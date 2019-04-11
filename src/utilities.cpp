
#include <random>
#include <ctime>
#include <cmath>

#include "utilities.h"

// This namespace contains all utility functions involving random numbers
namespace neat_random {

  // Variables for generating numbers from a uniform distribution
  static std::random_device rd1;
  static std::random_device rd2;
  // Use nondeterministic random numbers as seed if possible
  static unsigned int seed = (rd1() == rd2()) ? time(NULL) : rd1();
  static std::mt19937 generator(seed);
  static std::uniform_real_distribution<double> *real_dist = NULL;
  static std::uniform_int_distribution<int> *int_dist = NULL;
  static double curr_real_min, curr_real_max;
  static int curr_int_min, curr_int_max;
  
  // Generates a double from a uniform distribution
  double uniform(double min, double max) {
    // Reinitialize the distribution object if needed
    if(!real_dist || curr_real_min != min || curr_real_max != max) {
      delete real_dist;
      real_dist = new std::uniform_real_distribution<double>(min, max);
      curr_real_min = min;
      curr_real_max = max;
    }
    return (*real_dist)(generator);
  }

  // Generates an int from a uniform distribution
  int randint(int min, int max) {
    // Reinitialize the distribution object if needed
    if(!int_dist || curr_int_min != min || curr_int_max != max) {
      delete int_dist;
      int_dist = new std::uniform_int_distribution<int>(min, max);
      curr_int_min = min;
      curr_int_max = max;
    }
    return (*int_dist)(generator);
  }

}

// This namespace contains functions that operate on Node types
namespace neat_node {

  // Recursively calculates the value of a node via depth first search
  double calculate_output(Node *node)
  {

    // Base case, all nodes should lead to an input or bias node
    // The network cannot contain any loops
    if(node->type == NodeType::INPUT || node->type == NodeType::BIAS) {
      return node->value;
    }

    // Loop through the node's in connections and recurse
    // Multiply their values by the connection weights and sum
    double sum = 0.0;
    std::vector<Connection *>::iterator conn;
    for(conn = node->in_connections.begin(); conn != node->in_connections.end(); ++conn) {
      double v = calculate_output((*conn)->from_node);
      sum += v * (*conn)->weight;
    }

    // Activate the value and return
    return neat_math::activate(sum);
  }

}

namespace neat_math {

  // Returns the result of passing x to the sigmoid function
  double activate(double x) {
    return 1 / (1 + exp(-x));
  }

}

namespace neat_mutate {
  
  // Mutates a genome by adding a new node
  void add_node(Genome *g, InnovationMap *node_map, InnovationMap *conn_map)
  {
    // Select a random connection to split, if it is disabled the mutation simply fails
    int i = neat_random::randint(0, g->connections.size() - 1);
    Connection *old_conn = g->connections[i];
    if(old_conn->disabled == true) return;

    // Calculate the new innovation numbers
    int node_innov = node_map->get_innovation(old_conn->from_node->innovation_number, old_conn->to_node->innovation_number);
    int conn_innov1 = conn_map->get_innovation(old_conn->from_node->innovation_number, node_innov);
    int conn_innov2 = conn_map->get_innovation(node_innov, old_conn->to_node->innovation_number);

    // Create the new node and connections, store them in the genome
    Node *new_node = new Node(node_innov, NodeType::HIDDEN);
    Connection *new_conn1 = new Connection(old_conn->from_node, new_node, conn_innov1, old_conn->weight);
    Connection *new_conn2 = new Connection(new_node, old_conn->to_node, conn_innov2);
    g->nodes.push_back(new_node);
    g->connections.push_back(new_conn1);
    g->connections.push_back(new_conn2);

    // Disable the old connection
    old_conn->disabled = true;
  }

  // Mutates a genome by adding a new connection
  void add_connection(Genome *g, InnovationMap *node_map, InnovationMap *conn_map)
  {
  }

  // Mutates a genome by perturbing its connection weights
  void perturb_connections(Genome *g)
  {
  }

  // Mutates a genome by replacing a connection weight with a random value
  void replace_connection(Genome *g)
  {
  }

  // Mutates a genome by turning a connection on or off
  void toggle_connection(Genome *g)
  {
  }
  
}
