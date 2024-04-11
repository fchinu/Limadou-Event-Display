#pragma once

#include "Clustering/include/Cluster.h"
#include "Clustering/include/Projections2D.h"
#include "Utils/include/fileManager.h"
#include <vector>

class Clusterer : public TObject {

public:
  Clusterer();
  ~Clusterer();

  void Clustering(const char *inputFile);
  ClassDef(Clusterer, 1);

protected:
  void clearClusters() { fClusters.clear(); };
  void EventClustering(FileManager &inputData, const int event);

private:
  std::vector<Cluster> fClusters;
  void getRecursiveCluster(std::vector<int> &currentCluster, int index,
                           std::vector<int> &indices, double *chipID, double *x,
                           double *y);
};