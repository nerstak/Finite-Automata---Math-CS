#include "mainLoop.h"
#include "FA.h"

int mainLoop() {
    vector<FA*> *myFA = new vector<FA*>;
    int looper = 0;
    while (looper != 5) {
        looper = displayMainMenu();
        if(looper == 5)
            return 0;
        processAction(myFA,looper);
    }
}


int displayMainMenu(){
    cout << "~~Hello user~~" << endl;
    cout << "Make a choice :" << endl;
    cout << "[1] Load FA from files" << endl;
    cout << "[2] Display FA" << endl;
    cout << "[3] Compute FA (Determinize, Minimize, Complete..." << endl;
    cout << "[4] Word Recognize" << endl;
    cout << "[5] Exit" << endl;

    int i = 0;
    cin >> i;
    while (i<1 || i>5){
        cout << "Wrong entry. Please make a choice between 1 and 5." << endl;
        cin >> i;
    }
    return i;
}

void processAction(vector<FA*> *myFA, int action){

    switch (action){
        case 1:addVectorFromFiles(myFA);
                break;

        case 2: FA* temp;
                temp = pickFA(myFA);
                if(temp != nullptr)
                    temp->display();
                break;

        case 3: FA* temp1;
                temp1 = pickFA(myFA);
                if(temp1 == nullptr)
                    break;
                int i;
                i = displayComputeMenu() ;
                processComputationFA(i,temp1,myFA);
                break;
        case 4:  wordReco(myFA);
            break;
    }
}

void addVectorFromFiles(vector<FA*> *myFA){
    std::string myFile;
    myFile = "automata/L2Int1-7-" + to_string(askForFileNumber()) + ".txt";
    FA *temp = new FA(myFile);
    myFA->push_back(temp);
    cout << myFA->size();
    showMyFA(*myFA);
}

FA* pickFA(vector<FA*> *myFA){
    cout << "Choose a FA in:" << endl;
    showMyFA(*myFA);
    int i = 0;
    while(i < 1 || i > myFA->size()){
        cout << "Your choice (0 to exit) :" ;
        cin >> i;
        if(i>-1 && i < myFA->size() + 1) {
            if(i==0)
                return nullptr;
            return (*myFA)[i - 1];
        }
    }

}

int askForFileNumber(){
    int r = 0;
    while (r<1 || r>44){
        cout << "Enter the FA you want to load :" << endl;
        cin >> r;
        if(r>0 && r<45)
            return r;
        cout << "Not possible ! ";
    }
}

void showMyFA(vector<FA*> myFa){
    cout << "My FA : " << endl ;
    for(int i = 0; i < myFa.size() ; i++){
        cout << "[" << i+1 << "] : " << myFa[i]->getName() << endl;
    }
}


int displayComputeMenu(){
        cout << "Choose computation :" << endl;
        cout << "[1] Completation" << endl;
        cout << "[2] Determinize" << endl;
        cout << "[3] Standardize" << endl;
        cout << "[4] Minimize" << endl;
        cout << "[5] Complementarize" << endl;
        cout << "[6] Exit" << endl;

        int i = 0;
        cin >> i;
        while (i<1 || i>6){
            cout << "Wrong entry. Please make a choice between 1 and 5." << endl;
            cin >> i;
        }
        return i;
}

void processComputationFA(int a,FA *currentFA,vector<FA*> *myFA ){
    switch(a){
        case 1: completatationAndAdd(currentFA,myFA);
            break;
        case 2: determinizeAndAdd(currentFA,myFA);
            break;
        case 3: standardizeAndAdd(currentFA,myFA);
            break;
        case 4: minimizeAndAdd(currentFA,myFA);
            break;
        case 5: ComplementarizationAndAdd(currentFA,myFA);
                break;
        case 6:
            break;
    }
}



void completatationAndAdd(FA *currentFA,vector<FA*> *myFA){
    if(currentFA->isComplete(true)){

    }
    else {
        FA *temp;
        temp = currentFA->completion();
        if (temp == nullptr)
            cout << "Can't complete : you need to determinize..." << endl;
        else {
            myFA->push_back(temp);
            cout << "Successful Completion!" << endl;
        }
    }
}

void determinizeAndAdd(FA *currentFA,vector<FA*> *myFA) {
    if (currentFA->isDeterministic(true)) {
        cout << "Already Determinize!" << endl;
    } else {
        FA *temp;
        temp = currentFA->determinize();
        myFA->push_back(temp);
    }
}

void standardizeAndAdd(FA *currentFA,vector<FA*> *myFA) {
    if (currentFA->isStandard()) {
        cout << "Already standard!" << endl;
    } else {
        FA *temp;
        temp = currentFA->standardize();
        myFA->push_back(temp);
    }
}

void minimizeAndAdd(FA *currentFA,vector<FA*> *myFA) {
        FA *temp;
        temp = currentFA->minimize();
        if(temp != nullptr)
            myFA->push_back(temp);
}

void ComplementarizationAndAdd(FA *currentFA,vector<FA*> *myFA) {

        FA *temp;
        temp = currentFA->complementarize();
        if(temp != nullptr)
            myFA->push_back(temp);
        else
            cout<< "Operation not possible : you need to complete " << endl;
}

void wordReco(vector<FA*> *myFA) {
    FA *temp = pickFA(myFA);
    if (myFA != nullptr) {
        string myWord;
        cout << "Write a word ('exit' to exit) :" << endl;
        cin >> myWord;
        if (myWord != "exit") {
            if (temp->recognizeWord(myWord))
                cout << "Word is recognize" << endl;
            else
                cout << "Word is NOT recognize" << endl;
        }
    }
}