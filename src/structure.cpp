#include "structure.h"
#include <iostream>
using namespace std;


FA::FA(std::string FAname)
{
    name= FAname;
    determinized=minimized=completed= false;
}

FA::FA()
{
    name="Finite Automata";
    determinized=minimized=completed= false;
}

void FA::display() const
{
    int a_size=alphabet.size(), t_size, i, c, j ;

    for(i=0; i<states.size(); i++)
    {
        //Displays each state ID and if it is I/F
        cout << "State " << i << " :";

        if(states[i]->initial)
        {
            cout << " Initial";
        }
        if(states[i]->final)
        {
            cout << " Final";
        }
        cout << endl;


        //Displays the transitions of a state from each letter in the alphabet
        for(c=0;c<a_size;c++);
        {
            cout << "    "<< alphabet[c] << ": ";

            t_size=states[i]->exits.size();
            for(j=0;j<t_size;j++)
            {
                if(states[i]->exits[j]->trans==alphabet[c])
                {
                    cout << states[i]->exits[j]->dest->id << " " ;  //TODO: yeah I'll make it clearer
                }

            }
            cout << endl;
        }

        cout << endl;
    }
}
