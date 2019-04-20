#ifndef FINITE_AUTOMATA_MATH_CS_STRUCTURE_H
#define FINITE_AUTOMATA_MATH_CS_STRUCTURE_H

#include <vector>

// Outgoing transition from a State
typedef struct Transition
{
    struct State * dest;
    char trans;
}Transition;

//Single automata State
typedef struct State
{
    //int id;       //Arbitrary state name          Currently this is automatic but we could have custom names
    bool initial;   // true if this is an initial state
    bool final;     // true if this is a final state
    std::vector<Transition> exits;      //list of outgoing transitions
}State;


class FA
{
private:
    std::string name;           //Arbitrary name
    std::vector<State> states;  //List of all the automaton's states

    //Shows if in its current state the automaton is minimized/determinized/complete
    bool minimized;
    bool determinized;
    bool completed;

public:
    FA();
    FA(std::string);
    

    bool complete();
    FA minimize();
    FA determinize();
};
#endif //FINITE_AUTOMATA_MATH_CS_STRUCTURE_H
