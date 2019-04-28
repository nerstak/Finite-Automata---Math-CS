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

    /// Search transition having the specified character
    /// \param list List of Transition to look in
    /// \param c Character of transition to look for
    /// \return First occurrence, nullptr if none
    static Transition* searchByCharacter(vector<Transition*> &list, char c);

    /// Recover any occurrences in a list of transition for a character
    /// \param list List of Transition to look in
    /// \param c Character to look for
    /// \param recover List of occurrences (return by parameter)
    static void searchOccurrence(const vector<Transition*> &list, char c, vector<Transition*> &recover);
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
    bool _synchronous = false;

public:
    FA();

    /// Creating FA from a file
    /// \param nameFile Path and name of the file
    explicit FA(std::string nameFile);

    /// Creating FA from existing states and alphabet
    /// \param states Vector of states
    /// \param alphabet Vector of alphabet
    FA(vector<State*> &states, vector<char> &alphabet);

    /// Copy constructor
    /// \param toCopy FA to copy from
    FA(FA &toCopy);

    void changeName(const string &name);

    void display() const;

    void addState(string = "-1");

    /// Check if an automate is synchronous
    /// \param display Display result and explanation if true (false by default)
    /// \return bool
    bool isSynchronous(const bool display) const;

    /// Check if an automate is deterministic
    /// \param display Display result and explanation if true (false by default)
    /// \return bool
    bool isDeterministic(const bool display) const;

    bool isComplete();

    FA* minimize();

    /// Determinize an FA
    /// \return Address of the determinized FA
    FA* determinize();

    /// Run every checkX
    void runTest();

private:
    /// Inner function of the constructor from file
    /// \param stream Valid input stream
    void creatingFAFile(ifstream &stream);

    /// Inner function of the copy constructor
    /// \param toCopyStates States of the FA to copy from
    /// \param newID ID of the state to create
    /// \return Address of the state (used only for recursion)
    State* copyStatesProcess(std::vector<State*> &toCopyStates, const string &newID);

    /// Process of determinization of a Sync Automate
    /// \return Address of the determinized automate
    FA* determinization_Sync();

    /// Process of determinization of an Async Automate
    /// \return Address of the determinized automate
    FA* determinization_Async();

    /// Check if the automate is synchronous or not. Should be used after every change in the automate
    void checkSynchronous();

    /// Check if the automate is deterministic or not. Should be used after every change in the automate
    void checkDeterministic();
};

/// Generate an ID from a list of states
/// \param sameStates List of states
/// \return ID generated
extern string concatenateID(vector<State*> sameStates);

/// Sub function of FA::isDeterministic(), checking the number of entry
/// \param list List of states to check in
static void oneEntry(const vector<State*> &list);

/// Sub function of FA::isDeterministic(), checking if every transition is unique
/// \param list List of states
/// \param alphabet Alphabet of the FA
static void uniqueTransition(const vector<State*> &list, vector<char> alphabet);

#endif //FINITE_AUTOMATA_MATH_CS_STRUCTURE_H
