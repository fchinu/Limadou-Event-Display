#pragma once

#define MAX_CLUSTER_ROWS 8
#define MAX_CLUSTER_COLS 8

#include <array>
#include <bitset>
#include <cstdint>
class Cluster {

public:
  Cluster(
      unsigned chipId, unsigned eventId, float meanX, float meanY,
      unsigned clusterPositionX, unsigned clusterPositionY,
      std::array<std::bitset<MAX_CLUSTER_COLS>, MAX_CLUSTER_ROWS> arrayShape);
  Cluster(
      unsigned chipId, unsigned eventId, unsigned clusterPositionX,
      unsigned clusterPositionY,
      std::array<std::bitset<MAX_CLUSTER_COLS>, MAX_CLUSTER_ROWS> arrayShape);

  inline unsigned GetChipId() const { return fChipId; }
  inline unsigned GetEventId() const { return fEventId; }
  inline unsigned GetClusterPositionX() const { return fClusterPositionX; }
  inline unsigned GetClusterPositionY() const { return fClusterPositionY; }
  std::array<std::bitset<MAX_CLUSTER_COLS>, MAX_CLUSTER_ROWS> GetShape() const {
    return fShape;
  }
  inline float GetMeanX() const { return fMeanX; }
  inline float GetMeanY() const { return fMeanY; }
  inline unsigned GetClusterSize() const { return fClusterSize; }
  inline unsigned GetClusterId() const { return fClusterId; }

private:
  unsigned fChipId;
  unsigned fEventId;
  unsigned fClusterPositionX;
  unsigned fClusterPositionY;
  std::array<std::bitset<MAX_CLUSTER_COLS>, MAX_CLUSTER_ROWS> fShape;
  double fMeanX;
  double fMeanY;
  unsigned fClusterSize;
  unsigned fClusterId;

  inline static unsigned fClusterCounter = 0;
};

Cluster::Cluster(
    unsigned chipId, unsigned eventId, unsigned clusterPositionX,
    unsigned clusterPositionY,
    std::array<std::bitset<MAX_CLUSTER_COLS>, MAX_CLUSTER_ROWS> arrayShape)
    : fChipId(chipId), fEventId(eventId), fClusterPositionX(clusterPositionX),
      fClusterPositionY(clusterPositionY), fClusterSize(0), fShape(arrayShape),
      fClusterId(fClusterCounter++) {

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
    unsigned chipId, unsigned eventId, float meanX, float meanY,
    unsigned clusterPositionX, unsigned clusterPositionY,
    std::array<std::bitset<MAX_CLUSTER_COLS>, MAX_CLUSTER_ROWS> arrayShape)
    : fChipId(chipId), fEventId(eventId), fMeanX(meanX), fMeanY(meanY),
      fClusterPositionX(clusterPositionX), fClusterPositionY(clusterPositionY),
      fClusterSize(0), fShape(arrayShape), fClusterId(fClusterCounter++) {

  for (unsigned i = 0; i < MAX_CLUSTER_ROWS; i++)
    for (unsigned j = 0; j < MAX_CLUSTER_COLS; j++)
      if (fShape[i][j])
        fClusterSize++;
}
