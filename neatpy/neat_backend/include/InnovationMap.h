#ifndef NEAT_INNOVATION_MAP_H_
#define NEAT_INNOVATION_MAP_H_

#include <unordered_map>
#include <boost/functional/hash.hpp>

class InnovationMap {
 private:
  std::unordered_map<std::pair<int, int>, int, boost::hash<std::pair<int, int>>> innov_map;
  int counter;
 public:
  InnovationMap(int counter);
  int get_innovation(int left, int right);
};

#endif
