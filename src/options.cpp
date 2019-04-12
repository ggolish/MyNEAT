
#include "options.h"

namespace neat_options {

  // The minimum and maximum possible weights for a connection
  double MIN_CONNECTION_WEIGHT = -2.0;
  double MAX_CONNECTION_WEIGHT = 2.0;

  // The maximum percentage a connection weight can be perturbed by
  double PERTURB_MAX = 0.5;

  int NOUTPUT_CALCS = 5;
}
