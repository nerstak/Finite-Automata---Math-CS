#include <iostream>
#include "src/structure.h"
#include "src/files.h"

int main() {
    string lmao = "automata/test5.txt";
    FA fa(lmao);
    fa.display();
    FA* fx = fa.determinize();
    fx->display();

    return 0;
}