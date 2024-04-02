#pragma once

#define MAX_CLUSTER_ROWS 8
#define MAX_CLUSTER_COLS 8

#include <array>
#include <bitset>
#include <cstdint>
#include <iostream>
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

  void PrintCluster() const;

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
