#pragma once

#include <TGeoManager.h>
#include <TGeoMedium.h>
#include <TGeoVolume.h>

class DetectorChip {
public:
  DetectorChip()
      : fChipID(0), fNPixelsX(0), fNPixelsY(0), fPxSizeX(0.), fPxSizeY(0.),
        fSizeX(0.), fSizeY(0.), fSizeZ(0.), fChipVolume(nullptr){};
  /**
   * @brief Construct a new Detector Chip object
   * @param chipID Chip ID
   * @param nPixelsX Number of pixels in the x direction
   * @param nPixelsY Number of pixels in the y direction
   * @param pxSizeX Pixel size in the x direction (cm)
   * @param pxSizeY Pixel size in the y direction (cm)
   * @param sizeZ Chip size in the z direction (cm)
   */
  DetectorChip(const unsigned chipID, const unsigned nPixelsX,
               const unsigned nPixelsY, const double pxSizeX,
               const double pxSizeY, const double sizeZ)
      : fChipID(chipID), fNPixelsX(nPixelsX), fNPixelsY(nPixelsY),
        fPxSizeX(pxSizeX), fPxSizeY(pxSizeY), fSizeX(nPixelsX * pxSizeX),
        fSizeY(nPixelsY * pxSizeY), fSizeZ(sizeZ),
        fPosX(0.), fPosY(0.), fPosZ(0.), fChipVolume(nullptr){};
  DetectorChip(const DetectorChip &chip)
      : fChipID(chip.fChipID), fNPixelsX(chip.fNPixelsX),
        fNPixelsY(chip.fNPixelsY), fPxSizeX(chip.fPxSizeX),
        fPxSizeY(chip.fPxSizeY), fSizeX(chip.fSizeX), fSizeY(chip.fSizeY),
        fSizeZ(chip.fSizeZ),
        fPosX(0.), fPosY(0.), fPosZ(0.), fChipVolume(nullptr){};
  ~DetectorChip() {}
  DetectorChip operator=(const DetectorChip &chip);

  /**
   * @brief Set the position of the chip
   */
  inline void SetPosition(const double x, const double y, const double z) {
    fPosX = x;
    fPosY = y;
    fPosZ = z;
  }

  inline double GetSizeX() const { return fSizeX; }
  inline double GetSizeY() const { return fSizeY; }
  inline double GetSizeZ() const { return fSizeZ; }

  inline double GetPosX() const { return fPosX; }
  inline double GetPosY() const { return fPosY; }
  inline double GetPosZ() const { return fPosZ; }

  inline double GetPxSizeX() const { return fPxSizeX; }
  inline double GetPxSizeY() const { return fPxSizeY; }

  inline TGeoVolume* GetChipVolume() const { return fChipVolume; }
  TGeoMedium* GetChipMedium(const unsigned mediumID);

  TGeoVolume* Build(TGeoManager &geometry, TGeoMedium &medium, const char *chipName);
  void Print() const;
  void Show();

private:
  unsigned fChipID;

  unsigned fNPixelsX;
  unsigned fNPixelsY;

  double fPxSizeX; // cm
  double fPxSizeY; // cm

  double fSizeX; // cm
  double fSizeY; // cm
  double fSizeZ; // cm

  double fPosX; // cm, chip position
  double fPosY; // cm, chip position
  double fPosZ; // cm, chip position

  TGeoVolume* fChipVolume;
};