#pragma once

#include <TGeoManager.h>
#include <TGeoVolume.h>

#include "DetectorChip.h"
#include "DetectorModule.h"

class Detector {
public:
  Detector()
      : fNModules(0), fModuleDisalignmentX(0.), fModuleDisalignmentY(0.),
        fModulePosZ(NULL), fModule(), fModuleIDs(NULL){};
  /**
   * @brief Construct a new Detector object
   * @param nModules Number of modules
   * @param moduleGapZ Gap between modules in the z direction (cm)
   * @param module Module object (all modules are assumed identical)
   */
  Detector(const unsigned nModules, const double moduleDisalignmentX,
           const double moduleDisalignmentY, double *modulePosZ,
           const DetectorModule &module, unsigned *moduleIDs);
  ~Detector();

  inline double GetModuleDisalignmentY() const { return fModuleDisalignmentY; };
  inline double GetModulePosZ(const unsigned imodule) const {
    return fModulePosZ[imodule];
  };
  inline unsigned GetNModules() const { return fNModules; };

  void Show();

private:
  unsigned fNModules;

  double fModuleDisalignmentX; // cm
  double fModuleDisalignmentY; // cm
  double *fModulePosZ;         // cm

  DetectorModule fModule;
  unsigned *fModuleIDs;
};