#pragma once

#include "../../Utils/include/fileManager.h"
#include "../include/Cluster.h"
#include <vector>

class Clusterer {

public:
  Clusterer();
  ~Clusterer();

  void Clustering(const char *inputFile);

protected:
  void clearClusters() { fClusters.clear(); };
  void EventClustering(FileManager &inputData, const int event);

private:
  std::vector<Cluster> fClusters;
  void getRecursiveCluster(std::vector<int> &currentCluster, int index,
                           std::vector<int> &indices, double *chipID, double *x,
                           double *y);
};