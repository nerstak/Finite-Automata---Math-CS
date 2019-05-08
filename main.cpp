#include <iostream>
#include "src/FA.h"
#include "src/files.h"

int main() {
    string lmao = "automata/test3.txt";
    FA fa(lmao);
    fa.display();
    fa.isSynchronous(true);
    FA* fx = fa.determinize();
    FA* fg = fx->completion();
    fx->display();
    fg->display();
    fx->isComplete(true);
    fg->isDeterministic(true);

    return 0;
}