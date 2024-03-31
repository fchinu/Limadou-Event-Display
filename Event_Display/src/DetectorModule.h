#pragma once

#include <TGeoManager.h>
#include <TGeoMedium.h>
#include <TGeoVolume.h>

#include "DetectorChip.h"

class DetectorModule {
public:
  DetectorModule(){};
  /**
   * @brief Construct a new Detector Module object
   *
   *
   * @tparam nChipsX Number of chips in the x direction
   * @tparam nChipsY Number of chips in the y direction
   *
   * @param moduleID Module ID
   * @param chipGapX Gap between chips in the x direction (cm)
   * @param chipGapY Gap between chips in the y direction (cm)
   * @param sizeZ Module size in the z direction (cm)
   * @param chip Chip object (all chips on the module are assumed identical)
   */
  template <size_t nChipsX, size_t nChipsY>
  DetectorModule(const unsigned moduleID, const double chipGapX,
                 const double chipGapY, const double sizeZ,
                 const DetectorChip &chip,
                 unsigned (&chipIDs)[nChipsX][nChipsY]);
  ~DetectorModule();

  inline double GetSizeX() const { return fSizeX; };
  inline double GetSizeY() const { return fSizeY; };
  inline double GetSizeZ() const { return fSizeZ; };

  inline unsigned GetNChipsX() const { return fNChipsX; };
  inline unsigned GetNChipsY() const { return fNChipsY; };

  inline double GetChipGapX() const { return fChipGapX; };
  inline double GetChipGapY() const { return fChipGapY; };

  /**
   * @brief Get the x position of the center of the ix-th pixel along the x axis
   */
  inline double GetChipXPos(const unsigned ix) {
    return ix * (fChip.GetSizeX() + fChipGapX) +
           (-int(fNChipsX) / 2. + 0.5) * (fChip.GetSizeX() + fChipGapX);
  };
  /**
   * @brief Get the y position of the center of the iy-th pixel along the y axis
   */
  inline double GetChipYPos(const unsigned iy) {
    return iy * (fChip.GetSizeY() + fChipGapY) +
           (-int(fNChipsY) / 2. + 0.5) * (fChip.GetSizeY() + fChipGapY);
  };

  /**
   * Returns a DetectorChip with correct sizes and attribute. ChipID is
   * auto-initialized.
   */
  inline DetectorChip GetChip() const { return fChip; };
  inline unsigned GetChipID(const unsigned ix, const unsigned iy) const {
    return fChipIDs[ix][iy];
  };
  inline unsigned GetModuleID() const { return fModuleID; };

  inline TGeoVolume *GetModuleVolume() const { return fModuleVolume; };
  TGeoMedium *GetModuleMedium(const unsigned mediumID);

  /**
   * @brief Initialization function. Used in pythonization of the package.
   *
   * @tparam nChipsX Number of chips in the x direction
   * @tparam nChipsY Number of chips in the y direction
   *
   * @param moduleID Module ID
   * @param chipGapX Gap between chips in the x direction (cm)
   * @param chipGapY Gap between chips in the y direction (cm)
   * @param sizeZ Module size in the z direction (cm)
   * @param chip Chip object (all chips on the module are assumed identical)
   */
  template <size_t nChipsX, size_t nChipsY>
  void Init(const unsigned moduleID, const double chipGapX,
            const double chipGapY, const double sizeZ, const DetectorChip &chip,
            unsigned (&chipIDs)[nChipsX][nChipsY]);
  void Build(TGeoManager *geometry, TGeoMedium *medium, const char *moduleName);
  void Show();

private:
  bool fInit;

  unsigned fNChipsX;
  unsigned fNChipsY;

  double fChipGapX; // cm
  double fChipGapY; // cm

  double fSizeX; // cm
  double fSizeY; // cm
  double fSizeZ; // cm

  unsigned fModuleID;

  DetectorChip fChip;
  unsigned **fChipIDs; // [fNChipsY][fNChipsX]

  TGeoVolume *fModuleVolume;
};