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
}

#endif
