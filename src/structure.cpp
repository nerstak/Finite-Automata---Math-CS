#include <algorithm>
#include "structure.h"

using namespace std;

FA::FA() {
}

FA::FA(FA &toCopy) {
    _alphabet = toCopy._alphabet;
    _synchronous = toCopy._synchronous;
    _minimized = toCopy._minimized;
    _completed = toCopy._completed;

    vector<State*> init, final;
    State::recoverSpecials(toCopy._states, init, final);

    for (State* st: init) {
        copyStatesProcess(toCopy._states, st->id);
    }
}

State* FA::copyStatesProcess(std::vector<State*> &toCopyStates, string newID) {
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
}

void FA::display() const {
    int a_size = _alphabet.size(), st_size = _states.size(), t_size, i, c, j;

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
            cout << "    " << _alphabet[c] << ": ";

            for (j = 0; j < t_size; j++) {
                if (curSt->exits[j]->trans == _alphabet[c]) {
                    cout << curSt->exits[j]->dest->id << " ";

                }

            }
            cout << endl;
        }


        cout << endl;
    }
    cout << " - - - - - - - - - - - - - - - - - - - - - " << endl << endl;
}


void FA::addState(string ID) {
    State* St = new State;
    string
    x;
    char c, letter;
    bool exists;
    Transition* newT = nullptr;



    //Asks for state ID if it wasn't already given
    if (ID == "-1") {
        cout << "State ID: ";
        cin >> ID;
    }
    St->id = ID;

    //sets if the FA is initial or final
    cout << "Is state " << St->id << " initial (y/n): ";
    cin >> c;
    St->initial = c == 'y';


    cout << "Is state " << St->id << " final (y/n): ";
    cin >> c;
    St->final = c == 'y';

    //adds generated state to full list
    _states.push_back(St);

    do {
        //display automata
        display();

        cout << "Add another transition from state " << St->id << " ? (y/n)";
        cin >> c;
        if (c == 'y') {
            cout << "Transition Character: ";
            cin >> letter;

            //tries to find the transition character in the alphabet, if it does not exist, generate it
            if (find(_alphabet.begin(), _alphabet.end(), letter) == _alphabet.end()) {
                _alphabet.push_back(letter);
            }

            cout << "Transition destination state: ";
            cin >> x;

            //Tries to find the destination state, if it does not exist, creates it
            if (State::searchById(_states, x) == nullptr) {
                cout << endl << "    This is a new transition, making a new state... " << endl << endl;
                //recursion <3<3<3<3
                addState(x);
            }

            //creates a Transition and adds it to the list
            newT = new Transition;

            newT->trans = letter;
            newT->dest = State::searchById(_states, x);

            //if the transition already exists, it does not add it
            exists = false;
            for (Transition* exitStates : St->exits) {
                if (exitStates->trans == newT->trans && exitStates->dest == newT->dest) {
                    exists = true;
                    break;
                }
            }

            if (!exists) {
                St->exits.push_back(newT);
            }
        }
    } while (c == 'y');

}

void FA::changeName(string name) {
    _name = name;
}


State* State::searchById(vector<State*> &list, string id) {
    vector<State*>::iterator it;
    it = find_if(list.begin(), list.end(), [&id](State* st) -> bool {
        return st->id == id;
    });
    if (it != list.end()) {
        return *it;
    }
    return nullptr;
}


bool State::isAnyInitial(const vector<State*> &list) {
    for (State* st: list) {
        if (st->initial) {
            return true;
        }
    }
    return false;
}

bool State::isAnyFinal(const vector<State*> &list) {
    for (State* st: list) {
        if (st->final) {
            return true;
        }
    }
    return false;
}

extern string concatenateID(vector<State*> &sameStates) {
    sort(sameStates.begin(), sameStates.end(),
         [](const State* st1, const State* st2) -> bool { return stoi(st1->id) < stoi(st2->id); });
    string newID;
    for (State* st: sameStates) {
        newID += st->id;
    }
    return newID;
}

void State::recoverSpecials(const vector<State*> &list, vector<State*> &initials, vector<State*> &finals) {
    for (State* st: list) {
        if (st->initial) {
            initials.push_back(st);
        }
        if (st->final) {
            finals.push_back(st);
        }
    }
}

bool FA::isSynchronous() const {
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