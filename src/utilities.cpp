
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
  static std::uniform_real_distribution<double> *dist = NULL;
  static double curr_min, curr_max;
  
  // Generates a double from a uniform distribution
  double uniform(double min, double max) {
    // Reinitialize the distribution object if needed
    if(!dist || curr_min != min || curr_max != max) {
      delete dist;
      dist = new std::uniform_real_distribution<double>(min, max);
      curr_min = min;
      curr_max = max;
    }
    return (*dist)(generator);
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
