#include "Reading.h"

#include <iostream>

using namespace std;

bool FA::recognizeWord(string word)
{
    vector<State*> cur, Finals, next;
    State::recoverSpecials(_states , cur, Finals);
    for(char c : word)
    {
        ReadChar(c,cur,next);

        if(cur.empty())
        {
            break;
        }

        cur=next;
        next.clear();
    }

    return State::isAnyFinal(cur);
}

static void ReadChar(char c, vector<State*> &cur, vector<State*> &next)
{
    for(State * St : cur){
        for(Transition * T : St->exits){
            if(T->trans==c)
            {
                if(!State::searchById(next,T->dest->id))
                {
                    next.push_back(T->dest);
                }
            }
        }
    }
}