
#include <random>
#include <ctime>

#include "utilities.h"

// This namespace contains all utility functions involving random numbers
namespace neat_random {
  // Variables for generating numbers from a uniform distribution
  static std::mt19937 generator(time(NULL));
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
