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
/// \return Address of vector of address of states
static void createStates(ifstream &stream, vector<int>* initialStates, vector<int>* finalStates, vector<State*> &states,
                         vector<char> &alpha);

/// Check if the state exists, and if not, create it
/// \param list List of address of states
/// \param state ID (in int) of the state to add
static void checkAndCreateSingleState(vector<State*> &list, int state, vector<int>* init, vector<int>* final);

/// Allocate memory for a state
/// \param c id of the state (char)
/// \return Address of the state
static State* allocateState(int c);

static void separateTransition(std::string &transitionString, char &c, int &stateFrom, int &stateTo);

static void createTransition(vector<State*> &list, const int stateFromID, const int stateToID, const char transition);

static void addCharacterToAlphabet(vector<char> &alpha, char c);

#endif //FINITE_AUTOMATA_MATH_CS_FILES_H
