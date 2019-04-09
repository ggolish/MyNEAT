#include "InnovationMap.h"

InnovationMap::InnovationMap(int counter) :
  counter(counter)
{
}

int InnovationMap::get_innovation(int left, int right)
{
  std::pair<int, int> p(left, right);
  auto it = innov_map.find(p);
  if(it == innov_map.end()) {
    innov_map[p] = counter;
    return counter++;
  } else {
    return it->second;
  }
}
