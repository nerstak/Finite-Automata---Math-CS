#include <iostream>
#include "src/FA.h"
#include "src/files.h"

int main() {
    string lmao = "automata/test/test5.txt";
    FA fa(lmao);
    fa.display();
    FA* fa2 = fa.standardize();
   // fa2->display();

    return 0;
}