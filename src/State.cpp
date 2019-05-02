#include <algorithm>
#include "State.h"

using namespace std;

State* State::searchById(vector<State*> &list, string id) {
    vector<State*>::iterator it;
    it = find_if(list.begin(), list.end(), [&id](State* st) -> bool {
        return st->id == id;
    });
    if (it != list.end()) {
        return *it;
    }
    return nullptr;
}


bool State::isAnyInitial(const vector<State*> &list) {
    for (State* st: list) {
        if (st->initial) {
            return true;
        }
    }
    return false;
}

bool State::isAnyFinal(const vector<State*> &list) {
    for (State* st: list) {
        if (st->final) {
            return true;
        }
    }
    return false;
}

void State::recoverSpecials(const vector<State*> &list, vector<State*> &initials, vector<State*> &finals) {
    for (State* st: list) {
        if (st->initial) {
            initials.push_back(st);
        }
        if (st->final) {
            finals.push_back(st);
        }
    }
}

void State::sortStates(std::vector<State*> &list) {
    sort(list.begin(), list.end(),
         [](const State* st1, const State* st2) -> bool {
             return stoi(st1->id) < stoi(st2->id);
         });
}

