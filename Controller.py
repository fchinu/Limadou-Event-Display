import ROOT
import argparse
import os

BuildFolders = ["Utils/build", "Clustering/build"]

def CompileMacros(**kwargs):

    option = "k"
    if kwargs.get('force', False):
        option += "f"
    if kwargs.get('optimize', False):
        option += "O"
    option += "-"

    if kwargs.get('clean', False):
        for folder in BuildFolders:
            for root, _, files in os.walk(folder):
                for f in files:
                    os.unlink(os.path.join(root, f))
        

    ROOT.gSystem.AddIncludePath("-I" + ROOT.gSystem.GetWorkingDirectory())
    ROOT.gSystem.CompileMacro("Utils/include/fileManager.cxx", option, "", "Utils/build")
    ROOT.gSystem.CompileMacro("Clustering/src/Projections2D.cxx", option, "", "Clustering/build")
    ROOT.gSystem.CompileMacro("Clustering/src/Cluster.cxx", option, "", "Clustering/build")
    ROOT.gSystem.CompileMacro("Clustering/src/clusterer.cxx", option, "", "Clustering/build")

if __name__ == '__main__':
    argparser = argparse.ArgumentParser()
    argparser.add_argument('--force', '-f', help='Force compilation of the macros', default=False, action='store_true')
    argparser.add_argument('--clean', '-c', help='Clean build directories', default=False, action='store_true')
    argparser.add_argument('--optimize', '-o', help='Optimize compilation', default=False, action='store_true')
    args = argparser.parse_args()

    CompileMacros(force=args.force, clean=args.clean, optimize=args.optimize)    

    from ROOT import Clusterer

    c = Clusterer()
    c.Clustering("Clustering/data/input/DummyForTests2.txt")