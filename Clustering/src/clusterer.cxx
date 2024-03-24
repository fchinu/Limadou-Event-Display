
#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <unordered_map>

#include "../../Utils/include/fileManager.h"
#include "clusterer.h"

Clusterer::Clusterer() {}

Clusterer::~Clusterer() {}

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

      std::vector<int> nextIndices;
      nextIndices.push_back(indices[0]);
      double meanX = x[indices[0]], meanY = y[indices[0]];
      int clusterSize = 1;

      for (int i = 1; i < indices.size(); i++) {
        int index = indices[i];

        if (chipID[index] != chipID[indices[0]])
          continue;

        bool isValid = false;
        for (int j : nextIndices) {
          if (std::abs(x[index] - x[j]) + std::abs(y[index] - y[j]) <= 1)
            isValid = true;
        }

        if (isValid) {
          nextIndices.push_back(index);
          meanX += x[index];
          meanY += y[index];
          clusterSize++;
        }
      }

      size_t size = nextIndices.size();
      int xPos[size], yPos[size];
      for (int i = 0; i < size; i++) {
        xPos[i] = int(x[nextIndices[i]]);
        yPos[i] = int(y[nextIndices[i]]);
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
                      static_cast<unsigned>(ievent), minX, minY, shape, meanX,
                      meanY, clusterSize);

      fClusters.push_back(cluster);

      // Remove processed indices from the vector
      indices.erase(std::remove_if(indices.begin(), indices.end(),
                                   [&nextIndices](int i) {
                                     return std::find(nextIndices.begin(),
                                                      nextIndices.end(),
                                                      i) != nextIndices.end();
                                   }),
                    indices.end());
      indices.erase(indices.begin());
    }
  }
}
