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

    /// Search a state by ID
    /// \param list Address of list of address of states
    /// \param id ID of the state looked for
    /// \return Iterator of the state (NO SAFEGUARD, deference IFF possible)
    static vector<State*>::iterator searchById(vector<State*>* list, int id);
} State;


class FA {
private:
    string _name="Finite automata";           //Arbitrary name
    vector<State*> _states;  //List of all the automaton's states
    vector<char> _alphabet;

    // Shows if in its current state the automaton is minimized/determinized/complete
    bool _minimized = false;
    bool _determinized = false;
    bool _completed = false;

public:
    FA();

    FA(string);

    FA(vector<State*> &states, vector<char> &alphabet);

    void changeName(string name);

    void display() const;

    void addState(int= -1);

    void addCharacterToAlphabet(char c);

    bool isComplete();

    FA minimize();

    FA determinize();
};

/// Finds a specific state from its ID within a vector of states
/// \param ListStates: the vector of states
/// \param ID: the state int ID
/// \return NULL if it doesnt exist or the address to the state
State * findState(vector<State *> ListStates, int ID);

#endif //FINITE_AUTOMATA_MATH_CS_STRUCTURE_H
