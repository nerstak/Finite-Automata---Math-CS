#ifndef FINITE_AUTOMATA_MATH_CS_DETERMINIZATION_H
#define FINITE_AUTOMATA_MATH_CS_DETERMINIZATION_H

#include "structure.h"

/// Determinization for a state
/// \param presentStates List of states, where states of the new automate will be
/// \param alphabet Alphabet (to give)
/// \param sameStates States sharing the same character of transition. At first, put the initial states
/// \param init List of initial states (to give)
/// \param fin List of final states (to give)
/// \return Address of the state determinized (only used for recursion)
static State*
determinizationProcess_Sync(vector<State*> &presentStates, vector<char> alphabet, vector<State*> sameStates,
                            vector<State*> &init, vector<State*> &fin);

#endif //FINITE_AUTOMATA_MATH_CS_DETERMINIZATION_H
