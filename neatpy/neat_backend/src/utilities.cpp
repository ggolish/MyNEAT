
#include <algorithm>
#include <random>
#include <ctime>
#include <cmath>

#include "utilities.h"
#include "options.h"

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

    node->visited = true;

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
      if((*conn)->disabled == false) {
        if((*conn)->from_node->visited == false) 
          sum += calculate_output((*conn)->from_node) * (*conn)->weight;
        else
          sum += (*conn)->from_node->value * (*conn)->weight;
      }
    }

    // Activate the value and return
    node->value = neat_math::activate(sum);
    return node->value;
  }

  bool compare(Node *n1, Node *n2) 
  {
    return (n1->innovation_number < n2->innovation_number);
  }

}

namespace neat_connection {

  bool compare(Connection *c1, Connection *c2)
  {
    return (c1->innovation_number < c2->innovation_number);
  }

}

namespace neat_genome {

  bool compare(Genome *g1, Genome *g2)
  {
    return (g1->fitness < g2->fitness);
  }

}

namespace neat_math {

  // Returns the result of passing x to the sigmoid function
  double activate(double x) {
    return 1 / (1 + exp(-4.9 * x));
  }

}

namespace neat_genetics {
  
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
  void add_connection(Genome *g, InnovationMap *conn_map)
  {
    int i = neat_random::randint(0, g->nodes.size() - 1);
    int j = neat_random::randint(0, g->nodes.size() - 1);

    Node *from_node = g->nodes[i];
    Node *to_node = g->nodes[j];

    // Check if the connection is valid
    if(from_node->type == NodeType::OUTPUT || to_node->type == NodeType::INPUT || to_node->type == NodeType::BIAS)
      return;

    // Check if connection exists
    for(auto c = from_node->out_connections.begin(); c != from_node->out_connections.end(); ++c) {
      if((*c)->to_node == to_node) return;
    }

    // Create new connection and append
    int innov = conn_map->get_innovation(from_node->innovation_number, to_node->innovation_number);
    Connection *new_conn = new Connection(from_node, to_node, innov);
    g->connections.push_back(new_conn);
  }

  // Mutates a genome by perturbing its connection weights
  void perturb_connection(Genome *g)
  {
    for(unsigned int i = 0; i != g->connections.size(); ++i) {
      Connection *c = g->connections[i];
      double delta = neat_random::uniform(-neat_options::PERTURB_MAX, neat_options::PERTURB_MAX);
      c->weight += delta;
      c->weight = std::min(std::max(neat_options::MIN_CONNECTION_WEIGHT, c->weight), neat_options::MAX_CONNECTION_WEIGHT);
    }
  }

  // Mutates a genome by replacing a connection weight with a random value
  void replace_connection(Genome *g)
  {
    int i = neat_random::randint(0, g->connections.size() - 1);
    Connection *c = g->connections[i];
    c->weight = neat_random::uniform(neat_options::MIN_CONNECTION_WEIGHT, neat_options::MAX_CONNECTION_WEIGHT);
  }

  // Mutates a genome by turning a connection on or off
  void toggle_connection(Genome *g)
  {
    int i = neat_random::randint(0, g->connections.size() - 1);
    Connection *c = g->connections[i];
    c->disabled = !c->disabled;
  }

  // Sexual reproduction of two genomes
  Genome *crossover(Genome *g1, Genome *g2)
  {
    Genome *best_fit, *least_fit;
    Genome *baby = new Genome();

    // Determine the best fit parent
    if(g1->fitness > g2->fitness) {
      best_fit = g1;
      least_fit = g2;
    } else {
      best_fit = g2;
      least_fit = g1;
    }

    // Ensure nodes and connections are sorted by innovation number
    std::sort(g1->connections.begin(), g1->connections.end(), neat_connection::compare);
    std::sort(g2->connections.begin(), g2->connections.end(), neat_connection::compare);
    std::sort(g1->nodes.begin(), g1->nodes.end(), neat_node::compare);
    std::sort(g2->nodes.begin(), g2->nodes.end(), neat_node::compare);

    // The child inherits all nodes from the best fit parent
    for(auto n = best_fit->nodes.begin(); n != best_fit->nodes.end(); ++n) {
      Node *new_node = (*n)->copy();
      if((*n)->type == NodeType::INPUT) baby->input_nodes.push_back(new_node);
      else if((*n)->type == NodeType::OUTPUT) baby->output_nodes.push_back(new_node);
      baby->nodes.push_back(new_node);
    }

    // Loop through all connections in both parents, disjoint and excess are inherited from
    // more fit parent, all others chosen randomly
    auto c1 = best_fit->connections.begin();
    auto c2 = least_fit->connections.begin();
    while(c1 != best_fit->connections.end() && c2 != least_fit->connections.end()) {
      int innov1 = (*c1)->innovation_number;
      int innov2 = (*c2)->innovation_number;
      if(innov1 == innov2) {
        // Randomly choose which gene to inherit from
        double prob = neat_random::uniform(0, 1);
        Connection *new_conn = (prob < 0.5) ? (*c1)->copy(baby) : (*c2)->copy(baby);
        baby->connections.push_back(new_conn);
        c1++;
        c2++;
      } else if(innov1 < innov2) {
        // Add disjoint genes from best fit parent
        baby->connections.push_back((*c1)->copy(baby));
        c1++; 
      } else {
        // Disjoint genes from least_fit parent are ignored
        c2++;
      }
    }

    // Ensure all excess genes from best fit parent are added
    while(c1 != best_fit->connections.end()) {
      baby->connections.push_back((*c1)->copy(baby));
      c1++; 
    }

    return baby;
  }

}

