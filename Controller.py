import ROOT
ROOT.gInterpreter.ProcessLine('#include "Clustering/src/clusterer.cxx"')
ROOT.gInterpreter.ProcessLine('#include "Utils/include/fileManager.cxx"')

from ROOT import Clusterer

if __name__ == '__main__':
    c = Clusterer()
    c.Clustering("Clustering/data/input/DummyForTests1.txt")