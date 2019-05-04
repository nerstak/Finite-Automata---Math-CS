#include "FA.h"

FA* FA::complementarize() {
    if (_completed) {
        cout << "Complementary automate obtained from";
        if (_minimized) {
            cout << " minimized version." << endl;
        } else {
            cout << " just completed version." << endl;
        }

        vector<State*> newList = _states;
        for (State* st: newList) {
            st->final = !(st->final);
        }

        FA* complementary = new FA(newList, _alphabet);
        complementary->_name = _name + " Complementary";

        return complementary;
    }
    return nullptr;
}