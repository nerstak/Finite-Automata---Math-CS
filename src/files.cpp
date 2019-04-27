#include <fstream>
#include <algorithm>
#include "files.h"

using namespace std;

FA::FA(string nameFile) {
    ifstream inputStream(nameFile);

    if (inputStream) {
        creatingFAFile(inputStream);

        checkSynchronous();

        inputStream.close();
    }


}

void FA::creatingFAFile(ifstream &stream) {
    string line;
    int alphabetSize{0}, numberStates{0}, numberTransitions{0};
    vector<string>* initStates, * finalStates;

    alphabetSize = readUniqueNumber(stream);
    numberStates = readUniqueNumber(stream);
    initStates = readSpecialStates(stream);
    finalStates = readSpecialStates(stream);
    numberTransitions = readUniqueNumber(stream);

    createStates(stream, initStates, finalStates, _states, _alphabet);

    bool alphaNB = alphabetSize == _alphabet.size();
    bool numberST = numberStates == _states.size();
    bool numberTR = countTransitions(_states) == numberTransitions;

    delete (initStates);
    delete (finalStates);

    if (!(alphaNB && numberST && numberTR)) {
        _states.clear();
        _alphabet.clear();
    }
}

static vector<string>* readSpecialStates(ifstream &stream) {
    vector<string>* states = new vector<string>;
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
        } else if (newState != delimiter && newState != "") {
            states->push_back(newState);
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

static void createStates(ifstream &stream, vector<string>* initialStates, vector<string>* finalStates,
                         vector<State*> &states,
                         vector<char> &alpha) {
    string line;
    while (getline(stream, line)) {
        char c;
        string stateFrom, stateTo;
        // Splitting the instruction into 3 parts
        separateTransition(line, c, stateFrom, stateTo);

        // Recovering or creating states of the transition
        checkAndCreateSingleState(states, stateFrom, initialStates, finalStates);
        checkAndCreateSingleState(states, stateTo, initialStates, finalStates);

        createTransition(states, stateFrom, stateTo, c);

        addCharacterToAlphabet(alpha, c);
    }
}

static void checkAndCreateSingleState(vector<State*> &list, string state, vector<string>* init, vector<string>* final) {
    auto it = State::searchById(list, state);

    if (it == nullptr) {
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

static State* allocateState(string id) {
    State* st = new State();
    st->id = id;
    return st;
}

static void separateTransition(string &transitionString, char &c, string &stateFrom, string &stateTo) {
    string::iterator it = transitionString.begin();
    string stateF, stateT;

    // First state
    while (isdigit(*it)) {
        stateFrom += *it;
        it++;
    }
    // Character of transition
    while (isalpha(*it) || *it == EMPTY) {
        c = *it;
        it++;
    }
    // Second state
    while (isdigit(*it)) {
        stateTo += *it;
        it++;
    }
}

static void createTransition(vector<State*> &list, const string stateFromID, const string stateToID,
                             const char transition) {
    // Looking for address of the two states
    State* stateFrom = State::searchById(list, stateFromID);
    State* stateTo = State::searchById(list, stateToID);

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

static int countTransitions(vector<State*> &list) {
    int count{0};
    for_each(list.begin(), list.end(), [&count](State* st) -> void { count += st->exits.size(); });
    return count;
}