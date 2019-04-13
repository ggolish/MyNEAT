
#include "options.h"

namespace neat_options {

  // The minimum and maximum possible weights for a connection
  double MIN_CONNECTION_WEIGHT = -2.0;
  double MAX_CONNECTION_WEIGHT = 2.0;

  // The maximum percentage a connection weight can be perturbed by
  double PERTURB_MAX = 0.5;

  // The number of time to calculate the outputs for a network, to account
  // for recurrent connections
  int NOUTPUT_CALCS = 5;

  // Constants for distance function
  double EXCESS_CONSTANT = 1.0;
  double DISJOINT_CONSTANT = 1.0;
  double WEIGHTDIFF_CONSTANT = 0.4;
  double DISTANCE_THRESHOLD = 3.0;
}
