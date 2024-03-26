
#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <unordered_map>

#include "../../Utils/include/fileManager.h"
#include "clusterer.h"

Clusterer::Clusterer() {}

Clusterer::~Clusterer() {}

void Clusterer::getRecursiveCluster(std::vector<int> &currentCluster, int index, std::vector<int> &indices, double *chipID, double* x, double* y) {
  // recursive function to find all connected clusters

  // find all connected indices
  for (auto i : indices) {
    if (std::find(currentCluster.begin(), currentCluster.end(), i) !=
        currentCluster.end()) 
      continue; // already in the cluster
    else {
      int count = 0;
      for (auto j : currentCluster) {
        if (chipID[i]==chipID[j] && std::abs(x[i] - x[j]) + std::abs(y[i] - y[j]) <= 1) {
          count++;
          currentCluster.push_back(i);
          getRecursiveCluster(currentCluster, i, indices, chipID, x, y);
        }
      }

      if (count == 0) // no connected indices
        return;
    }
  }
}

void Clusterer::Clustering(const char *inputFile) {

  // add filemanager
  FileManager inputData(inputFile);

  std::unordered_map<int, std::vector<int>> eventIndices;

  double *event = inputData.getColumn("event_count");
  double *chipID = inputData.getColumn("chip_id(decimal)");
  double *x = inputData.getColumn("hit_x");
  double *y = inputData.getColumn("hit_y");

  for (int irow = 0; irow < inputData.getNRows(); irow++) {
    eventIndices[event[irow]].push_back(irow);
  }

  for (auto it = eventIndices.begin(); it != eventIndices.end(); ++it) {
    int ievent = it->first;
    std::vector<int> &indices = it->second;

    std::cout << "Event " << ievent << std::endl;
    std::cout << "Indices size: " << indices.size() << std::endl;

    while (!indices.empty()) {

      for (auto i : indices) {
        std::cout << i << "\t";
      }
      std::cout << std::endl;

      std::vector<int> currentCluster {indices[0]};
      getRecursiveCluster(currentCluster, indices[0], indices, chipID, x, y);

      double meanX = x[indices[0]], meanY = y[indices[0]];
      int clusterSize = 1;

      for (auto i : currentCluster) {
        std::cout << i << std::endl;
        meanX += x[i];
        meanY += y[i];
        clusterSize++;
      }

      size_t size = currentCluster.size();
      int xPos[size], yPos[size];
      for (int i = 0; i < size; i++) {
        xPos[i] = int(x[currentCluster[i]]);
        yPos[i] = int(y[currentCluster[i]]);
      }

      int minX = *std::min_element(xPos, xPos + size);
      int minY = *std::min_element(yPos, yPos + size);

      meanX /= clusterSize;
      meanY /= clusterSize;

      // cluster shape
      std::array<std::bitset<MAX_CLUSTER_COLS>, MAX_CLUSTER_ROWS> shape = {0};
      for (int i = 0; i < size; i++)
        shape[yPos[i] - minY].set(xPos[i] - minX);

      // cluster class implementation needed
      Cluster cluster(static_cast<unsigned>(chipID[indices[0]]),
                      static_cast<unsigned>(ievent), meanX, meanY, minX, minY,
                      shape);

      std::cout << "Cluster size " << cluster.GetClusterSize() << std::endl;

      fClusters.push_back(cluster);

      // Remove processed indices from the vector
      indices.erase(std::remove_if(indices.begin(), indices.end(), [&currentCluster](int i) {
        return std::find(currentCluster.begin(), currentCluster.end(), i) !=
               currentCluster.end(); }), indices.end());

      currentCluster.clear();
    }
  }
}
