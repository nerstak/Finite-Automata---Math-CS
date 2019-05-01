#ifndef FINITE_AUTOMATA_MATH_CS_FILES_H
#define FINITE_AUTOMATA_MATH_CS_FILES_H

#include "FA.h"

/// Convert line of number into an array of special (initial or terminal) states
/// \param stream File stream (read)
/// \return List of special states
static vector<string>* readSpecialStates(ifstream &stream);

/// Read an unique number on a line
/// \param stream File stream (read)
/// \return int Number read on the line
static int readUniqueNumber(ifstream &stream);

/// Create states and relationship between all of them
/// \param stream File stream (read)
/// \param initialStates List of initial states
/// \param finalStates List of final states
/// \param states List of all states
/// \param alpha Alphabet of the FA
static void createStates(ifstream &stream, vector<std::string>* initialStates, vector<std::string>* finalStates,
                         vector<State*> &states, vector<char> &alpha);

/// Check if the state exists, and if not, create it
/// \param list List of all states
/// \param state ID of the state
/// \param init List of initial states
/// \param final List of final states
static void checkAndCreateSingleState(vector<State*> &list, const std::string &state, vector<std::string>* init,
                                      vector<std::string>* final);

/// Allocate memory for a state
/// \param id ID of the state (string)
/// \return Address of the state
static State* allocateState(std::string id);

/// Convert a transition into 2 states and a character (return by parameters)
/// \param transitionString String of transition
/// \param c Character of transition
/// \param stateFrom Initial state of transition
/// \param stateTo Final state of transition
static void separateTransition(std::string &transitionString, char &c, std::string &stateFrom, std::string &stateTo);

/// Create a transition
/// \param list List of all states
/// \param stateFromID ID of the initial state of transition
/// \param stateToID ID of the final state of transition
/// \param transition Character of transition
static void
createTransition(vector<State*> &list, const std::string &stateFromID, const std::string &stateToID, char transition);

/// Add a character to an alphabet if not in
/// \param alpha Alphabet of the FA
/// \param c Character to add
static void addCharacterToAlphabet(vector<char> &alpha, char c);

/// Count the number of transition from the list of state
/// \param list Reference of a vector of address of State
/// \return Number of transition
static int countTransitions(vector<State*> &list);

/// Verify if a transition already exists (same character, same destination)
/// \param stateFrom State from where the transition comes
/// \param stateTo State where the transition leads
/// \param c Character of transition
/// \return true if existing, false if not
static bool verifyExistence(const State* stateFrom, const State* stateTo, char c);

#endif //FINITE_AUTOMATA_MATH_CS_FILES_H
