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

    string Yoo="automata/test4.txt";

    FA doot(Yoo);
    doot.display();
    if(doot.recognizeWord("ab")) //yes
        cout << "Yooooooo reco: ab" << endl;

    string boi="automata/testRead.txt";

    FA Aut(boi);
    Aut.display();
    if(Aut.recognizeWord("aa")) //yes
        cout << "reco: aa" << endl;
    if(Aut.recognizeWord("abbbaaaaba")) //yes
        cout << "reco: abbbaaaaba" << endl;
    if(Aut.recognizeWord("baa")) //yes
        cout << "reco: baa" << endl;
    if(Aut.recognizeWord("aab")) //no
        cout << "reco: aab" << endl;
    if(Aut.recognizeWord("*"))   //yes
        cout << "reco: *" << endl;
    if(Aut.recognizeWord("*a*a")) //yes
        cout << "reco: *a*a" << endl;
    if(Aut.recognizeWord("baaaa")) //yes
        cout << "reco: *baaaa" << endl;
    return 0;
}