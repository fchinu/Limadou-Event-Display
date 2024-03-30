#include <Riostream.h>

#include <TGeoManager.h>
#include <TGeoMaterial.h>
#include <TGeoMedium.h>
#include <TGeoVolume.h>

#include <TString.h>

#include "DetectorChip.h"
#include "DetectorModule.h"
// #include "../include/DetectorModule.h"
#include "../include/Materials.h"

template <size_t chipsY, size_t chipsX>
DetectorModule::DetectorModule(const unsigned moduleID, const unsigned nChipsX,
                               const unsigned nChipsY, const double chipGapX,
                               const double chipGapY, const double sizeZ,
                               const DetectorChip &chip,
                               unsigned (&chipIDs)[chipsY][chipsX])
    : fModuleID(moduleID), fNChipsX(nChipsX), fNChipsY(nChipsY),
      fChipGapX(chipGapX), fChipGapY(chipGapY), fSizeZ(sizeZ), fChip(chip),
      fModuleVolume(NULL) {

  fSizeX = nChipsX * chip.GetSizeX() + (nChipsX + 1) * chipGapX;
  fSizeY = nChipsY * chip.GetSizeY() + (nChipsY + 1) * chipGapY;

  if (chipsY != nChipsY || chipsX != nChipsX) {
    std::cerr << "Error: Chip ID array size does not match the number of chips "
                 "in the module"
              << std::endl;
    return;
  }

  fChipIDs = new unsigned *[fNChipsY];
  for (unsigned iy = 0; iy < fNChipsY; iy++) {
    fChipIDs[iy] = new unsigned[fNChipsX];
    for (unsigned ix = 0; ix < fNChipsX; ix++) {
      fChipIDs[iy][ix] = chipIDs[iy][ix];
    }
  }
}

DetectorModule::~DetectorModule() {
  for (unsigned iy = 0; iy < fNChipsY; iy++) {
    delete[] fChipIDs[iy];
  }
  delete[] fChipIDs;
  delete fModuleVolume;
}

/**
 * @brief Get the medium for the module (carbon fiber)
 */
TGeoMedium *DetectorModule::GetModuleMedium(const unsigned mediumID) {
  Carbon C;
  return new TGeoMedium("carbon", mediumID,
                        new TGeoMaterial(C.fMaterial, C.fZ, C.fA, C.fDensity));
}

/**
 * @brief Build the detector module
 * @param geometry TGeoManager object
 * @param medium TGeoMedium object
 * @param moduleName Name of the module

*/
void DetectorModule::Build(TGeoManager *geometry, TGeoMedium *medium,
                           const char *moduleName) {
  fModuleVolume = geometry->MakeBox(moduleName, medium, fSizeX / 2.,
                                    fSizeY / 2., fSizeZ / 2.);
}

/**
 * @brief Show the detector module in OpenGL
 */
void DetectorModule::Show() {
  TGeoManager *geometry =
      new TGeoManager("geometry", "Detector module geometry");

  // top volume
  TGeoMedium *vacuum =
      new TGeoMedium("vacuum", 1, new TGeoMaterial("Vacuum", 0, 0, 0));
  TGeoVolume *world =
      geometry->MakeBox("world", vacuum, 2 * fSizeX, 2 * fSizeY, 10 * fSizeZ);
  geometry->SetTopVolume(world);
  geometry->SetTopVisible(false);

  // module
  DetectorModule::Build(geometry, GetModuleMedium(2), "module");
  world->AddNode(fModuleVolume, 1, new TGeoTranslation(0, 0, 0));

  TGeoMedium *chipMedium = fChip.GetChipMedium(3);
  TGeoVolume *chip;
  for (unsigned iy = 0; iy < fNChipsY; iy++) {
    for (unsigned ix = 0; ix < fNChipsX; ix++) {
      fChip.Build(geometry, chipMedium, Form("chip_%d", fChipIDs[iy][ix]));
      chip = fChip.GetChipVolume();
      chip->SetLineColor(kRed);
      world->AddNodeOverlap(chip, 1,
                            new TGeoTranslation(DetectorModule::GetChipXPos(ix),
                                                DetectorModule::GetChipYPos(iy),
                                                0.1 * fChip.GetSizeZ()));
    }
  }

  geometry->CloseGeometry();
  world->SetVisibility(false);

  world->Draw("ogl");
}
