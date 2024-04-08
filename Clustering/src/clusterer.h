#pragma once

#include <TObject.h>
#include <vector>

#include "../../Utils/include/fileManager.h"
#include "../include/Cluster.h"

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