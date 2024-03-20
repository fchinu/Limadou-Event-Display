#include <iostream>
#include <bitset>
#include "TH2D.h"
#include "TCanvas.h"
#include "TStyle.h"

void fillBinaryMatrix(TH2D* hist, const uint8_t* ExampleArray, int size, int max_length, int xClusterPosition, int yClusterPosition) {
    for (int i = 0; i < size; ++i) {
        std::bitset<8> bits(ExampleArray[i]);
        for (int j = 0; j < max_length; j++) {
            hist->Fill(xClusterPosition + j, yClusterPosition - i-1, bits[max_length - 1 - j]); // Adjusting the y-position
        }
    }
}

void ClusterShapeDisplay() {
    //need to link t cluster class
    //uint8_t ExampleArray[] = {16, 48, 48, 224, 32, 0, 0, 0};// Example array
    uint8_t ExampleArray[] = {192, 192, 80, 248, 16, 16, 16, 16};
    int size = sizeof(ExampleArray) / sizeof(ExampleArray[0]);
    int max_length = 8;
    //int xClusterPosition = 123;
    //int yClusterPosition = 456;
    int xClusterPosition = 379;
    int yClusterPosition = 28;

    TH2D* hist = new TH2D("Cluster", "Cluster", max_length, xClusterPosition, xClusterPosition + max_length, size, yClusterPosition - size, yClusterPosition);

    fillBinaryMatrix(hist, ExampleArray, size, max_length, xClusterPosition, yClusterPosition);

    TCanvas* canvas = new TCanvas("canvas", "Canvas", 800, 600);
    gStyle->SetOptStat(0);
    hist->Draw("col");
    canvas->SaveAs("clusterShape1.png");

    delete hist;
    delete canvas;
}






