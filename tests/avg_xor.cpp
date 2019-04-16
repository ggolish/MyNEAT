#include <cmath>
#include <iostream>
#include <vector>

#include "NEAT.h"
#include "utilities.h"

#define EPOCHS 100
#define POPULATION_SIZE 150
#define NINPUTS 2
#define NOUTPUTS 1
#define THRESHOLD 0.98

bool accepted(double outputs[]);

std::vector<std::vector<double>> inputs_list {
  {0.0, 0.0},
  {0.0, 1.0},
  {1.0, 0.0},
  {1.0, 1.0}
};

std::vector<double> outputs_list {0.0, 1.0, 1.0, 0.0};

int main()
{
  double gen_sum = 0;
  for(int epoch = 0; epoch < EPOCHS; ++epoch) {
    NEAT neat(POPULATION_SIZE, NINPUTS, NOUTPUTS);
    double best_fitness;
    int best_index;
    int generations = 1;
    for(;generations++;) {
      std::vector<double> fitnesses;
      best_fitness = 0.0;
      best_index = -1;
      for(int i = 0; i < POPULATION_SIZE; ++i) {
        double fitness = 0.0;
        int j = 0;
        for(auto inputs = inputs_list.begin(); inputs != inputs_list.end(); ++inputs) {
          auto outputs = neat.feed_forward(i, (*inputs));
          fitness += fabs(outputs_list[j++] - outputs[0]);
        }
        fitness = 4.0 - fitness;
        fitness *= fitness;
        if(fitness > best_fitness) {
          best_fitness = fitness;
          best_index = i;
        }
        fitnesses.push_back(fitness);
      }
      double check_outputs[4];
      int j = 0;
      for(auto inputs = inputs_list.begin(); inputs != inputs_list.end(); ++inputs) {
        auto outputs = neat.feed_forward(best_index, (*inputs));
        check_outputs[j++] = outputs[0];
      }
      if(accepted(check_outputs) == true) break;
      neat.repopulate(fitnesses);
    }
    gen_sum += generations;
    std::cout << gen_sum / (epoch + 1) << std::endl;
  }
  std::cout << "Average generations: " << gen_sum / EPOCHS << std::endl;
}

bool accepted(double outputs[])
{
  if(outputs[0] < 0.5 && outputs[1] > 0.5 && outputs[2] > 0.5 && outputs[3] < 0.5) {
    return true;
  } 
  return false;
}

