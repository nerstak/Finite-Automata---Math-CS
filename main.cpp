#include <iostream>
#include "src/structure.h"
#include "src/files.h"

int main() {
    FA d;
    d.addState();
    string lmao = "automata/test.txt";
    readFile(lmao)->display();
    return 0;
}