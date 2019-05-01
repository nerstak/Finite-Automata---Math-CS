#include "FA.h"
#include <string>

FA* FA::standardize() {

    //First, check if the Automata isn't already standard, in order to not create new state.
    if(this->checkStandard()){
        cout << "Already Standard!" << endl;
        return this;
    }

    //Initialization of our new FA
    FA* newFA = new FA(*this);
    State* newIni = new State;
    newIni->initial = true;
    newIni->id = to_string(newFA->_states.size() + 1);

    //We will go into all the initial states
    for(State* st: newFA->_states){
        if(st->initial){

            //To know if the initial state that we will have at the end is final, we check if one of the initial state is final
            if(!newIni->final){
                if(st->final)
                    newIni->final = true;
            }

            // Then we plug all the transitions of our old initial(s) state(s) in the new one
            for(int i = 0 ; i < st->exits.size() ; i++){
                newIni->exits.push_back(st->exits[i]);
            }

            // Finally, we make our old initial state not initial
            st->initial = false;
        }
    }

    // We add our new and unique initial state to our states.
    newFA->_states.push_back(newIni);
    return newFA;

}

bool FA::checkStandard(){
    // 2 case to standardize : +2 state and 1 state with a transition ending in this one.
    int count = 0;

    //We go through the states
    for(State* st: this->_states){

        //if there are more than 2 initials states, the FA isn't standard
        if(st->initial){
            count++;
            if(count==2)
                return false;
        }

        //For each transitions, if one is going to an initial state, the FA isn't standard
        for(Transition* tr: st->exits){
            if(tr->dest->initial)
                return false;
        }
    }
    //In all other case, the FA is standard
    return true;

}

