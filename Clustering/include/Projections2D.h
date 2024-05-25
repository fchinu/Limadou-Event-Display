#pragma once

#include "Clustering/include/Cluster.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TRandom.h"
#include "TScatter.h"
#include "TStyle.h"
#include <vector>
#define N_CHIPS 10
#define N_PIXELS_X 512
#define N_PIXELS_Y 1024

class Projections2D {

public:
  Projections2D(std::vector<Cluster> clusters);
  //~Projections2D() {delete fCanvas;}

  // void const DrawProjections();

private:
  std::vector<Cluster> fClusters;
  std::array<std::vector<double>, N_CHIPS> fClusterSizes;
  std::array<std::vector<double>, N_CHIPS> fX;
  std::array<std::vector<double>, N_CHIPS> fY;
  std::array<std::vector<double>, N_CHIPS> fColors;
  TCanvas fCanvas;
  std::array<TScatter *, N_CHIPS> fChipsHistos;
};