#include <TSystem.h>

#include "../src/Detector.h"
#include "../src/DetectorChip.h"
#include "../src/DetectorModule.h"
// #include "../include/DetectorChip.h"
// #include "../include/DetectorModule.h"

#pragma once

void LoadMacros() {
  gSystem->AddIncludePath(
      (std::string("-I ") + gSystem->GetWorkingDirectory() + "../build")
          .c_str());
  gSystem->CompileMacro("../src/DetectorChip.cxx", "kg", "", "../build");
  gSystem->CompileMacro("../src/DetectorModule.cxx", "kg", "", "../build");
  gSystem->CompileMacro("../src/Detector.cxx", "kg", "", "../build");
}