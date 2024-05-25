#pragma once

#include <array>
#include <bitset>

#include <Riostream.h>
#include <TObject.h>

#define MAX_CLUSTER_ROWS 8
#define MAX_CLUSTER_COLS 8

class Cluster : public TObject {
public:
  Cluster()
      : fChipID(0), fEventID(0), fClusterPositionX(0), fClusterPositionY(0),
        fMeanX(0.0), fMeanY(0.0), fClusterSize(0), fShape(0), fClusterID(0) {}
  /**
   * @brief Construct a new Cluster object
   *
   * @param chipID
   * @param eventID
   * @param meanX
   * @param meanY
   * @param clusterPositionX
   * @param clusterPositionY
   * @param clusterSize
   * @param shape The cluster shape is encoded in a 64 bit variable. The maximum
   * cluster accepted is 8x8 large. Each 8 bit is a row.
   */
  Cluster(unsigned chipID, unsigned eventID, float meanX, float meanY,
          unsigned clusterPositionX, unsigned clusterPositionY,
          unsigned clusterSize, uint64_t shape);
  Cluster(unsigned chipID, unsigned eventID, float meanX, float meanY,
          unsigned clusterPositionX, unsigned clusterPositionY, uint64_t shape);
  Cluster(unsigned chipID, unsigned eventID, unsigned clusterPositionX,
          unsigned clusterPositionY, uint64_t shape);
  Cluster(const Cluster &cluster);

  inline unsigned GetChipID() const { return fChipID; }
  inline unsigned GetEventID() const { return fEventID; }
  inline unsigned GetClusterPositionX() const { return fClusterPositionX; }
  inline unsigned GetClusterPositionY() const { return fClusterPositionY; }
  inline uint64_t GetShape() const { return fShape; }
  inline float GetMeanX() const { return fMeanX; }
  inline float GetMeanY() const { return fMeanY; }
  inline unsigned GetClusterSize() const { return fClusterSize; }
  inline unsigned GetClusterID() const { return fClusterID; }

  void Print();

  ClassDef(Cluster, 1);

  uint8_t operator[](int idx) { return (fShape >> idx) & 255; }

private:
  unsigned fChipID;
  unsigned fEventID;
  unsigned fClusterPositionX;
  unsigned fClusterPositionY;
  uint64_t fShape;
  double fMeanX;
  double fMeanY;
  unsigned fClusterSize;
  unsigned fClusterID;

  static unsigned fClusterCounter;
};

unsigned Cluster::fClusterCounter = 0;

Cluster::Cluster(unsigned chipID, unsigned eventID, unsigned clusterPositionX,
                 unsigned clusterPositionY, uint64_t shape)
    : fChipID(chipID), fEventID(eventID), fClusterPositionX(clusterPositionX),
      fClusterPositionY(clusterPositionY), fClusterSize(0), fShape(shape),
      fClusterID(fClusterCounter++) {
  // for (unsigned i = 0; i < MAX_CLUSTER_ROWS; i++) {
  //     for (unsigned j = 0; j < MAX_CLUSTER_COLS; j++) {
  //         continue;
  //         if (fShape[i][j]) {
  //             fMeanX += i;
  //             fMeanY -= j;
  //             fClusterSize++;
  //
  //         }
  //     }
  // }
  fMeanX /= fClusterSize;
  fMeanY /= fClusterSize;
  fMeanX += fClusterPositionX;
  fMeanY += fClusterPositionY;
}

Cluster::Cluster(unsigned chipID, unsigned eventID, float meanX, float meanY,
                 unsigned clusterPositionX, unsigned clusterPositionY,
                 uint64_t shape)
    : fChipID(chipID), fEventID(eventID), fMeanX(meanX), fMeanY(meanY),
      fClusterPositionX(clusterPositionX), fClusterPositionY(clusterPositionY),
      fClusterSize(0), fShape(shape), fClusterID(fClusterCounter++) {
  for (unsigned i = 0; i < MAX_CLUSTER_ROWS; i++) {
    for (unsigned j = 0; j < MAX_CLUSTER_COLS; j++) {
      const int position = i * MAX_CLUSTER_COLS + j;
      uint64_t mask = 1ULL << position;
      uint64_t bit = (fShape & mask) >> position;
      if (position == 1) {
        fClusterSize++;
      }
    }
  }
}

Cluster::Cluster(unsigned chipID, unsigned eventID, float meanX, float meanY,
                 unsigned clusterPositionX, unsigned clusterPositionY,
                 unsigned clusterSize, uint64_t shape)
    : fChipID(chipID), fEventID(eventID), fMeanX(meanX), fMeanY(meanY),
      fClusterPositionX(clusterPositionX), fClusterPositionY(clusterPositionY),
      fClusterSize(clusterSize), fShape(shape), fClusterID(fClusterCounter++) {}

Cluster::Cluster(const Cluster &cluster)
    : TObject(cluster), fChipID(cluster.fChipID), fEventID(cluster.fEventID),
      fClusterPositionX(cluster.fClusterPositionX),
      fClusterPositionY(cluster.fClusterPositionY), fShape(cluster.fShape),
      fMeanX(cluster.fMeanX), fMeanY(cluster.fMeanY),
      fClusterSize(cluster.fClusterSize), fClusterID(cluster.fClusterID) {}

void Cluster::Print() {
  std::cout << "Cluster ID: " << fClusterID << std::endl;
  std::cout << "Chip ID: " << fChipID << std::endl;
  std::cout << "Event ID: " << fEventID << std::endl;
  std::cout << "Cluster Position X: " << fClusterPositionX << std::endl;
  std::cout << "Cluster Position Y: " << fClusterPositionY << std::endl;
  std::cout << "Mean X: " << fMeanX << std::endl;
  std::cout << "Mean Y: " << fMeanY << std::endl;
  std::cout << "Cluster Size: " << fClusterSize << std::endl;
  std::cout << "Shape: " << std::endl;
  for (unsigned i = 0; i < MAX_CLUSTER_ROWS; i++) {
    for (unsigned j = 0; j < MAX_CLUSTER_COLS; j++) {
      const int position = i * MAX_CLUSTER_COLS + j;
      uint64_t mask = 1ULL << position;
      uint64_t bit = (fShape & mask) >> position;
      std::cout << bit;
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}
