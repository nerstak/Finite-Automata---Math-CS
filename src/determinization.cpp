#include <algorithm>
#include "determinization.h"

static State*
determinizationProcess_Sync(vector<State*> &presentStates, vector<char> alphabet, vector<State*> sameStates,
                            vector<State*> &init, vector<State*> &fin) {
    // Naming the new state
    string newID;
    newID = concatenateID(sameStates);

    // Checking if the state isn't already existing
    auto search = State::searchById(presentStates, newID);
    if (search != nullptr) {
        return search;
    }

    // Creating the state
    State* actual = new State;
    actual->id = newID;
    actual->initial = sameStates == init;
    actual->final = State::isAnyFinal(sameStates);
    presentStates.push_back(actual);

    // Generating each transition of the alphabet of the new state from states that compose it
    for (auto c: alphabet) {
        vector<State*> sameFinalState;
        for (State* st: sameStates) {
            for (Transition* tr: st->exits) {
                bool isNotPresent = find_if(sameFinalState.begin(), sameFinalState.end(), [tr](const State* s) -> bool {
                    return s == tr->dest;
                }) == sameFinalState.end();
                if (tr->trans == c && isNotPresent) {
                    // We add the element if it is not already on the list and if the transition character correspond
                    sameFinalState.push_back(tr->dest);
                }
            }
        }
        // Creating the transition, with the character and the address of the terminal state
        if (!sameFinalState.empty()) {
            Transition* tr = new Transition;
            tr->trans = c;
            tr->dest = determinizationProcess_Sync(presentStates, alphabet, sameFinalState, init, fin);
            actual->exits.push_back(tr);
        }
    }
    return actual;
}

FA* FA::determinization_Sync() {
    if (_determinized) {
        return this;
    }

    vector<State*> initials, finals, states;

    // Recovering final and initial states
    State::recoverSpecials(_states, initials, finals);

    determinizationProcess_Sync(states, _alphabet, initials, initials, finals);

    // Creating the FA in itself
    FA* determinized = new FA(states, _alphabet);
    determinized->_determinized = true;
    return determinized;
}

FA* FA::determinize() {
    if (_synchronous) {
        return determinization_Sync();
    } else {
        // Should return the pointer of the async determinized
        return nullptr;
    }
}