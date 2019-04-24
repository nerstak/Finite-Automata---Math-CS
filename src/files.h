#ifndef FINITE_AUTOMATA_MATH_CS_FILES_H
#define FINITE_AUTOMATA_MATH_CS_FILES_H

#include "structure.h"

/// Read a specified file and return the corresponding FA
/// \param nameFile reference of the path of the file
/// \return Address of the FA
extern FA* readFile(std::string &nameFile);

/// Create the FA from a valid stream
/// \param stream File stream (read)
/// \return Address of the FA
static FA* creatingFA(ifstream &stream);

/// Convert line of number into an array of special (initial or terminal) states
/// \param stream File stream (read)
/// \return Address of the array of States (by int)
static vector<int>* readSpecialStates(ifstream &stream);

/// Read an unique number on a line
/// \param stream File stream (read)
/// \return int
static int readUniqueNumber(ifstream &stream);

/// Create states and relationship between all of them
/// \param stream File stream (read)
/// \param initialStates Address of vector of all initial states
/// \param finalStates Address of vector of all final states
/// \param states Reference of vector of address of all states
/// \param alpha Reference of vector of alphabet
static void createStates(ifstream &stream, vector<int>* initialStates, vector<int>* finalStates, vector<State*> &states,
                         vector<char> &alpha);

/// Check if the state exists, and if not, create it
/// \param list List of address of states
/// \param init Address of vector of all initial states
/// \param final Address of vector of all final states
static void checkAndCreateSingleState(vector<State*> &list, int state, vector<int>* init, vector<int>* final);

/// Allocate memory for a state
/// \param c id of the state (char)
/// \return Address of the state
static State* allocateState(int c);

/// Convert a transition into 2 states and a character
/// \param transitionString String of transition
/// \param c Reference of the character of the transition
/// \param stateFrom Reference of the initial state of transition
/// \param stateTo Reference of the final state of transition
static void separateTransition(std::string &transitionString, char &c, int &stateFrom, int &stateTo);

/// Create a transition
/// \param list List of address of states
/// \param stateFromID ID of the initial state of transition
/// \param stateToID ID of the final state of transition
/// \param transition Character of transition
static void createTransition(vector<State*> &list, int stateFromID, int stateToID, char transition);

/// Add a character to an alphabet if not in
/// \param alpha Reference to a vector of char (alphabet)
/// \param c Character to add
static void addCharacterToAlphabet(vector<char> &alpha, char c);

/// Count the number of transition from the list of state
/// \param list Reference of a vector of address of State
/// \return Number of transition
static int countTransitions(vector<State*> &list);

#endif //FINITE_AUTOMATA_MATH_CS_FILES_H
