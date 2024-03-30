#include <TGeoManager.h>
#include <TGeoMaterial.h>
#include <TGeoMedium.h>
#include <TGeoVolume.h>

#include "DetectorChip.h"
// #include "../include/DetectorChip.h"
#include "../include/Materials.h"

DetectorChip DetectorChip::operator=(const DetectorChip &chip) {
  fChipID = chip.fChipID;
  fNPixelsX = chip.fNPixelsX;
  fNPixelsY = chip.fNPixelsY;
  fPxSizeX = chip.fPxSizeX;
  fPxSizeY = chip.fPxSizeY;
  fSizeX = chip.fSizeX;
  fSizeY = chip.fSizeY;
  fSizeZ = chip.fSizeZ;
  fChipVolume = NULL;
  return *this;
}

TGeoMedium *DetectorChip::GetChipMedium(const unsigned mediumlID) {
  Silicon Si;
  return new TGeoMedium(
      "silicon", mediumlID,
      new TGeoMaterial(Si.fMaterial, Si.fZ, Si.fA, Si.fDensity));
}

void DetectorChip::Build(TGeoManager *geometry, TGeoMedium *medium,
                         const char *chipName) {
  fChipVolume = geometry->MakeBox(chipName, medium, fSizeX / 2., fSizeY / 2.,
                                  fSizeZ / 2.);
}

void DetectorChip::Show() {

  TGeoManager *geometry = new TGeoManager("geometry", "Detector chip geometry");
  TGeoMedium *vacuum =
      new TGeoMedium("vacuum", 1, new TGeoMaterial("Vacuum", 0, 0, 0));
  TGeoVolume *world =
      geometry->MakeBox("world", vacuum, 2 * fSizeX, 2 * fSizeY, 10 * fSizeZ);

  TGeoMedium *medium = GetChipMedium(2);
  DetectorChip::Build(geometry, medium, "chip");
  world->AddNodeOverlap(fChipVolume, 1, new TGeoTranslation(0, 0, 0));

  geometry->CloseGeometry();
  geometry->SetVisLevel(4);
  geometry->SetVisOption(0);

  world->Draw("ogl");
}