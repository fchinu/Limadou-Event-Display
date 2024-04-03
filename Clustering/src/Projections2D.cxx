#include "TCanvas.h"
#include "Clustering/include/Projections2D.h"

Projections2D::Projections2D(std::vector<Cluster> clusters) : 
fClusters(clusters), fCanvas(TCanvas("ProjectionCanvas", "ProjectionCanvas", 1280, 720))
{
    gStyle->SetPalette(kBird, 0, 0.6);
    for (auto const& cluster : fClusters) {
        fX[cluster.GetChipID()].push_back(cluster.GetMeanX());
        fY[cluster.GetChipID()].push_back(cluster.GetMeanY());
        fClusterSizes[cluster.GetChipID()].push_back(cluster.GetClusterSize()*1000);
        fColors[cluster.GetChipID()].push_back(gRandom->Rndm(1));
        std::cout << "Cluster size: " << cluster.GetClusterSize() << std::endl;
        std::cout << "Cluster ID: " << cluster.GetClusterID() << std::endl;
    }

    for (auto i = 0; i < N_CHIPS; i++) {
        fChipsHistos[i] = new TScatter(fClusterSizes[i].size(), fX[i].data(), fY[i].data(), fColors[i].data(), fClusterSizes[i].data());
        fChipsHistos[i]->SetMarkerStyle(20);
        fChipsHistos[i]->SetMarkerColor(kRed);
    }

    fCanvas.Divide(5, 2);
    for (auto i = 0; i < N_CHIPS; i++) {
        fCanvas.cd(i + 1);
        gPad->DrawFrame(0, 0, N_PIXELS_X, N_PIXELS_Y);
        fChipsHistos[i]->Draw();
    }
    fCanvas.Modified();
    fCanvas.Update();
    fCanvas.SaveAs("Clustering/out/Projections2D.root");
    fCanvas.SaveAs("Clustering/out/Projections2D.pdf");
        
}

