#include "TCanvas.h"
#include "TH2D.h"
#include "TStyle.h"
#include <TGraphErrors.h>
#include <TMarker.h>
#include <bitset>
#include <iostream>

void fillBinaryMatrix(TH2D *histCluster, const uint8_t *ExampleArray, int size,
                      int max_length, int xClusterPosition,
                      int yClusterPosition) {
  for (int i = 0; i < size; ++i) {
    std::bitset<8> bits(ExampleArray[i]);
    for (int j = 0; j < max_length; j++) {
      histCluster->Fill(xClusterPosition + j, yClusterPosition - i - 1,
                        bits[max_length - 1 - j]); // Adjusting the y-position
    }
  }
}

void ClusterShapeDisplay() {
  // need to link t cluster class
  uint8_t ExampleArray[] = {0b00000010,
                            0b00000011,
                            0b00000010,
                            0b00000000,
                            0b00000000,
                            0b00000000,
                            0b00000000,
                            0b00000000};
  //uint8_t ExampleArray[] = {16, 48, 48, 224, 32, 0, 0, 0}; // Example array
  // uint8_t ExampleArray[] = {192, 192, 80, 248, 16, 16, 16, 16};
  int size = sizeof(ExampleArray) / sizeof(ExampleArray[0]);
  int max_length = 8;
  int xClusterPosition = 123;
  int yClusterPosition = 456;
  // int xClusterPosition = 379;
  // int yClusterPosition = 28;
  double xMean = 125;
  double yMean = 453.5;
  double xErrorBar = 2;
  double yErrorBar = 2.5;
  // double xMean=381.5; //to be linked to the cluster class, made with mean of
  // random numbers used before double yMean=24.0; double xErrorBar=2.5; double
  // yErrorBar=4.0;

  TH2D *histCluster = new TH2D("Cluster", "Cluster", max_length,
                               xClusterPosition, xClusterPosition + max_length,
                               size, yClusterPosition - size, yClusterPosition);

  fillBinaryMatrix(histCluster, ExampleArray, size, max_length,
                   xClusterPosition, yClusterPosition);

  TCanvas *canvas = new TCanvas("canvas", "Canvas", 1000, 1000);
  gStyle->SetOptStat(0);
  gPad->SetGrid();
  histCluster->Draw("col");
  histCluster->GetXaxis()->SetTitle("X (pixel)");
  histCluster->GetYaxis()->SetTitle("Y (pixel)");
  TGraphErrors *PointGraph = new TGraphErrors();
  PointGraph->SetPoint(0, xMean, yMean);
  PointGraph->SetPointError(0, xErrorBar, yErrorBar);
  PointGraph->SetLineColor(kRed);
  PointGraph->SetLineWidth(3);
  PointGraph->SetMarkerStyle(20);
  PointGraph->SetMarkerColor(kRed);
  PointGraph->SetMarkerSize(2);
  PointGraph->Draw("P,same");

  canvas->Update();
  canvas->SaveAs("clusterShape3.png");

  delete histCluster;
  delete canvas;
}
