#include "minimization.h"

using namespace std;

FA* FA::minimize() {
    auto* Partitions = new vector<vector<State*> >;
    vector<State*> Final, NonFinal;

    for (State* St: _states) {
        if (St->final) {
            Final.push_back(St);
        } else {
            NonFinal.push_back(St);
        }
    }

    Partitions->push_back(Final);
    Partitions->push_back(NonFinal);

    Partitions = partitioning(Partitions);

    return Partition2FA(Partitions);
}


static vector<vector<State*> > * partitioning(vector< vector<State*> > * P)
{

}

static FA * Partition2FA(vector< vector<State*> > * P)
{

}