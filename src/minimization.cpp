#include "minimization.h"


FA* FA::minimize()
{
    //TODO prevent Non deterministic, Non complete FA + add comments
    Partition P = new vector<PatternGroup>;
    P->resize(2);

    for (State* St: _states)
    {
        if (St->final)
        {
            (*P)[0].group.push_back(St); //Final
        } else
        {
            (*P)[1].group.push_back(St); //NonFinal
        }
    }

    P = partitioning(P, _alphabet);

    FA* newAuto = new FA;

    newAuto->_states = *Partition2States(P, _alphabet);
    newAuto->_alphabet = _alphabet;
    newAuto->_completed = true;
    newAuto->_determinized = true;
    newAuto->_minimized = true;
    newAuto->_synchronous = true;
    newAuto->_name = "Minimized " + _name;

    return newAuto;
}


static Partition partitioning(Partition P, vector<char> alphabet)
{
    vector<Partition> AllParts;
    vector<int>* patt;
    Partition nextP;
    PatternGroup* newPattGroup;
    vector<PatternGroup>::iterator EndPattGroups;


    for (PatternGroup const &Pgroup  : *P)
    {
        nextP = new vector<PatternGroup>;

        for (State* St : Pgroup.group)
        {
            patt = getPattern(P, St->exits, alphabet);
            for (EndPattGroups = nextP->begin(); EndPattGroups != nextP->end(); ++EndPattGroups)
            {
                if (isSamePattern(*patt, EndPattGroups->pattern))
                {
                    EndPattGroups->group.push_back(St);
                    break;
                }
            }
            if (EndPattGroups == nextP->end())
            {
                newPattGroup = new PatternGroup;
                newPattGroup->group.push_back(St);
                newPattGroup->pattern = (*patt);
                nextP->push_back(*newPattGroup);
            }
        }
        AllParts.push_back(nextP);
    }

    //Concat AllParts
    nextP = new vector<PatternGroup>;
    for (Partition Part: AllParts)
    {
        nextP->insert(nextP->end(), Part->begin(), Part->end());
    }


    if (nextP->size() > P->size())
    {
        //TODO Clear P but good
        P->clear();

        nextP = partitioning(nextP, alphabet);
    }

    return nextP;
}

static vector<State*>* Partition2States(Partition P, vector<char> &alphabet)
{
    vector<State*>* FaStates = new vector<State*>;
    State* newSt;

    for (PatternGroup curG : *P)
    {
        newSt = new State;
        for (State* curSt : curG.group)
        {
            if (curSt != curG.group[0])
            {
                newSt->id += "+";
            }
            newSt->id += curSt->id;
        }
        newSt->initial = State::isAnyInitial(curG.group);
        newSt->final = State::isAnyFinal(curG.group);
        FaStates->push_back(newSt);
    }

    Transition* newTrans;

    for (int i = 0; i < FaStates->size(); i++)
    {
        for (int j = 0; j < alphabet.size(); j++)
        {
            newTrans = new Transition;
            newTrans->trans = alphabet[j];
            newTrans->dest = (*FaStates)[(*P)[i].pattern[j]]; // dont even try with this cursed line
            (*FaStates)[i]->exits.push_back(newTrans);
        }
    }

    return FaStates;
}

static vector<int>* getPattern(Partition source, vector<Transition*> &exits, vector<char> alphabet)
{
    vector<int>* newpatt = new vector<int>;
    for (char c: alphabet)
    {
        for (Transition* T : exits)
        {
            if (T->trans == c)
            {
                for (int i = 0; i < source->size(); i++)
                {
                    if (State::searchById((*source)[i].group, T->dest->id))
                    {
                        newpatt->push_back(i);
                    }
                }
                break;
            }
        }
    }
    return newpatt;
}


static bool isSamePattern(vector<int> &p1, vector<int> &p2)
{
    auto i = p1.begin(), j = p2.begin();
    for (i, j; i != p1.end() && j != p2.end(); ++i, ++j)
    {
        if (*i != *j)
            return false;
    }

    return i == p1.end() && j == p2.end();

}