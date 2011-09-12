#ifndef DSL_PC_H
#define DSL_PC_H

// {{SMILE_PUBLIC_HEADER}}

#include <vector>

class DSL_dataset;
class DSL_learnProgress;
class DSL_network;
class DSL_pattern;
class DSL_cormat;

class DSL_pc
{
public:
    DSL_pc()
    {
        maxAdjacency = 8;
        maxSearchTime = 0;
        significance = 0.05;
    }
    
    int maxAdjacency;
    int maxSearchTime;
    double significance;
    
    typedef std::vector<std::pair<int, int> > IntPairVector;
    IntPairVector forcedArcs;
    IntPairVector forbiddenArcs;
    IntPairVector tiers;
    
    int Learn(const DSL_dataset &ds, DSL_pattern &pat, DSL_learnProgress *progress = NULL) const;
    
    // not for public use
    int Dbcml(const DSL_dataset &ds, int maxDeriv, std::vector<std::vector<int> > &derivs, DSL_pattern &pat, DSL_dataset *dsderivs, DSL_learnProgress *progress) const;
    int DbcmlPc(DSL_cormat &cm, DSL_pattern &pat, std::vector<std::vector<std::vector<int> > > &sepsets) const;
    int Idx(int nvar, int var, int deriv, int time) const;
    std::vector<int> nc;
};

#endif
