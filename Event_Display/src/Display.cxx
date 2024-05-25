#include <Riostream.h>

#include <TH1F.h>
#include <TCanvas.h>
#include <TString.h>
#include <TSystem.h>
#include <TApplication.h>

#include "Display.h"
#include "../include/LimadouConstants.h"
#include "../include/Logger.h"
#include "../include/Materials.h"

Display::Display(const Geometry& geometry, const double worldSizeX, const double worldSizeY, const double worldSizeZ):
    fGeometry(geometry) {
    LOG_DEBUG("Display::Display() - fGeometry = %p", &fGeometry);
    fGeoManager = new TGeoManager("GeoManager", "Event Display");
    LOG_DEBUG("Display::Display() - fGeoManager = %p", fGeoManager);
    fVacuum = new TGeoMedium("Vacuum", 1, new TGeoMaterial("Vacuum", 0, 0, 0));
    fWorld = fGeoManager->MakeBox("World", fVacuum, worldSizeX, worldSizeY, worldSizeZ);  
    LOG_DEBUG("Display::Display() - fWorld = %p", fWorld);
    LOG_DEBUG("Display::Display() - fVacuum = %p", &fVacuum);
    fGeoManager->SetTopVolume(fWorld);
    fGeoManager->SetTopVisible(false);
    LOG_DEBUG("Display::Display() - fGeoManager->GetTopVolume() = %p", fGeoManager->GetTopVolume());
}

Display::~Display() {
    /*
    LOG_DEBUG("Display::~Display()");
    for (auto& volume : fDetectorVolumes) {
        delete volume;
    }
    fDetectorVolumes.clear();
    LOG_DEBUG("Display::~Display() - fDetectorVolumes.size() = %zu", fDetectorVolumes.size());
    
    //delete fCanvas;
    delete fWorld;
    delete fVacuum;
    delete fGeoManager;

    LOG_DEBUG("Display::~Display() - after CloseGeometry()");
    */
}

/**
 * @brief Build the detector geometry
*/
void Display::Build() {

    LOG_DEBUG("Display::Build()");
    
    fDetectorVolumes.clear();
    LOG_DEBUG("Display::Build() - fDetectorVolumes.size() = %zu", fDetectorVolumes.size());
    const int nVolumes = limadou::N_CHIPS_X * limadou::N_CHIPS_Y * limadou::N_MODULES + limadou::N_MODULES;
    LOG_DEBUG("Display::Build() - nVolumes = %d", nVolumes);
    fDetectorVolumes.reserve(nVolumes); 

    LOG_DEBUG("Display::Build() - fDetectorVolumes.size() = %zu", fDetectorVolumes.size());
    auto chipMaterial = fGeometry.GetChipMaterial();
    auto moduleMaterial = fGeometry.GetModuleMaterial();    
    
    LOG_DEBUG("Display::Build() - chipMaterial = %p", &chipMaterial);
    TGeoMedium* chipMedium = new TGeoMedium("chipMedium", 2, new TGeoMaterial(chipMaterial.GetName(), chipMaterial.GetA(), chipMaterial.GetZ(), chipMaterial.GetDensity()));
    TGeoMedium* moduleMedium = new TGeoMedium("moduleMedium", 3, new TGeoMaterial(moduleMaterial.GetName(), moduleMaterial.GetA(), moduleMaterial.GetZ(), moduleMaterial.GetDensity()));

    LOG_DEBUG("Display::Build() - chipMedium = %p", chipMedium);
    for(unsigned imodule = 0; imodule < limadou::N_MODULES; imodule++) {

        LOG_DEBUG("Display::Build() - imodule = %d", imodule);
        DetectorModule* module = fGeometry.GetModule(limadou::MODULE_IDS[imodule]);
        LOG_DEBUG("Display::Build() - module = %p", module);
        TGeoVolume* moduleVolume = module->Build(*fGeoManager, *moduleMedium, Form("Module%d", limadou::MODULE_IDS[imodule]));
        fDetectorVolumes.push_back(moduleVolume);
        fDetectorVolumes.back()->SetLineColor(fGeometry.GetModuleColor());
        LOG_DEBUG("Display::Build() - fDetectorVolumes.back() = %p", fDetectorVolumes.back());

        TGeoRotation* rotation = new TGeoRotation(Form("CombiModule%d", limadou::MODULE_IDS[imodule]),
                                                          0, 0, 0); // rotate the chip so that the z-axis is vertical
        TGeoCombiTrans* combi = new TGeoCombiTrans(Form("CombiModule%d", limadou::MODULE_IDS[imodule]), 
                                                           module->GetPosX(), module->GetPosY(), module->GetPosZ(), 
                                                           rotation);
        fWorld->AddNodeOverlap(fDetectorVolumes.back(), 1, combi);
        LOG_DEBUG("Display::Build() - fWorld->GetNode(0) = %p", fWorld->GetNode(0));
        module->Print();    
        
        for(unsigned ix = 0; ix < limadou::N_CHIPS_X; ix++) {
            for(unsigned iy = 0; iy < limadou::N_CHIPS_Y; iy++) {
                
                LOG_DEBUG("Display::Build() - ix = %d, iy = %d", ix, iy);
                DetectorChip* chip = fGeometry.GetChip(limadou::MODULE_IDS[imodule], limadou::CHIP_IDS[ix][iy]);
                LOG_DEBUG("Display::Build() - chip = %p", chip);
                TGeoVolume* chipVolume = chip->Build(*fGeoManager, *chipMedium, Form("Chip%dModule%d", limadou::CHIP_IDS[ix][iy], limadou::MODULE_IDS[imodule]));
                fDetectorVolumes.push_back(chipVolume);  
                fDetectorVolumes.back()->SetLineColor(fGeometry.GetChipColor());
                fDetectorVolumes.back()->Print();
                

                TGeoRotation* rotation = new TGeoRotation(Form("CombiChip%dModule%d", limadou::CHIP_IDS[ix][iy], limadou::MODULE_IDS[imodule]),
                                                          0, 0, 0); // rotate the chip so that the z-axis is vertical
                TGeoCombiTrans* combi = new TGeoCombiTrans(Form("CombiChip%dModule%d", limadou::CHIP_IDS[ix][iy], limadou::MODULE_IDS[imodule]), 
                                                           module->GetPosX() + module->GetChipXPos(ix), module->GetPosY() + module->GetChipYPos(iy), module->GetPosZ() + 0.1 * chip->GetSizeZ(), 
                                                           rotation);
                fWorld->AddNodeOverlap(fDetectorVolumes.back(), 1, combi);
                LOG_DEBUG("Display::Build() - fWorld->GetNode(0) = %p", fWorld->GetNode(0));
            }
        }
        LOG_DEBUG("Display::Build() - before delete module");
    }

    LOG_DEBUG("Display::Build() - before CloseGeometry()");
    gGeoManager->CloseGeometry();
    LOG_DEBUG("Display::Build() - after CloseGeometry()");
    gGeoManager->SetVisLevel(4);
    LOG_DEBUG("Display::Build() - after SetVisLevel()");
    gGeoManager->SetVisOption(0);
    LOG_DEBUG("Display::Build() - after SetVisOption()");
}

void Display::TestBuild() {
    LOG_DEBUG("Display::Build()");

    fDetectorVolumes.clear();
    fDetectorVolumes.reserve(1);
    // Create a test object
    TGeoMedium* Si = new TGeoMedium("Si", 2, new TGeoMaterial("Si", 28.0855, 14, 2.33));
    
    LOG_DEBUG("Display::Build() - Si = %p", Si);
    TGeoVolume* testVolume = nullptr;
    LOG_DEBUG("Display::Build() - testVolume = %p", testVolume);
    testVolume = fGeoManager->MakeBox("TestVolume", Si, 1., .5, 1.);
    LOG_DEBUG("Display::Build() - testVolume = %p", testVolume);
    testVolume->SetLineColor(kRed);

    fDetectorVolumes.push_back(testVolume);
    LOG_DEBUG("Display::Build() - fDetectorVolumes.size() = %zu", fDetectorVolumes.size());

    LOG_DEBUG("Display::Build() - fDetectorVolumes[0] = %p", fDetectorVolumes[0]);
    //fWorld->Print();
    //testVolume->Print();
    

    // Add the test object to the world
    fWorld->AddNodeOverlap(fDetectorVolumes[0], 1, new TGeoTranslation(0, 0, 0));

    // Close the geometry
    fGeoManager->CloseGeometry();
    fGeoManager->SetVisLevel(4);
    fGeoManager->SetVisOption(0);
}

void Display::Run()
{
    LOG_DEBUG("Display::Run()");

    // Check that fWorld is initialized
    if (!fWorld) {
        LOG_ERROR("Display::Run() - fWorld is not initialized");
        return;
    }

    // Add similar checks for other members if necessary...

    TCanvas * monitor = new TCanvas("monitor", "monitor", 1200, 1000);
    this->Build();
    fDetectorVolumes[0]->Print();

    //LOG_DEBUG("Display::Run() - canvas = %p", monitor);
    /*
    TApplication* app = gApplication;
    if (!app) {
        app = new TApplication("app", nullptr, nullptr);
    }

    LOG_DEBUG("Display::Run() - app = %p", app);

    monitor->SetFillColor(kWhite);

    LOG_DEBUG("Display::Run() - before while loop");
  
    while (true) {
        LOG_DEBUG("Display::Run() - in while loop");
        monitor->Clear();
        LOG_DEBUG("Display::Run() - in while loop 2");
    */
    monitor->cd();
    LOG_DEBUG("Display::Run() - in while loop 3");
    if (fWorld) {
        fWorld->Print();
        //fWorld->Draw();
        fWorld->Draw("ogl");
    }
    /*
        LOG_DEBUG("Display::Run() - in while loop 4");
        monitor->Update();
        LOG_DEBUG("Display::Run() - in while loop 5");
        gSystem->ProcessEvents(); // Process pending GUI events
        LOG_DEBUG("Display::Run() - in while loop 6");
        gSystem->Sleep(1e4);
    }

    LOG_DEBUG("Display::Run() - after while loop");

    if (!gApplication) {
        app->Run();
        delete app;
    }
    delete monitor;
    */
}

void Display::RunLive() {
    LOG_ERROR("Display::RunLive() - not implemented yet");
}

void Display::AddChip(const unsigned chipID, const unsigned moduleID) {
  
  
  std::unique_ptr<TGeoMedium> Si = std::make_unique<TGeoMedium>("Si", 1, new TGeoMaterial("Si", 28.0855, 14, 2.33));
  
  auto chipVolume = fGeometry.GetChip(moduleID, chipID)->Build(*fGeoManager, *Si.get(), Form("Chip%dModule%d", chipID, moduleID));

  fDetectorVolumes.push_back(chipVolume);
}