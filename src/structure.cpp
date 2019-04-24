#include "structure.h"
#include <algorithm>

using namespace std;


FA::FA(std::string FAname) {
    name = FAname;
}

FA::FA() {

}

void FA::display() const {
    int a_size = alphabet.size(), st_size = states.size(), t_size, i, c, j;

    State* curSt;

    cout << endl << " - - - - - - - - - - - - - - - - - - - - - " << endl;
    cout << "          FA: "<< name << endl << endl;
    for (i = 0; i < st_size; i++) {
        //Displays each state ID and if it is I/F
        curSt = states[i];

        cout << "State " << curSt->id << " :";


        t_size = curSt->exits.size();

        if (curSt->initial) {
            cout << " Initial";
        }
        if (curSt->final) {
            cout << " Final";
        }
        cout << endl;
        int a = 0;

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


void FA::addState(int ID) {
    State* St = new State;
    int x, st_size;
    char c, letter;
    Transition* newT = NULL;

    if (ID == -1) {
        cout << "State ID: ";
        cin >> ID;
    }
    St->id = ID;

    cout << "Is state " << St->id << " initial (y/n): ";
    cin >> c;
    St->initial = c == 'y';


    cout << "Is state " << St->id << " final (y/n): ";
    cin >> c;
    St->final = c == 'y';


    states.push_back(St);

    do {
        display();
        cout << "Add another transition from state " << St->id << " ? (y/n)";
        cin >> c;
        if (c == 'y') {
            cout << "Transition Character: ";
            cin >> letter;

            if (find(alphabet.begin(), alphabet.end(), letter) == alphabet.end()) {
                alphabet.push_back(letter);
            }

            cout << "Transition destination state: ";
            cin >> x;


            if (findState(states, x) == NULL) {
                cout << endl << "    This is a new transition, making a new state... " << endl << endl;

                addState(x);
            }

            newT = new Transition;

            newT->trans = letter;
            newT->dest = findState(states, x);


            St->exits.push_back(newT);
            //TODO prevent duplicate transitions
        }
    } while (c == 'y');

}


State* findState(vector<State*> ListStates, int ID) {
    for (State* allstates: ListStates) {
        if (allstates->id == ID) {
            return allstates;
        }
    }
    return NULL;
}