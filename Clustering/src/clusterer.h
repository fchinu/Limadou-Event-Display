#pragma once

#include "../include/Cluster.h"
#include <vector>

class Clusterer {

public:
  Clusterer();
  ~Clusterer();

  void Clustering(const char *inputFile);

protected:
  void clearClusters() { fClusters.clear(); };

private:
  std::vector<Cluster> fClusters;
};