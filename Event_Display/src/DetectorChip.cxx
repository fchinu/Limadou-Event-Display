#include <Riostream.h>

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

TGeoMedium *DetectorChip::GetChipMedium(const unsigned mediumID) {
  Silicon Si;
  return new TGeoMedium(
      "silicon", mediumID,
      new TGeoMaterial(Si.GetName(), Si.GetZ(), Si.GetA(), Si.GetDensity()));
}

TGeoVolume *DetectorChip::Build(TGeoManager &geometry, TGeoMedium &medium,
                                const char *chipName) {
  fChipVolume = geometry.MakeBox(chipName, &medium, fSizeX / 2., fSizeY / 2.,
                                 fSizeZ / 2.);
  return fChipVolume;
}

void DetectorChip::Print() const {
  std::cerr << "Chip ID: " << fChipID << std::endl;
  std::cerr << "Number of pixels in x: " << fNPixelsX << std::endl;
  std::cerr << "Number of pixels in y: " << fNPixelsY << std::endl;
  std::cerr << "Pixel size in x: " << fPxSizeX << " cm" << std::endl;
  std::cerr << "Pixel size in y: " << fPxSizeY << " cm" << std::endl;
  std::cerr << "Chip size in x: " << fSizeX << " cm" << std::endl;
  std::cerr << "Chip size in y: " << fSizeY << " cm" << std::endl;
  std::cerr << "Chip size in z: " << fSizeZ << " cm" << std::endl;
  std::cerr << "Chip position: (" << fPosX << ", " << fPosY << ", " << fPosZ
            << ") cm" << std::endl;
}

void DetectorChip::Show() {

  std::cerr << "DetectorChip::Show() not implemented" << std::endl;
  // TGeoManager *geometry = new TGeoManager("geometry", "Detector chip
  // geometry"); TGeoMedium *vacuum =
  //     new TGeoMedium("vacuum", 1, new TGeoMaterial("Vacuum", 0, 0, 0));
  // TGeoVolume *world =
  //     geometry->MakeBox("world", vacuum, 2 * fSizeX, 2 * fSizeY, 10 *
  //     fSizeZ);
  //
  // TGeoMedium *medium = GetChipMedium(2);
  // DetectorChip::Build(geometry, medium, "chip");
  // world->AddNodeOverlap(fChipVolume, 1, new TGeoTranslation(0, 0, 0));
  //
  // geometry->CloseGeometry();
  // geometry->SetVisLevel(4);
  // geometry->SetVisOption(0);
  //
  // world->Draw("ogl");
}