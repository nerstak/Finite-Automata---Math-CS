#ifndef FINITE_AUTOMATA_MATH_CS_MINIMIZATION_H
#define FINITE_AUTOMATA_MATH_CS_MINIMIZATION_H

#include "FA.h"

typedef struct PatternGroup
{
    vector<State*> group;
    vector<int> pattern;
} PatternGroup;

typedef vector<PatternGroup>* Partition;


static Partition partitioning(Partition P, vector<char> alphabet);

static vector<State*>* Partition2States(Partition P, vector<char> &alphabet);

static vector<int>* getPattern(Partition source, vector<Transition*> &exits, vector<char> alphabet);

static bool isSamePattern(vector<int> &p1, vector<int> &p2);


#endif //FINITE_AUTOMATA_MATH_CS_MINIMIZATION_H
