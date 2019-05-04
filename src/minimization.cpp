#include "minimization.h"


FA* FA::minimize()
{
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

    return Partition2FA(P);
}


static Partition partitioning(Partition P, vector<char> alphabet)
{
    vector<Partition> AllParts;
    vector<int>* patt;
    Partition nextP;
    PatternGroup* newPattGroup;
    vector<PatternGroup>::iterator EndPattGroups;


    for (PatternGroup Pgroup  : *P)
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

static FA* Partition2FA(Partition P)
{


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

    return !(i == p1.end() || j == p2.end());

}