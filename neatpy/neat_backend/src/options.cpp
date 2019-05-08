
#include "options.h"

#include <cmath>

namespace neat_options {

  // The minimum and maximum possible weights for a connection
  double MIN_CONNECTION_WEIGHT = -4.0;
  double MAX_CONNECTION_WEIGHT = 4.0;

  // The maximum percentage a connection weight can be perturbed by
  double PERTURB_MAX = (std::abs(MIN_CONNECTION_WEIGHT) + std::abs(MAX_CONNECTION_WEIGHT)) / 2.0;

  // The number of time to calculate the outputs for a network, to account
  // for recurrent connections
  int NOUTPUT_CALCS = 5;

  // Constants for distance function
  double EXCESS_CONSTANT = 1.0;
  double DISJOINT_CONSTANT = 1.0;
  double WEIGHTDIFF_CONSTANT = 1.0;
  double DISTANCE_THRESHOLD = 3.0;

  // Determines the number of rounds to run a species tournament
  int TOURNAMENT_ROUNDS = 5;

  // Repopulation rates
  double MUTATION_RATE = 0.25;
  double CONNECTION_MUTATION_RATE = 0.8;
  double PERTURB_MUTATION_RATE = 0.9;
  double TOGGLE_MUTATION_RATE = 0.01;
  double ADDNODE_MUTATION_RATE = 0.03;
  double ADDCONN_MUTATION_RATE = 0.05;
  double ANOMOLY_RATE = 0.01;

  // The number of rounds a species has to improve before it is no longer
  // aloud to reproduce
  int UNIMPROVEMENT_LIMIT = 15;
}
