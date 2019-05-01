#include <iostream>
#include "src/FA.h"
#include "src/files.h"

int main() {
    string lmao = "automata/test5.txt";
    FA fa(lmao);
    fa.display();
    fa.isSynchronous(true);
    FA* fx = fa.determinize();
    fx->display();
    fx->isSynchronous(true);

    string boi="automata/testRead.txt";

    FA Aut(boi);
    Aut.display();
    if(Aut.recognizeWord("aa"))
        cout << "reco: aa" << endl;
    if(Aut.recognizeWord("abbbaaaaba"))
        cout << "reco: abbbaaaaba" << endl;
    if(Aut.recognizeWord("baa"))
        cout << "reco: baa" << endl;
    if(Aut.recognizeWord("aab"))
        cout << "reco: aab" << endl;
    return 0;
}