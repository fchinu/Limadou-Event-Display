import numpy as np

import sys
sys.path.append('..')

import ROOT 
#ROOT.PyConfig.GUIThreadScheduleOnce += [ lambda : 1 ]

ROOT.gInterpreter.ProcessLine('#include "../src/DetectorChip.cxx"') 
from src.DetectorModuleWrapper import DetectorModule
ROOT.gInterpreter.ProcessLine('#include "../src/Detector.cxx"')

from ROOT import DetectorChip, Detector

    

if __name__ == '__main__' :

    nPixelsX = 1024 
    nPixelsY = 512 
    pxSizeX = 0.002924 #cm 
    pxSizeY = 0.002688 #cm

    nChipsX = 5 
    nChipsY = 2 
    chipGapX = 0.0150 #cm 
    chipGapY = 0.0150 #cm

    chipIDs = np.array([[0, 1, 2, 3, 4], [5, 6, 7, 8, 9]], dtype = np.uintc)
    sizeZ = 0.05 #cm

    nModules = 3
    moduleDisalignmentX = 0.       # cm
    moduleDisalignmentY = 0.       # cm
    modulePosZ = np.array([0., 0.85, 1.7], dtype=np.double)      # cm
    moduleIDs = np.array([0, 1, 2], dtype=np.uintc)

    chip = DetectorChip(1, nPixelsX, nPixelsY, pxSizeX, pxSizeY, sizeZ)
    #chip.Show()
    module = DetectorModule()
    module.init([nChipsX, nChipsY])(0, chipGapX, chipGapY, sizeZ, chip, chipIDs) 
    #module.Show()
    detector = Detector(nModules, moduleDisalignmentX, moduleDisalignmentY, modulePosZ, module, moduleIDs)
    detector.Show()
    input('Press Enter to continue...')