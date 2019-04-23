#include <fstream>
#include <algorithm>
#include "files.h"

using namespace std;

extern FA* readFile(string &nameFile) {
    ifstream inputStream(nameFile);

    if (!inputStream) {
        return nullptr;
    }

    creatingFA(inputStream);

    inputStream.close();
}

static FA* creatingFA(ifstream &stream) {
    string line;
    int alphabetSize{0}, numberStates{0}, numberTransitions{0};
    vector<int>* initStates, * finalStates;
    vector<State*>* statesList;

    alphabetSize = readUniqueNumber(stream);
    numberStates = readUniqueNumber(stream);
    initStates = readSpecialStates(stream);
    finalStates = readSpecialStates(stream);
    numberTransitions = readUniqueNumber(stream);

    createStates(stream);

}

static vector<int>* readSpecialStates(ifstream &stream) {
    vector<int>* states = new vector<int>;
    string line, newState, delimiter = " ";
    int size{0};
    size_t pos = 0;
    getline(stream, line);

    while ((pos = line.find(delimiter)) != string::npos) {
        newState = line.substr(0, pos);
        if (states->empty() && size == 0) {
            size = stoi(newState);
        } else {
            states->push_back(stoi(newState));
        }
        line.erase(0, pos + delimiter.length());
    }

    if (states->size() != size) {
        return nullptr;
    }
    return states;
}

static int readUniqueNumber(ifstream &stream) {
    string line;
    getline(stream, line);
    return stoi(line);
}

static vector<State*>* createStates(ifstream &stream) {
    string line;
    vector<State*>* states = new vector<State*>;
    while (getline(stream, line)) {
        checkAndCreateSingleState(states, line[0]);
        checkAndCreateSingleState(states, line[2]);
        // Todo: createTransition(), createFA(), addCharacterToAlphabet
    }
}

static void checkAndCreateSingleState(vector<State*>* list, char state) {
    vector<State*>::iterator it;
    it = find_if(list->begin(), list->end(), [&state](State* st) -> bool {
        return st->id == (int) state - 48;
    });

    if (it == list->end()) {
        list->push_back(allocateState(state));
    }


}

static State* allocateState(char c) {
    State* st = new State();
    st->id = (int) c - 48;
    return st;
}