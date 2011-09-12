#ifndef DSL_FCI_H
#define DSL_FCI_H

// {{SMILE_PUBLIC_HEADER}}

#include <vector>

class DSL_dataset;
class DSL_learnProgress;
class DSL_network;
class DSL_pattern;

class DSL_fci
{
public:
    DSL_fci()
    {
        maxAdjacency = 8;
        maxSearchTime = 0;
        significance = 0.05;
    }
    
    int maxAdjacency;
    int maxSearchTime;
    double significance;
    
    //typedef std::vector<std::pair<int, int> > IntPairVector;
    //IntPairVector forcedArcs;
    //IntPairVector forbiddenArcs;
    //IntPairVector tiers;
    
    int Learn(const DSL_dataset &ds, DSL_pattern &pat, DSL_learnProgress *progress = NULL) const;
};

#endif
