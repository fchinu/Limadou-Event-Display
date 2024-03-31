#include <Riostream.h>
#include <TSystem.h>

#include "../src/Detector.h"
#include "../src/DetectorChip.h"
#include "../src/DetectorModule.h"
// #include "../include/DetectorChip.h"
// #include "../include/DetectorModule.h"

void Display() {
  // LoadMacros();

  const int nPixelsX = 1024;
  const int nPixelsY = 512;
  const double pxSizeX = 0.002924; // cm
  const double pxSizeY = 0.002688; // cm

  const int nChipsX = 5;
  const int nChipsY = 2;
  const double chipGapX = 0.0150; // cm
  const double chipGapY = 0.0150; // cm

  unsigned chipIDs[5][2] = {{0, 5}, {1, 6}, {2, 7}, {3, 8}, {4, 9}};

  const unsigned nModules = 3;
  const double moduleDisalignmentX = 0.;       // cm
  const double moduleDisalignmentY = 0.722312; // cm
  double modulePosZ[3] = {0., 0.85, 1.7};      // cm
  unsigned moduleIDs[3] = {0, 1, 2};

  double sizeZ = 0.05; // cm

  DetectorChip *chip =
      new DetectorChip(1, nPixelsX, nPixelsY, pxSizeX, pxSizeY, sizeZ);
  // chip->Show();
  DetectorModule *module =
      new DetectorModule(0, chipGapX, chipGapY, sizeZ, *chip, chipIDs);
  // module->Show();
  Detector *detector =
      new Detector(nModules, moduleDisalignmentX, moduleDisalignmentY,
                   modulePosZ, *module, moduleIDs);
  detector->Show();
}