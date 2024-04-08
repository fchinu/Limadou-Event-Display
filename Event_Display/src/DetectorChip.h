#pragma once

#include <TGeoManager.h>
#include <TGeoMedium.h>
#include <TGeoVolume.h>

class DetectorChip {
public:
  DetectorChip()
      : fChipID(0), fNPixelsX(0), fNPixelsY(0), fPxSizeX(0.), fPxSizeY(0.),
        fSizeX(0.), fSizeY(0.), fSizeZ(0.), fChipVolume(NULL){};
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
        fSizeY(nPixelsY * pxSizeY), fSizeZ(sizeZ), fChipVolume(NULL){};
  DetectorChip(const DetectorChip &chip)
      : fChipID(chip.fChipID), fNPixelsX(chip.fNPixelsX),
        fNPixelsY(chip.fNPixelsY), fPxSizeX(chip.fPxSizeX),
        fPxSizeY(chip.fPxSizeY), fSizeX(chip.fSizeX), fSizeY(chip.fSizeY),
        fSizeZ(chip.fSizeZ), fChipVolume(NULL){};
  ~DetectorChip() { delete fChipVolume; };
  DetectorChip operator=(const DetectorChip &chip);

  inline double GetSizeX() const { return fSizeX; };
  inline double GetSizeY() const { return fSizeY; };
  inline double GetSizeZ() const { return fSizeZ; };

  inline double GetPxSizeX() const { return fPxSizeX; };
  inline double GetPxSizeY() const { return fPxSizeY; };

  inline TGeoVolume *GetChipVolume() const { return fChipVolume; };
  TGeoMedium *GetChipMedium(const unsigned mediumID);

  void Build(TGeoManager *geometry, TGeoMedium *medium, const char *chipName);
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

  TGeoVolume *fChipVolume;
};