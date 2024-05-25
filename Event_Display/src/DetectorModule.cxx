#include <Riostream.h>

#include <TGeoManager.h>
#include <TGeoMaterial.h>
#include <TGeoMedium.h>
#include <TGeoVolume.h>

#include <TString.h>

#include "DetectorChip.h"
#include "DetectorModule.h"

#include "../include/Materials.h"

DetectorModule::DetectorModule(const DetectorModule &module) {
  fModuleID = module.fModuleID;
  fNChipsX = module.fNChipsX;
  fNChipsY = module.fNChipsY;
  fChipGapX = module.fChipGapX;
  fChipGapY = module.fChipGapY;
  fSizeX = module.fSizeX;
  fSizeY = module.fSizeY;
  fSizeZ = module.fSizeZ;
  fPosX = module.fPosX;
  fPosY = module.fPosY;
  fPosZ = module.fPosZ;
  fChip = module.fChip;
  fChipIDs = new unsigned *[fNChipsX];
  for (unsigned ix = 0; ix < fNChipsX; ix++) {
    fChipIDs[ix] = new unsigned[fNChipsY];
    for (unsigned iy = 0; iy < fNChipsY; iy++) {
      fChipIDs[ix][iy] = module.fChipIDs[ix][iy];
    }
  }
}

DetectorModule::~DetectorModule() {
  for (unsigned ix = 0; ix < fNChipsX; ix++) {
    delete[] fChipIDs[ix];
  }
  delete[] fChipIDs;
}

/**
 * @brief Get the medium for the module (carbon fiber)
 */
TGeoMedium *DetectorModule::GetModuleMedium(const unsigned mediumID) {
  Carbon C;
  return new TGeoMedium("carbon", mediumID,
                        new TGeoMaterial(C.GetName(), C.GetZ(), C.GetA(), C.GetDensity()));
}

template <size_t nChipsX, size_t nChipsY>
void DetectorModule::Init(const unsigned moduleID, const double chipGapX,
                          const double chipGapY, const double sizeZ,
                          const DetectorChip &chip,
                          unsigned (&chipIDs)[nChipsX][nChipsY]) {

  if (fInit) {
    std::cerr << "Module already initialized!" << std::endl;
    return;
  }

  fModuleID = moduleID;
  fNChipsX = nChipsX;
  fNChipsY = nChipsY;
  fChipGapX = chipGapX;
  fChipGapY = chipGapY;
  fSizeZ = sizeZ;
  fChip = chip;

  fSizeX = nChipsX * chip.GetSizeX() + (nChipsX + 1) * chipGapX;
  fSizeY = nChipsY * chip.GetSizeY() + (nChipsY + 1) * chipGapY;

  fChipIDs = new unsigned *[fNChipsX];
  for (unsigned ix = 0; ix < fNChipsX; ix++) {
    fChipIDs[ix] = new unsigned[fNChipsY];
    for (unsigned iy = 0; iy < fNChipsY; iy++) {
      fChipIDs[ix][iy] = chipIDs[ix][iy];
    }
  }

  fInit = true;
}

/**
 * @brief Build the detector module
 * @param geometry TGeoManager object
 * @param medium TGeoMedium object
 * @param moduleName Name of the module

*/
TGeoVolume* DetectorModule::Build(TGeoManager &geometry, TGeoMedium &medium,
                           const char *moduleName) {
  fModuleVolume = geometry.MakeBox(moduleName, &medium, fSizeX / 2.,
                                    fSizeY / 2., fSizeZ / 2.);
  return fModuleVolume;
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
  DetectorModule::Build(*geometry, *GetModuleMedium(2), "module");
  world->AddNode(fModuleVolume, 1, new TGeoTranslation(0, 0, 0));

  TGeoMedium *chipMedium = fChip.GetChipMedium(3);
  TGeoVolume *chip;
  for (unsigned ix = 0; ix < fNChipsX; ix++) {
    for (unsigned iy = 0; iy < fNChipsY; iy++) {
      fChip.Build(*geometry, *chipMedium, Form("chip_%d", fChipIDs[ix][iy]));
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

void DetectorModule::Print() const {
  std::cout << "Module ID: " << fModuleID << std::endl;
  std::cout << "Number of chips in x: " << fNChipsX << std::endl;
  std::cout << "Number of chips in y: " << fNChipsY << std::endl;
  std::cout << "Chip gap in x: " << fChipGapX << " cm" << std::endl;
  std::cout << "Chip gap in y: " << fChipGapY << " cm" << std::endl;
  std::cout << "Module size in x: " << fSizeX << " cm" << std::endl;
  std::cout << "Module size in y: " << fSizeY << " cm" << std::endl;
  std::cout << "Module size in z: " << fSizeZ << " cm" << std::endl;
  std::cout << "Module position: (" << fPosX << ", " << fPosY << ", " << fPosZ
            << ") cm" << std::endl;
  std::cout << "Chip IDs:" << std::endl;
  for (unsigned ix = 0; ix < fNChipsX; ix++) {
    for (unsigned iy = 0; iy < fNChipsY; iy++) {
      std::cout << fChipIDs[ix][iy] << " ";
    }
    std::cout << std::endl;
  }
}
