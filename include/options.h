#ifndef NEAT_OPTIONS_H_
#define NEAT_OPTIONS_H_

// Global options that change NEAT behavior, should be set
// before NEAT object creation
namespace neat_options {

  // The minimum and maximum possible weights for a connection
  double MIN_CONNECTION_WEIGHT = -2.0;
  double MAX_CONNECTION_WEIGHT = 2.0;

}

#endif
