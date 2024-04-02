
#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <unordered_map>

#include "../../Clustering/include/clusterer.h"
#include "../../Utils/include/fileManager.h"

/*  PUBLIC  */

Clusterer::Clusterer() {}

Clusterer::~Clusterer() {}

/**
 * @brief Cluster the hits of the input file. Different events are clustered
 * with EventClustering.
 */
void Clusterer::Clustering(const char *inputFile) {

  // add filemanager
  FileManager inputData(inputFile);

  std::unordered_map<int, std::vector<int>> eventIndices;

  int nEvents = 0;
  double *events = inputData.unique("event_count", nEvents);
  for (int i = 0; i < nEvents; i++) {
    std::cout << "Event " << i << std::endl;
    EventClustering(inputData, static_cast<int>(events[i]));
  }
}

/*  PROTECTED   */

/**
 * @brief Cluster the hits of a single event.
 * Algorithm: Checks the first hit in the event, verifying if there are hits on
 * its left, right, above or below it. If there are, they are added to the
 * cluster (in a vector) and marked in a vector of bools. Then loops on the
 * newly found hits looking for neighboring hits. If there are any, they are
 * included in a new newly-found-hits vector and loop again. Otherwise, the
 * cluster is initialised with the hits found. After a cluster is found, it
 * moves on the following hit (not in the cluster) and repeats.
 */
void Clusterer::EventClustering(FileManager &inputData, const int ievent) {

  std::unordered_map<int, std::vector<int>> eventIndices;

  double *event = inputData.getColumn("event_count");
  double *chipID = inputData.getColumn("chip_id(decimal)");
  double *x = inputData.getColumn("hit_x");
  double *y = inputData.getColumn("hit_y");

  for (int irow = 0; irow < inputData.getNRows(); irow++) {
    eventIndices[event[irow]].push_back(irow);
  }

  std::vector<int> &indices = eventIndices[ievent];

  while (!indices.empty()) {

    std::vector<bool> inCluster(indices.size(), false);
    std::vector<int> clusterIndeces;
    clusterIndeces.push_back(indices[0]);
    inCluster[0] = true;

    bool found = true;
    std::vector<int> foundIndices;
    std::vector<int> newFoundIndices;
    foundIndices.push_back(indices[0]);

    double meanX = x[indices[0]], meanY = y[indices[0]];
    int clusterSize = 1;

    while (found) {

      found = false;

      for (int i = 0; i < foundIndices.size(); i++) {
        for (int j = 0; j < indices.size(); j++) {

          if (inCluster[j])
            continue;

          if (chipID[indices[j]] != chipID[foundIndices[i]])
            continue;

          if (std::abs(x[indices[j]] - x[foundIndices[i]]) +
                  std::abs(y[indices[j]] - y[foundIndices[i]]) <=
              1) {
            clusterIndeces.push_back(indices[j]);
            meanX += x[indices[j]];
            meanY += y[indices[j]];
            clusterSize++;
            inCluster[j] = true;
            found = true;
            newFoundIndices.push_back(indices[j]);
          }
        }
      }
      foundIndices.clear();
      foundIndices = newFoundIndices;
      newFoundIndices.clear();
    }

    foundIndices.clear();
    newFoundIndices.clear();

    size_t size = clusterIndeces.size();
    int xPos[size], yPos[size];
    for (int i = 0; i < size; i++) {
      xPos[i] = int(x[clusterIndeces[i]]);
      yPos[i] = int(y[clusterIndeces[i]]);
    }

    int minX = *std::min_element(xPos, xPos + size);
    int maxY = *std::max_element(yPos, yPos + size);

    meanX /= clusterSize;
    meanY /= clusterSize;

    // cluster shape
    std::array<std::bitset<MAX_CLUSTER_COLS>, MAX_CLUSTER_ROWS> shape = {0};
    for (int i = 0; i < size; i++)
      shape[(maxY - yPos[i])].set(MAX_CLUSTER_COLS - 1 - (xPos[i] - minX));

    // cluster class implementation needed
    Cluster cluster(static_cast<unsigned>(chipID[indices[0]]),
                    static_cast<unsigned>(ievent), meanX, meanY, minX, maxY,
                    shape);

    fClusters.push_back(cluster);

    // visualize cluster on terminal
    cluster.PrintCluster();

    indices.erase(std::remove_if(indices.begin(), indices.end(),
                                 [&clusterIndeces](int i) {
                                   return std::find(clusterIndeces.begin(),
                                                    clusterIndeces.end(),
                                                    i) != clusterIndeces.end();
                                 }),
                  indices.end());
  }
}

/*  PRIVATE  */

void Clusterer::getRecursiveCluster(std::vector<int> &currentCluster, int index,
                                    std::vector<int> &indices, double *chipID,
                                    double *x, double *y) {
  // recursive function to find all connected clusters

  // find all connected indices
  for (auto i : indices) {
    if (std::find(currentCluster.begin(), currentCluster.end(), i) !=
        currentCluster.end())
      continue; // already in the cluster
    else {
      int count = 0;
      for (auto j : currentCluster) {
        if (chipID[i] == chipID[j] &&
            std::abs(x[i] - x[j]) + std::abs(y[i] - y[j]) <= 1) {
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