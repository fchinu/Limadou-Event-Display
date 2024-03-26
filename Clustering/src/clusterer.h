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
  void getRecursiveCluster(std::vector<int> &currentCluster, int index, std::vector<int> &indices, double *chipID, double* x, double* y);
};