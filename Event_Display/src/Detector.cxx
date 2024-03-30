#include <TString.h>

#include <TGeoManager.h>
#include <TGeoMaterial.h>
#include <TGeoMedium.h>
#include <TGeoVolume.h>

#include "Detector.h"
#include "DetectorChip.h"
#include "DetectorModule.h"

Detector::Detector(const unsigned nModules, const double moduleDisalignmentX,
                   const double moduleDisalignmentY, double *modulePosZ,
                   const DetectorModule &module, unsigned *moduleIDs)
    : fNModules(nModules), fModuleDisalignmentX(moduleDisalignmentX),
      fModuleDisalignmentY(moduleDisalignmentY), fModulePosZ(NULL),
      fModule(module), fModuleIDs(NULL) {
  fModulePosZ = new double[fNModules];
  fModuleIDs = new unsigned[fNModules];
  for (unsigned imodule = 0; imodule < fNModules; imodule++) {
    fModulePosZ[imodule] = modulePosZ[imodule];
    fModuleIDs[imodule] = moduleIDs[imodule];
  }
}

Detector::~Detector() {
  delete[] fModulePosZ;
  delete[] fModuleIDs;
}

void Detector::Show() {
  // initialize world sizes
  const double xSize = fModule.GetSizeX() + fModuleDisalignmentX;
  const double ySize = fModule.GetSizeY() + fModuleDisalignmentY;
  double zSize = 0.;
  for (unsigned iz = 0; iz < fNModules; iz++) {
    zSize += fModule.GetSizeZ() + fModulePosZ[iz];
  }

  // initialize offset (to center everything)
  const double xOffset = -fModuleDisalignmentX / 2.;
  const double yOffset = -fModuleDisalignmentY / 2.;
  double zOffset = 0.;
  for (unsigned iz = 0; iz < fNModules; iz++) {
    zOffset -= fModulePosZ[iz] / 2.;
  }

  TGeoManager *geometry = new TGeoManager("geometry", "Detector chip geometry");
  TGeoMedium *vacuum =
      new TGeoMedium("vacuum", 1, new TGeoMaterial("Vacuum", 0, 0, 0));
  TGeoVolume *world =
      geometry->MakeBox("world", vacuum, 2 * xSize, 2 * ySize, 2 * zSize);
  geometry->SetTopVolume(world);
  geometry->SetTopVisible(false);

  TGeoMedium *moduleMedium = fModule.GetModuleMedium(2);
  TGeoVolume *module;

  DetectorChip Chip = fModule.GetChip();
  TGeoMedium *chipMedium = Chip.GetChipMedium(3);
  TGeoVolume *chip;

  double zPosModule = zOffset;
  for (unsigned imodule = 0; imodule < fNModules; imodule++) {
    // build module
    double xPosModule = xOffset;
    double yPosModule = yOffset;
    if (imodule % 2 == 0) {
      xPosModule += fModuleDisalignmentX;
      yPosModule += fModuleDisalignmentY;
    }
    zPosModule += fModulePosZ[imodule];

    fModule.Build(geometry, moduleMedium,
                  Form("module_%d", fModuleIDs[imodule]));
    module = fModule.GetModuleVolume();
    module->SetLineColor(kGray + 3);
    world->AddNode(module, 1,
                   new TGeoTranslation(xPosModule, yPosModule, zPosModule));

    // build chips of the module
    for (unsigned iy = 0; iy < fModule.GetNChipsY(); iy++) {
      for (unsigned ix = 0; ix < fModule.GetNChipsX(); ix++) {
        Chip.Build(
            geometry, chipMedium,
            Form("chip_%d", fModule.GetChipID(ix, iy) +
                                (fModule.GetModuleID() * fModule.GetNChipsX() *
                                 fModule.GetNChipsY())));
        chip = Chip.GetChipVolume();
        chip->SetLineColor(kOrange - 5);
        world->AddNodeOverlap(
            chip, 1,
            new TGeoTranslation(xPosModule + fModule.GetChipXPos(ix),
                                yPosModule + fModule.GetChipYPos(iy),
                                zPosModule + 0.1 * Chip.GetSizeZ()));
      }
    }
  }

  geometry->CloseGeometry();
  world->SetAttVisibility(false);

  world->Draw("ogl");
}
