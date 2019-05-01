#ifndef FINITE_AUTOMATA_MATH_CS_STRUCTURE_H
#define FINITE_AUTOMATA_MATH_CS_STRUCTURE_H

#include <iostream>
#include <vector>

#include "State.h"

#define EMPTY '*'

using namespace std;


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
    explicit FA(const std::string &nameFile);

    /// Creating FA from existing states and alphabet
    /// \param states Vector of states
    /// \param alphabet Vector of alphabet
    FA(vector<State*> &states, vector<char> &alphabet);

    ~FA();

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
