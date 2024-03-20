#ifndef CLUSTERING_INCLUDE_CLUSTER_H_
#define CLUSTERING_INCLUDE_CLUSTER_H_

#define MAX_CLUSTER_SIZE 8

#include <array>
#include <cstdint>
class Cluster {

public:
  Cluster(unsigned chipId, unsigned eventId, unsigned meanX, unsigned meanY,
          unsigned clusterSize,
          std::array<uint8_t, MAX_CLUSTER_SIZE> arrayShape);
  inline unsigned GetMeanX() const { return fMeanX; }
  inline unsigned GetMeanY() const { return fMeanY; }
  inline unsigned GetClusterSize() const { return fClusterSize; }
  std::array<uint8_t, MAX_CLUSTER_SIZE> GetShape() const { return fShape; }

private:
  unsigned fChipId;
  unsigned fEventId;
  unsigned fMeanX;
  unsigned fMeanY;
  unsigned fClusterSize;
  std::array<uint8_t, MAX_CLUSTER_SIZE> fShape;
};

Cluster::Cluster(unsigned chipId, unsigned eventId, unsigned meanX,
                 unsigned meanY, unsigned clusterSize,
                 std::array<uint8_t, MAX_CLUSTER_SIZE> arrayShape)
    : fChipId(chipId), fEventId(eventId), fMeanX(meanX), fMeanY(meanY),
      fClusterSize(clusterSize), fShape(arrayShape) {}

#endif // CLUSTERING_INCLUDE_CLUSTER_H_
