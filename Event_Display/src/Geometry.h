#pragma once

#include <stdint.h>

#include <TGeoMaterial.h>

#include "../include/LimadouConstants.h"
#include "../include/Materials.h"
#include "DetectorChip.h"
#include "DetectorModule.h"

/**
 * Class to represent the geometry of the Limadou detector
*/
class Geometry {

public: 

    Geometry();
    Geometry(const Geometry&);
    ~Geometry();

    void Print() const;

    DetectorChip* GetChip(const unsigned moduleID, const unsigned chipID) const;
    DetectorModule* GetModule(const unsigned moduleID) const;
    
    std::array<std::array<std::array<DetectorChip*, limadou::N_PIXELS_X>, limadou::N_PIXELS_Y>, limadou::N_MODULES> GetChips() const { return fChips; }
    std::array<DetectorModule*, limadou::N_MODULES> GetModules() const { return fModules; }

    Silicon GetChipMaterial() const { return Silicon(); }
    Carbon GetModuleMaterial() const { return Carbon(); }

    int GetChipColor() const { return kOrange - 5; }
    int GetModuleColor() const { return kGray + 3; }

private:

    std::array<std::array<std::array<DetectorChip*, limadou::N_PIXELS_X>, limadou::N_PIXELS_Y>, limadou::N_MODULES> fChips;
    std::array<DetectorModule*, limadou::N_MODULES> fModules;
};