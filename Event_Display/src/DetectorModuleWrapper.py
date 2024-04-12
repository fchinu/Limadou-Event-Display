import ROOT 
ROOT.gInterpreter.ProcessLine('#include "../src/DetectorModule.cxx"')

class DetectorModule(ROOT.DetectorModule):
    def __init__(self):
        ROOT.DetectorModule.__init__(self)

    def init(self, nChips):
        def initTemplate(moduleID, chipGapX, chipGapY, sizeZ, chip, chipIDs):
            ROOT.DetectorModule.Init[nChips[0], nChips[1]](self, moduleID, chipGapX, chipGapY, sizeZ, chip, chipIDs) 
        return initTemplate