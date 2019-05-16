#include <iostream>
#include "src/FA.h"
#include "src/files.h"
#include "src/mainLoop.h"

int main() {
    mainLoop();
 /*   string lmao = "automata/L2Int1-7-36.txt";
    FA fa(lmao);
    fa.display();
    FA* fx = fa.determinize();
    fx->isSynchronous(true);
    FA* fg = fx->completion();
    fx->display();
    fg->display();
    fg->complementarize()->display();
    fg->minimize()->display();*/

   /**
    string Yoo="automata/test/test4.txt";

    FA doot(Yoo);
    doot.display();
    if(doot.recognizeWord("ab")) //yes
        cout << "Yooooooo reco: ab" << endl;

    string boi="automata/test/testRead.txt";

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
        cout << "reco: *baaaa" << endl;**/


    return 0;
}