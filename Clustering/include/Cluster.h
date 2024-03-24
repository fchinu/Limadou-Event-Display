#pragma once

#define MAX_CLUSTER_ROWS 8
#define MAX_CLUSTER_COLS 8

#include <array>
#include <bitset>
#include <cstdint>
class Cluster {

public:
  Cluster(
      unsigned chipID, unsigned eventID, float meanX, float meanY,
      unsigned clusterPositionX, unsigned clusterPositionY,
      std::array<std::bitset<MAX_CLUSTER_COLS>, MAX_CLUSTER_ROWS> arrayShape);
  Cluster(
      unsigned chipID, unsigned eventID, unsigned clusterPositionX,
      unsigned clusterPositionY,
      std::array<std::bitset<MAX_CLUSTER_COLS>, MAX_CLUSTER_ROWS> arrayShape);

  inline unsigned GetChipID() const { return fChipID; }
  inline unsigned GetEventID() const { return fEventID; }
  inline unsigned GetClusterPositionX() const { return fClusterPositionX; }
  inline unsigned GetClusterPositionY() const { return fClusterPositionY; }
  std::array<std::bitset<MAX_CLUSTER_COLS>, MAX_CLUSTER_ROWS> GetShape() const {
    return fShape;
  }
  inline float GetMeanX() const { return fMeanX; }
  inline float GetMeanY() const { return fMeanY; }
  inline unsigned GetClusterSize() const { return fClusterSize; }
  inline unsigned GetClusterID() const { return fClusterID; }

private:
  unsigned fChipID;
  unsigned fEventID;
  unsigned fClusterPositionX;
  unsigned fClusterPositionY;
  std::array<std::bitset<MAX_CLUSTER_COLS>, MAX_CLUSTER_ROWS> fShape;
  double fMeanX;
  double fMeanY;
  unsigned fClusterSize;
  unsigned fClusterID;

  inline static unsigned fClusterCounter = 0;
};

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
