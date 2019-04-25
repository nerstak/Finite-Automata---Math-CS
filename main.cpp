#include <iostream>
#include "src/structure.h"
#include "src/files.h"

int main() {
    string lmao = "automata/test2.txt";
    FA* fa = readFile(lmao);
    if (fa != nullptr) {
        fa->display();
        auto x = fa->determinization_Sync();
        delete (fa);
        x->display();
    } else {
        cout << "Error while reading file" << endl;
    }

    return 0;
}