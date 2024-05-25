#include <Riostream.h>

#include "../include/Logger.h"
#include "Geometry.h"
#include "DetectorChip.h"

Geometry::Geometry() {

    std::cout << "Geometry::Geometry()" << std::endl;
    // z offset of the modules
    double zOffsetModule = 0.;
    for (unsigned iz = 0; iz < limadou::N_MODULES; iz++) {
        zOffsetModule -= limadou::MODULE_POS_Z[iz] / 2.;
    }

    // dummy chip: used to create the first module
    std::unique_ptr<DetectorChip> dummyChip = std::make_unique<DetectorChip>(0, limadou::N_PIXELS_X, limadou::N_PIXELS_Y, limadou::PX_SIZE_X, limadou::PX_SIZE_Y, limadou::SIZE_Z);
    //DetectorChip* dummyChip = new DetectorChip(0, limadou::N_PIXELS_X, limadou::N_PIXELS_Y, limadou::PX_SIZE_X, limadou::PX_SIZE_Y, limadou::SIZE_Z);

    // create the detector chips
    for (unsigned imodule = 0; imodule < limadou::N_MODULES; imodule++) {


        fModules[imodule] = new DetectorModule(limadou::MODULE_IDS[imodule],
                                               limadou::CHIP_GAP_X, limadou::CHIP_GAP_Y,
                                               limadou::SIZE_Z, *dummyChip, 
                                               limadou::CHIP_IDS);
        
        fModules[imodule]->SetPosition(0., 0., zOffsetModule + limadou::MODULE_POS_Z[imodule]);

        fChips[imodule] = std::array<std::array<DetectorChip*, limadou::N_PIXELS_X>, limadou::N_PIXELS_Y>();
        
        for (unsigned ix = 0; ix < limadou::N_CHIPS_X; ix++) {
            for (unsigned iy = 0; iy < limadou::N_CHIPS_Y; iy++) {
        
                fChips[imodule][ix][iy] = new DetectorChip(limadou::CHIP_IDS[ix][iy], limadou::N_PIXELS_X, 
                                                            limadou::N_PIXELS_Y, limadou::PX_SIZE_X, limadou::PX_SIZE_Y, limadou::SIZE_Z);
                fChips[imodule][ix][iy]->SetPosition(fModules[imodule]->GetChipXPos(ix),
                                                     fModules[imodule]->GetChipYPos(iy),
                                                     fModules[imodule]->GetPosZ() + 0.1 * limadou::SIZE_Z);
            }
        }
    }

}

Geometry::Geometry(const Geometry& geometry) {
    for (unsigned imodule = 0; imodule < limadou::N_MODULES; imodule++) {
        fModules[imodule] = new DetectorModule(*geometry.fModules[imodule]);
        for (unsigned ix = 0; ix < limadou::N_CHIPS_X; ix++) {
            for (unsigned iy = 0; iy < limadou::N_CHIPS_Y; iy++) {
                fChips[imodule][ix][iy] = new DetectorChip(*geometry.fChips[imodule][ix][iy]);
            }
        }
    }
}

Geometry::~Geometry() {
    for (unsigned imodule = 0; imodule < limadou::N_MODULES; imodule++) {
        delete fModules[imodule];
        for (unsigned ix = 0; ix < limadou::N_CHIPS_X; ix++) {
            for (unsigned iy = 0; iy < limadou::N_CHIPS_Y; iy++) {
                delete fChips[imodule][ix][iy];
            }
        }
    }
}

void Geometry::Print() const {
    for (unsigned imodule = 0; imodule < limadou::N_MODULES; imodule++) {
        fModules[imodule]->Print();
        for (unsigned ix = 0; ix < limadou::N_CHIPS_X; ix++) {
            for (unsigned iy = 0; iy < limadou::N_CHIPS_Y; iy++) {
                fChips[imodule][ix][iy]->Print();
            }
        }
    }
}

DetectorChip* Geometry::GetChip(const unsigned moduleID, const unsigned chipID) const {

    // get  the chip position in the module
    std::pair<unsigned, unsigned> chipIndex;
    if (limadou::CHIP_IDS_MAP.count(chipID)) {
        chipIndex = limadou::CHIP_IDS_MAP[chipID];
    } else {
        LOG_ERROR("chipID not found in the map");
        return nullptr;
    }
    
    // get the chip from the module
    if (limadou::MODULE_IDS_MAP.count(moduleID)) {
        return fChips[limadou::MODULE_IDS_MAP[moduleID]][chipIndex.first][chipIndex.second];
    } else {
        LOG_ERROR("moduleID not found in the map");
        return nullptr;
    }
}

DetectorModule* Geometry::GetModule(const unsigned moduleID) const {
    
    // get the module position from the module ID
    if (limadou::MODULE_IDS_MAP.count(moduleID)) {
        return fModules[limadou::MODULE_IDS_MAP[moduleID]];
    } else {
        LOG_ERROR("moduleID not found in the map");
        return nullptr;
    }

}