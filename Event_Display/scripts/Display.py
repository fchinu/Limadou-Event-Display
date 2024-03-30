#DOES NOT WORK

import numpy as np

import ROOT 
ROOT.gInterpreter.ProcessLine('#include "../src/DetectorChip.cxx"') 
ROOT.gInterpreter.ProcessLine('#include "../src/DetectorModule.cxx"')

from ROOT import DetectorChip, DetectorModule

if __name__ == '__main__' :

    nPixelsX = 1024 
    nPixelsY = 512 
    pxSizeX = 0.002924 #cm 
    pxSizeY = 0.002688 #cm

    nChipsX = 5 
    nChipsY = 2 
    chipGapX = 0.0150 #cm 
    chipGapY = 0.0150 #cm

    chipIDs = np.array([[0, 1, 2, 3, 4], [5, 6, 7, 8, 9]], dtype = int)
    sizeZ = 0.05 #cm

    chip = DetectorChip(1, nPixelsX, nPixelsY, pxSizeX, pxSizeY, sizeZ)
    #chip.Show()
    module = DetectorModule(0, nChipsX, nChipsY, chipGapX, chipGapY, sizeZ, chip, chipIDs) 
    module.Show()