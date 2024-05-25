#pragma once

#include <vector>

#include <TGeoManager.h>
#include <TGeoMedium.h>
#include <TGeoVolume.h>

#include "Geometry.h"

class Display {

public:
  Display(const Geometry &geometry, const double worldSizeX,
          const double worldSizeY, const double worldSizeZ);
  ~Display();

  void TestBuild();
  void Build();
  void Run();
  void RunLive();
  void Update() { return; }

  void AddChip(const unsigned chipID, const unsigned moduleID);
  void AddGeometry();

private:
  TGeoManager *fGeoManager;
  TGeoMedium *fVacuum;
  // const std::unique_ptr<TGeoMedium> fVacuum =
  // std::make_unique<TGeoMedium>("Vacuum", 1, new TGeoMaterial("Vacuum", 0, 0,
  // 0));
  TGeoVolume *fWorld;

  const Geometry &fGeometry;

  std::vector<TGeoVolume *> fDetectorVolumes;
  std::vector<int> fPixelsOn; // vector of pixel idx in fVolumes
};