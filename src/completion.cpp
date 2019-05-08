//
// Created by gmaza on 03/05/2019.
//
#include <algorithm>
#include "Transition.h"
#include <vector>
#include <evntprov.h>
#include "completion.h"
#include "FA.h"


void static completionProcess(vector<State*> &list, const vector<char> &alphabet){
    State *P = new State;
    P->id = "P";
    P->initial = false;
    P->final = false;
    bool isPUsed = false;
    for (State *st: list) {
        for (char c : alphabet) {
            vector <Transition*> t;
            Transition T;
            if (Transition::searchByCharacter(st->exits,c) == nullptr) {
                T.dest = P;
                T.trans = c;
                st->exits.push_back(T);
                isPUsed = true;
            }
        }
    }
    if (isPUsed == false) {
        delete P;
    } else {
        list.push_back(P);
    }
}

