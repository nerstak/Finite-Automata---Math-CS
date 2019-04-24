#ifndef FINITE_AUTOMATA_MATH_CS_STRUCTURE_H
#define FINITE_AUTOMATA_MATH_CS_STRUCTURE_H

#include <iostream>
#include <vector>

using namespace std;

// Outgoing transition from a State
typedef struct Transition {
    struct State* dest;
    char trans;
} Transition;

//Single automata State
typedef struct State {
    int id;       //Arbitrary state name          make this char?
    bool initial;   // true if this is an initial state
    bool final;     // true if this is a final state
    std::vector<Transition*> exits;      //list of outgoing transitions
} State;


class FA {
private:
    string name="Finite automata";           //Arbitrary name
    vector<State*> states;  //List of all the automaton's states
    vector<char> alphabet;

    // Shows if in its current state the automaton is minimized/determinized/complete
    bool minimized = false;
    bool determinized = false;
    bool completed = false;

public:
    FA();

    FA(string);

    void display() const;

    void addState(int= -1);

    bool isComplete();

    FA minimize();

    FA determinize();
};

State * findState(vector<State *> ListStates, int ID);

#endif //FINITE_AUTOMATA_MATH_CS_STRUCTURE_H
