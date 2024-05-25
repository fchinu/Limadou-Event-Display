#include <Riostream.h>
#include <TSystem.h>

#include "../include/LimadouConstants.h"
#include "../include/Logger.h"

#include "../src/DetectorChip.h"
#include "../src/DetectorModule.h"
#include "../src/Geometry.h"
#include "../src/Display.h"

void LimadouApp() {
    
    std::cout << "App()" << std::endl;
    Geometry geometry;
    LOG_DEBUG("App() - Geometry created");
    //Display display(geometry, 10., 10., 10.);
    LOG_DEBUG("App() - Display created");
    //display.Run();
    LOG_DEBUG("App() - Display run");
}