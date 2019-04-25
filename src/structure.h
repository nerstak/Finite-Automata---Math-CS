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
    string id;       //Arbitrary state name
    bool initial = false;   // true if this is an initial state
    bool final = false;     // true if this is a final state
    std::vector<Transition*> exits;      //list of outgoing transitions

    /// Search a state by ID
    /// \param list List of states to look in
    /// \param id ID of the state looked for
    /// \return Address of the state if found, nullptr if not
    static State* searchById(vector<State*> &list, string id);

    /// Search if any initial states in list
    /// \param list List of states
    /// \return true if any, false if none
    static bool isAnyInitial(const vector<State*> &list);

    /// Search if any final states in list
    /// \param list List of states
    /// \return true if any, false if none
    static bool isAnyFinal(const vector<State*> &list);

    /// Recover initial and final states from a list
    /// \param list List of states
    /// \param initials List where initial states will be
    /// \param finals List where final states will be
    static void recoverSpecials(const vector<State*> &list, vector<State*> &initials, vector<State*> &finals);
} State;


class FA {
private:
    string _name = "Finite automata";           //Arbitrary name
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

    void addState(string = "-1");

    void addCharacterToAlphabet(char c);

    bool isComplete();

    FA minimize();

    FA determinize();

public: // Will be private
    FA* determinization_Sync();
};

/// Generate an ID from a list of states
/// \param sameStates List of states
/// \return ID generated
extern string concatenateID(vector<State*> &sameStates);

#endif //FINITE_AUTOMATA_MATH_CS_STRUCTURE_H
