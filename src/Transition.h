#ifndef FINITE_AUTOMATA___MATH_CS_TRANSITION_H
#define FINITE_AUTOMATA___MATH_CS_TRANSITION_H

#include <vector>

#define EMPTY '*'


// Outgoing transition from a State
typedef struct Transition {
    struct State* dest;
    char trans;

    /// Search transition having the specified character
    /// \param list List of Transition to look in
    /// \param c Character of transition to look for
    /// \return First occurrence, nullptr if none
    static Transition* searchByCharacter(std::vector<Transition*> &list, char c);

    /// Recover any occurrences in a list of transition for a character
    /// \param list List of Transition to look in
    /// \param c Character to look for
    /// \param recover List of occurrences (return by parameter)
    static void searchOccurrence(const std::vector<Transition*> &list, char c, std::vector<Transition*> &recover);
} Transition;


#endif //FINITE_AUTOMATA___MATH_CS_TRANSITION_H
