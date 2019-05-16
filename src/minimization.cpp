#include "minimization.h"


FA* FA::minimize()
{
    if (_completed && _determinized)
    {
        Partition P = new vector<PatternGroup>;
        PatternGroup Finals, NonFinals;

        //The initial Partition is the F and NF states
        for (State* St: _states)
        {
            if (St->final)
            {
                Finals.group.push_back(St); //Final
            } else
            {
                NonFinals.group.push_back(St); //NonFinal
            }
        }
        if (!NonFinals.group.empty())
        {
            P->push_back(NonFinals);
        }
        if (!Finals.group.empty())
        {
            P->push_back(Finals);
        }


        P = partitioning(P, _alphabet);

        //Creates a new FA from a list of states
        FA* newAuto = new FA;

        newAuto->_states = *Partition2States(P, _alphabet);
        newAuto->_alphabet = _alphabet;
        newAuto->_completed = true;
        newAuto->_determinized = true;
        newAuto->_minimized = true;
        newAuto->_synchronous = true;
        newAuto->_name = "Minimized " + _name;

        return newAuto;
    } else
    {
        cout << "FA must be Complete and Deterministic." << endl;
        return nullptr;
    }

}


static Partition partitioning(Partition P, vector<char> alphabet)
{
    vector <Partition> AllParts;
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

    //clear it up
    AllParts.clear();
    if (nextP->size() > P->size())
    {
        for(PatternGroup curg : *P)
        {
            curg.group.clear();
            curg.pattern.clear();
        }
        P->clear();

        nextP = partitioning(nextP, alphabet);
    }

    return nextP;
}

static vector<State*>* Partition2States(Partition P, vector<char> &alphabet)
{
    vector < State * > *FaStates = new vector<State*>;
    State* newSt;

    //Print the table of Association
    cout << endl << "   Table of Association:" << endl << endl;
    for (int l = 0; l < P->size(); l++)
    {
        newSt = new State;
        newSt->id= to_string(l);
        cout<< " " << l << ":    ";

        for (State* curSt : (*P)[l].group)
        {
            if (curSt != (*P)[l].group[0])
            {
                cout << " + ";
            }
            cout << curSt->id;
        }
        cout << endl;
        newSt->initial = State::isAnyInitial((*P)[l].group);
        newSt->final = State::isAnyFinal((*P)[l].group);
        FaStates->push_back(newSt);
    }

    Transition* newTrans;

    //Sets up proper Transitions
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
            //This makes sure that the pattern order is consistant
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