
#include <algorithm>
#include <iostream>
#include <unordered_map>

#include "../../Utils/include/fileManager.h"
#include "clusterer.h"

Clusterer::Clusterer() {}

Clusterer::~Clusterer() {}

void Clusterer::Clustering(const char *inputFile) {

  // add filemanager
  FileManager inputData(inputFile);

  std::unordered_map<int, std::vector<int>> event_indices;

  double *event = inputData.getColumn("event_count");
  double *chip_id = inputData.getColumn("chip_id(decimal)");
  double *x = inputData.getColumn("hit_x");
  double *y = inputData.getColumn("hit_y");

  for (int irow = 0; irow < inputData.getNRows(); irow++) {
    event_indices[event[irow]].push_back(irow);
  }

  for (auto it = event_indices.begin(); it != event_indices.end(); ++it) {
    int ievent = it->first;
    std::vector<int> &indices = it->second;

    std::cout << "Event " << ievent << std::endl;
    std::cout << "Indices size: " << indices.size() << std::endl;

    while (!indices.empty()) {

      std::vector<int> next_indices;
      double mean_ix = x[indices[0]], mean_iy = y[indices[0]];
      int cluster_size = 1;

      for (int i = 1; i < indices.size(); i++) {
        int index = indices[i];

        if (chip_id[index] != chip_id[indices[0]])
          continue;

        bool isValid = false;
        if ((std::abs(x[index] - x[indices[0]]) +
             std::abs(y[index] - y[indices[0]])) <= 1)
          isValid = true;
        for (int j : next_indices) {
          if (std::abs(x[index] - x[j]) == 1 && std::abs(y[index] - y[j]) == 1)
            isValid = true;
        }

        if (isValid) {
          next_indices.push_back(index);
          mean_ix += x[index];
          mean_iy += y[index];
          cluster_size++;
        }
      }

      mean_ix /= cluster_size;
      mean_iy /= cluster_size;

      // cluster class implementation needed
      Cluster cluster(static_cast<int>(chip_id[indices[0]]),
                      static_cast<int>(ievent), mean_ix, mean_iy, cluster_size);
      fClusters.push_back(cluster);

      // Remove processed indices from the vector
      indices.erase(std::remove_if(indices.begin(), indices.end(),
                                   [&next_indices](int i) {
                                     return std::find(next_indices.begin(),
                                                      next_indices.end(),
                                                      i) != next_indices.end();
                                   }),
                    indices.end());
      indices.erase(indices.begin());
    }
  }
}
