#ifndef FINITE_AUTOMATA_MATH_CS_STRUCTURE_H
#define FINITE_AUTOMATA_MATH_CS_STRUCTURE_H

#include <iostream>
#include <vector>

#define EMPTY '*'

using namespace std;

// Outgoing transition from a State
typedef struct Transition {
    struct State* dest;
    char trans;
} Transition;

//Single automata State
typedef struct State {
    int id;       //Arbitrary state name          make this char?
    bool initial = false;   // true if this is an initial state
    bool final = false;     // true if this is a final state
    std::vector<Transition*> exits;      //list of outgoing transitions

    static vector<State*>::iterator searchById(vector<State*>* list, int id);
} State;


class FA {
private:
    string _name;           //Arbitrary name
    vector<State*> _states;  //List of all the automaton's states
    vector<char> _alphabet;

    // Shows if in its current state the automaton is minimized/determinized/complete
    bool minimized = false;
    bool determinized = false;
    bool completed = false;

public:
    FA();

    FA(string);

    FA(vector<State*>* states, vector<char>* alphabet);

    void changeName(string name);

    void display() const;

    void addState();

    void addCharacterToAlphabet(char c);

    bool isComplete();

    FA minimize();

    FA determinize();
};
#endif //FINITE_AUTOMATA_MATH_CS_STRUCTURE_H
