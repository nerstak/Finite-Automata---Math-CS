#include <algorithm>
#include "structure.h"

using namespace std;


FA::FA(std::string FAname) {
    _name = FAname;
}

FA::FA() {
    _name = "Finite Automata";
}

FA::FA(vector<State*> &states, vector<char> &alphabet) {
    _states = states;
    _alphabet = alphabet;
    _name = "Finite Automata (from file)";

}

void FA::display() const {
    cout << _alphabet[0];
    int a_size = _alphabet.size(), t_size, i, c, j;

    for (i = 0; i < _states.size(); i++) {
        //Displays each state ID and if it is I/F
        cout << "State " << _states[i]->id << " :";

        if (_states[i]->initial) {
            cout << " Initial";
        }
        if (_states[i]->final) {
            cout << " Final";
        }
        cout << endl;


        //Displays the transitions of a state from each letter in the _alphabet
        for (c = 0; c < a_size; c++) {
            cout << "    Char " << _alphabet[c] << ": ";

            t_size = _states[i]->exits.size();
            for (j = 0; j < t_size; j++) {
                if (_states[i]->exits[j]->trans == _alphabet[c]) {
                    cout << _states[i]->exits[j]->dest->id << " ";  //TODO: yeah I'll make it clearer
                }

            }
            cout << endl;
        }


        cout << endl;
    }
}


void FA::addState() {
    State* St = new State;
    char c;

    cout << "State ID: ";
    cin >> St->id;

    cout << "Is state final (y/n): ";
    cin >> c;
    St->final = c == 'y';

    cout << "Is state initial (y/n): ";
    cin >> c;
    St->initial = c == 'y';

    //TODO add trransitions


}

void FA::changeName(string name) {
    _name = name;
}

vector<State*>::iterator State::searchById(vector<State*>* list, int id) {
    vector<State*>::iterator it;
    it = find_if(list->begin(), list->end(), [&id](State* st) -> bool {
        return st->id == id;
    });
    return it;
}