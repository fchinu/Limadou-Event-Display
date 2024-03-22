#ifndef CLUSTERING_INCLUDE_CLUSTER_H_
#define CLUSTERING_INCLUDE_CLUSTER_H_

#include <cstdint>
class Cluster {
  int fX;
  int fY;
  int fClusterSize;
  uint8_t fArrayShape[8];

  int GetX() const;
  int GetY() const;
  int GetClusterSize() const;
  uint8_t *GetArrayShape();
};

#endif // CLUSTERING_INCLUDE_CLUSTER_H_
