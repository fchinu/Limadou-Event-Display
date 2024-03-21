#ifndef CLUSTERING_INCLUDE_CLUSTER_H_
#define CLUSTERING_INCLUDE_CLUSTER_H_

#define MAX_CLUSTER_ROWS 8
#define MAX_CLUSTER_COLS 8

#include <array>
#include <bitset>
#include <cstdint>
class Cluster {

public:
  Cluster(
      unsigned chipId, unsigned eventId, unsigned clusterPositionX,
      unsigned clusterPositionY, unsigned clusterSize,
      std::array<std::bitset<MAX_CLUSTER_COLS>, MAX_CLUSTER_ROWS> arrayShape);
  inline unsigned GetMeanX() const { return fMeanX; }
  inline unsigned GetMeanY() const { return fMeanY; }
  inline unsigned GetClusterSize() const { return fClusterSize; }
  std::array<std::bitset<MAX_CLUSTER_COLS>, MAX_CLUSTER_ROWS> GetShape() const {
    return fShape;
  }

private:
  unsigned fChipId;
  unsigned fEventId;
  unsigned fClusterPositionX;
  unsigned fClusterPositionY;
  std::array<std::bitset<MAX_CLUSTER_COLS>, MAX_CLUSTER_ROWS> fShape;
  double fMeanX;
  double fMeanY;
  unsigned fClusterSize;
};

Cluster::Cluster(
    unsigned chipId, unsigned eventId, unsigned clusterPositionX,
    unsigned clusterPositionY, unsigned clusterSize,
    std::array<std::bitset<MAX_CLUSTER_COLS>, MAX_CLUSTER_ROWS> arrayShape)
    : fChipId(chipId), fEventId(eventId), fClusterPositionX(clusterPositionX),
      fClusterPositionY(clusterPositionY), fShape(arrayShape) {

  for (unsigned i = 0; i < MAX_CLUSTER_ROWS; i++) {
    for (unsigned j = 0; j < MAX_CLUSTER_ROWS; j++) {
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

#endif // CLUSTERING_INCLUDE_CLUSTER_H_
