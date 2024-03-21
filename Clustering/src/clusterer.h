#pragma once

#include <vector>
#include "../include/cluster.h"

class Clusterer
{

    public:
        Clusterer();
        ~Clusterer();

        void Clustering(const char * inputFile);
        
    protected: 

        void clearClusters() {fClusters.clear();};

    private:

    std::vector<Cluster> fClusters;


    

};