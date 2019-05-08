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
    State *P = new State; //Declaration of a new state "P"
    P->id = "P";
    P->initial = false; //As P is neither an initial or a final state in the automaton
    P->final = false;
    bool isPUsed = false; //Declaration of "isPUsed" that will check if the state "P" has been used in this process.
    for (State *st: list) {
        for (char c : alphabet) {
            //Checking all alphabet for each state, to see if there are empty transitions. If yes, adds P as a transition.
            Transition T;
            if (Transition::searchByCharacter(st->exits,c) == nullptr) {
                T.dest = P;
                T.trans = c;
                st->exits.push_back(T);
                isPUsed = true; //As P has been used in this process
            }
        }
    }
    if (isPUsed == false) {
        delete P; //If P has not been used, we don't need it, so it is deleted
    } else {
        list.push_back(P); //Adds P to the list of states
    }
}

