#include <iostream>
#include "src/structure.h"
#include "src/files.h"

int main() {
    std::cout << "Henlo, World!" << std::endl;
    string lmao = "automata/test.txt";
    readFile(lmao);
    return 0;
}