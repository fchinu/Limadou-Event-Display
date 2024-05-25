#include <TSystem.h>

#include "../src/DetectorChip.h"
#include "../src/DetectorModule.h"
#include "../src/Geometry.h"
#include "../src/Display.h"

#pragma once

void LoadMacros() {
  gSystem->AddIncludePath(
      (std::string("-I ") + gSystem->GetWorkingDirectory() + "../build")
          .c_str());
  gSystem->CompileMacro("../src/DetectorChip.cxx", "kg", "", "../build");
  gSystem->CompileMacro("../src/DetectorModule.cxx", "kg", "", "../build");
  gSystem->CompileMacro("../src/Geometry.cxx", "kg", "", "../build");
  gSystem->CompileMacro("../src/Display.cxx", "kg", "", "../build");
  
}