#ifndef NEAT_OPTIONS_H_
#define NEAT_OPTIONS_H_

// Global options that change NEAT behavior, should be set
// before NEAT object creation
namespace neat_options {

  // The minimum and maximum possible weights for a connection
  extern double MIN_CONNECTION_WEIGHT;
  extern double MAX_CONNECTION_WEIGHT;

  // The maximum percentage a connection weight can be perturbed by
  extern double PERTURB_MAX;

  // The number of time to calculate the outputs for a network, to account
  // for recurrent connections
  extern int NOUTPUT_CALCS;

  // Constants for distance function
  extern double EXCESS_CONSTANT;
  extern double DISJOINT_CONSTANT;
  extern double WEIGHTDIFF_CONSTANT;
  extern double DISTANCE_THRESHOLD;

  // Determines the number of rounds to run a species tournament
  extern int TOURNAMENT_ROUNDS;

  // Repopulation rates
  extern double MUTATION_RATE;
  extern double CONNECTION_MUTATION_RATE;
  extern double PERTURB_MUTATION_RATE;
  extern double TOGGLE_MUTATION_RATE;
  extern double ADDNODE_MUTATION_RATE;
  extern double ADDCONN_MUTATION_RATE;
  extern double ANOMOLY_RATE;

  // The number of rounds a species has to improve before it is no longer
  // aloud to reproduce
  extern int UNIMPROVEMENT_LIMIT;
}

#endif
