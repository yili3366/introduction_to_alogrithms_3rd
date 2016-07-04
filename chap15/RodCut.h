//
// Created by yijun on 6/30/16.
//

#ifndef CHAP15_CUTROD_H
#define CHAP15_CUTROD_H

struct RodCutInfo{
    int r;
    int s;
};

class RodCut {
public:
    int CutRod(int p[], int n);
    int MemorizedCutRod(int p[], int n);
    int MemorizedCutRodAux(int p[], int n, int r[]);
    int BottomUpCutRod(int p[], int n);
    std::vector<RodCutInfo> ExtendedBottomUpCutRod(int p[], int n);
    void PrintCutRodSolution(int p[], int n);
};

#endif //CHAP15_CUTROD_H
