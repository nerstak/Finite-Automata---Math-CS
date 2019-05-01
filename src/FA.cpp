#include <algorithm>
#include "FA.h"

using namespace std;

FA::FA() {
}

FA::FA(FA &toCopy) {
    _alphabet = toCopy._alphabet;
    _synchronous = toCopy._synchronous;
    _minimized = toCopy._minimized;
    _completed = toCopy._completed;
    _determinized = toCopy._determinized;

    vector<State*> init, final;
    State::recoverSpecials(toCopy._states, init, final);

    for (State* st: init) {
        copyStatesProcess(toCopy._states, st->id);
    }
}

State* FA::copyStatesProcess(std::vector<State*> &toCopyStates, const string &newID) {
    // Checking if the state isn't already existing
    auto search = State::searchById(_states, newID);
    if (search != nullptr) {
        return search;
    }

    auto old = State::searchById(toCopyStates, newID);
    // Creating the state
    State* actual = new State;
    actual->id = newID;
    actual->initial = old->initial;
    actual->final = old->final;
    _states.push_back(actual);

    for (Transition* t: old->exits) {
        Transition* tr = new Transition;
        tr->trans = t->trans;
        tr->dest = copyStatesProcess(toCopyStates, t->dest->id);
        actual->exits.push_back(tr);
    }
    return actual;
}

FA::FA(vector<State*> &states, vector<char> &alphabet) {
    _states = states;
    _alphabet = alphabet;
    _name = "Finite Automata (from file)";
    runTest();
}

FA::~FA() {
    for (State* st: _states) {
        for (Transition* t: st->exits) {
            delete (t);
        }
        delete (st);
    }
}

void FA::display() const {
    vector<char> alphabet = _alphabet;
    if (!_synchronous) {
        alphabet.push_back(EMPTY);
    }

    int a_size = alphabet.size(), st_size = _states.size(), t_size, i, c, j;

    State* curSt;

    cout << endl << " - - - - - - - - - - - - - - - - - - - - - " << endl;
    cout << "          FA: " << _name << endl << endl;
    for (i = 0; i < st_size; i++) {
        //Displays each state ID and if it is I/F
        curSt = _states[i];

        cout << "State " << curSt->id << " :";


        t_size = curSt->exits.size();

        if (curSt->initial) {
            cout << " Initial";
        }
        if (curSt->final) {
            cout << " Final";
        }
        cout << endl;

        //Displays the transitions of a state from each letter in the alphabet
        for (c = 0; c < a_size; c++) {
            cout << "    " << alphabet[c] << ": ";

            for (j = 0; j < t_size; j++) {
                if (curSt->exits[j]->trans == alphabet[c]) {
                    cout << curSt->exits[j]->dest->id << " ";

                }
            }
            cout << endl;
        }

        cout << endl;
    }
    cout << " - - - - - - - - - - - - - - - - - - - - - " << endl << endl;
}



void FA::changeName(const string &name) {
    _name = name;
}



extern string concatenateID(vector<State*> sameStates) {
    sort(sameStates.begin(), sameStates.end(),
         [](const State* st1, const State* st2) -> bool { return stoi(st1->id) < stoi(st2->id); });
    string newID;
    for (State* st: sameStates) {
        if (!newID.empty()) { newID += "."; }
        newID += st->id;
    }
    return newID;
}


bool FA::isSynchronous(const bool display = false) const {
    if (display) {
        cout << "Is Automate Synchronous? " << boolalpha << _synchronous << endl;
        if (!_synchronous) {
            for (State* st: _states) {
                // Searching empty closures
                vector<Transition*> emptyClosure;
                Transition::searchOccurrence(st->exits, EMPTY, emptyClosure);

                if (!emptyClosure.empty()) {
                    cout << "At state " << st->id << ", transition EMPTY to: ";
                    for (Transition* tr: emptyClosure) {
                        cout << tr->dest->id << " ";
                    }
                    cout << endl;
                }
            }
        }
    }
    return _synchronous;
}

void FA::checkSynchronous() {
    bool sync = true;
    for (State* st: _states) {
        for (Transition* tr: st->exits) {
            if (tr->trans == EMPTY) {
                sync = false;
                // Note: We use a goto to escape the loop as soon as we found an Empty Closure, which is enough to qualify the FA of asynchronous
                goto exit;
            }
        }
    }
    exit:
    _synchronous = sync;
}

static void oneEntry(const vector<State*> &list) {
    vector<State*> init, fin;
    State::recoverSpecials(list, init, fin);
    if (init.size() > 1) {
        cout << "More than one entry: ";
        for (State* st: init) {
            cout << st->id << " ";
        }
        cout << endl;
    }
}

static void uniqueTransition(const vector<State*> &list, vector<char> alphabet) {
    alphabet.push_back(EMPTY);
    for (State* st: list) {
        bool displayID = false;
        for (char c: alphabet) {
            vector<Transition*> sameCharacter;
            Transition::searchOccurrence(st->exits, c, sameCharacter);
            if (sameCharacter.size() > 1) {
                if (!displayID) {
                    cout << "At state " << st->id << ", same character of transition for:" << endl;
                }
                displayID = true;
                cout << "- Character " << c << ", leading to: ";
                for (Transition* tr: sameCharacter) {
                    cout << tr->dest->id << " ";
                }
                cout << endl;
            }
        }
        if (displayID) {
            cout << endl;
        }
    }
}

bool FA::isDeterministic(const bool display = false) const {
    if (display) {
        cout << "Is Automate Deterministic? " << boolalpha << _determinized << endl;
        if (!_determinized) {
            if (!_synchronous) {
                cout << "Automate is not Synchronous" << endl;
            }

            // Checking if there is only one entry
            oneEntry(_states);

            // Checking if every transition is unique for each state
            uniqueTransition(_states, _alphabet);
        }
    }
    return _determinized;
}

void FA::checkDeterministic() {
    bool det = false;
    if (_synchronous) {
        // Checking the number of initial states
        vector<State*> init, fin;
        State::recoverSpecials(_states, init, fin);
        if (init.size() > 1) {
            goto exit;
        }

        // Checking that every transition is unique
        for (State* st: _states) {
            for (char c: _alphabet) {
                vector<Transition*> occurrences;
                Transition::searchOccurrence(st->exits, c, occurrences);
                if (occurrences.size() > 1) {
                    goto exit;
                }
            }
        }
        det = true;
    }
    exit:
    _determinized = det;
}

void FA::runTest() {
    checkSynchronous();
    checkDeterministic();
}