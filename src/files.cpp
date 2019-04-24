#include <fstream>
#include <algorithm>
#include "files.h"

using namespace std;

extern FA* readFile(string &nameFile) {
    ifstream inputStream(nameFile);

    if (!inputStream) {
        return nullptr;
    }

    FA* result = creatingFA(inputStream);

    inputStream.close();
    return result;
}

static FA* creatingFA(ifstream &stream) {
    string line;
    int alphabetSize{0}, numberStates{0}, numberTransitions{0};
    vector<int>* initStates, * finalStates;
    vector<State*> statesList;
    vector<char> alphabet;

    alphabetSize = readUniqueNumber(stream);
    numberStates = readUniqueNumber(stream);
    initStates = readSpecialStates(stream);
    finalStates = readSpecialStates(stream);
    numberTransitions = readUniqueNumber(stream);

    createStates(stream, initStates, finalStates, statesList, alphabet);

    FA* newFA = new FA(statesList, alphabet);

    delete (initStates);
    delete (finalStates);

    // TODO: Add security and all that kind of stuff

    return newFA;
}

static vector<int>* readSpecialStates(ifstream &stream) {
    vector<int>* states = new vector<int>;
    string line, newState, delimiter = " ";
    int size{-1};
    size_t pos = 0;
    getline(stream, line);

    // Splitting instruction with ' '
    while ((pos = line.find(delimiter)) != string::npos) {
        newState = line.substr(0, pos);
        if (states->empty() && size == -1) {
            // First number is for the size
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

static void createStates(ifstream &stream, vector<int>* initialStates, vector<int>* finalStates, vector<State*> &states,
                         vector<char> &alpha) {
    string line;
    while (getline(stream, line)) {
        char c;
        int stateFrom, stateTo;
        // Splitting the instruction into 3 parts
        separateTransition(line, c, stateFrom, stateTo);

        // Recovering or creating states of the transition
        checkAndCreateSingleState(states, stateFrom, initialStates, finalStates);
        checkAndCreateSingleState(states, stateTo, initialStates, finalStates);

        createTransition(states, stateFrom, stateTo, c);

        addCharacterToAlphabet(alpha, c);
    }
}

static void checkAndCreateSingleState(vector<State*> &list, int state, vector<int>* init, vector<int>* final) {
    auto it = State::searchById(&list, state);

    if (it == list.end()) {
        list.push_back(allocateState(state));

        // Checking if the created state is special
        if (find(init->begin(), init->end(), state) != init->end()) {
            list.back()->initial = true;
        }
        if (find(final->begin(), final->end(), state) != final->end()) {
            list.back()->final = true;
        }
    }
}

static State* allocateState(int c) {
    State* st = new State();
    st->id = c;
    return st;
}

static void separateTransition(string &transitionString, char &c, int &stateFrom, int &stateTo) {
    string::iterator it = transitionString.begin();
    string stateF, stateT;

    // First state
    while (isdigit(*it)) {
        stateF += *it;
        it++;
    }
    // Character of transition
    while (isalpha(*it) || *it == EMPTY) {
        c = *it;
        it++;
    }
    // Second state
    while (isdigit(*it)) {
        stateT += *it;
        it++;
    }
    stateFrom = stoi(stateF);
    stateTo = stoi(stateT);
}

static void createTransition(vector<State*> &list, const int stateFromID, const int stateToID, const char transition) {
    // Looking for address of the two states
    State* stateFrom = *State::searchById(&list, stateFromID);
    State* stateTo = *State::searchById(&list, stateToID);

    Transition* t = new Transition;
    t->trans = transition;
    t->dest = stateTo;
    stateFrom->exits.push_back(t);
}

static void addCharacterToAlphabet(vector<char> &alpha, char c) {
    // We add character to alphabet if not in or empty word
    if (find(alpha.begin(), alpha.end(), c) == alpha.end() && c != EMPTY) {
        alpha.push_back(c);
    }
}