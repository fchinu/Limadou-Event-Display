#include "../../Clustering/include/Cluster.h"

Cluster::Cluster(
    unsigned chipID, unsigned eventID, unsigned clusterPositionX,
    unsigned clusterPositionY,
    std::array<std::bitset<MAX_CLUSTER_COLS>, MAX_CLUSTER_ROWS> arrayShape)
    : fChipID(chipID), fEventID(eventID), fClusterPositionX(clusterPositionX),
      fClusterPositionY(clusterPositionY), fClusterSize(0), fShape(arrayShape),
      fClusterID(fClusterCounter++) {

  for (unsigned i = 0; i < MAX_CLUSTER_ROWS; i++) {
    for (unsigned j = 0; j < MAX_CLUSTER_COLS; j++) {
      if (fShape[i][j]) {
        fMeanX += i;
        fMeanY -= j; // fClusterPositionY is top row, so we need to
                     // subtract the row number to get the correct
                     // position
        fClusterSize++;
      }
    }
  }
  fMeanX /= fClusterSize;
  fMeanY /= fClusterSize;
  fMeanX += fClusterPositionX;
  fMeanY += fClusterPositionY;
}

Cluster::Cluster(
    unsigned chipID, unsigned eventID, float meanX, float meanY,
    unsigned clusterPositionX, unsigned clusterPositionY,
    std::array<std::bitset<MAX_CLUSTER_COLS>, MAX_CLUSTER_ROWS> arrayShape)
    : fChipID(chipID), fEventID(eventID), fMeanX(meanX), fMeanY(meanY),
      fClusterPositionX(clusterPositionX), fClusterPositionY(clusterPositionY),
      fClusterSize(0), fShape(arrayShape), fClusterID(fClusterCounter++) {

  for (unsigned i = 0; i < MAX_CLUSTER_ROWS; i++)
    for (unsigned j = 0; j < MAX_CLUSTER_COLS; j++)
      if (fShape[i][j])
        fClusterSize++;
}

void Cluster::PrintCluster() const {
    std::cout << "Cluster ID: " << fClusterID << std::endl;
    std::cout << "Chip ID: " << fChipID << std::endl;
    std::cout << "Event ID: " << fEventID << std::endl;
    std::cout << "Cluster Position: (" << fClusterPositionX << ", "
                << fClusterPositionY << ")" << std::endl;
    std::cout << "Mean Position: (" << fMeanX << ", " << fMeanY << ")" << std::endl;
    std::cout << "Cluster Size: " << fClusterSize << std::endl;
    std::cout << "Cluster Shape:" << std::endl;
    for (unsigned i = 0; i < MAX_CLUSTER_ROWS; i++) {
        for (unsigned j = 0; j < MAX_CLUSTER_COLS; j++) {
        if (fShape[i][j])
            std::cout << "X";
        else
            std::cout << ".";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}