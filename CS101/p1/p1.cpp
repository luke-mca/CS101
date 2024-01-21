#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

string toUpper(string word) {
    for(int j=0; j< word.length(); j++) {
        word[j] = toupper(word[j]);
    }
    return word;
}

int main(int argc, char *argv[]) {
    string fileIN, fileOUT;

    ifstream inFS;
    int i = 0;
    string Source[1000];
    string Destination[1000];
    int Bandwidth[1000];

    fileIN = argv[1];
    fileOUT = argv[2];
    
    inFS.open(fileIN);

    string sourceZ, destZ;

    inFS >> sourceZ;
    inFS >> destZ;
    inFS >> Bandwidth[0];
    Source[0] = toUpper(sourceZ);
    Destination[0] = toUpper(destZ);
    while (!inFS.fail()) {
        i += 1;
        inFS >> sourceZ;
        inFS >> destZ;
        inFS >> Bandwidth[i];
        Source[i] = toUpper(sourceZ);
        Destination[i] = toUpper(destZ);
    };


    ofstream outFS;
    outFS.open(fileOUT);
    int q = 0;
    string uniqLeaf[500];
    for (int k=0; k<1000; k++) {
        bool SisU = true;
        bool DisU = true;
        for(int g=0; g<500; g++) {
            if (Source[k] == uniqLeaf[g]){
                SisU = false;
            }
            if (Destination[k] == uniqLeaf[g]){
                DisU = false;
            }
        };
        if (SisU){
            uniqLeaf[q] = Source[k];
            outFS << Source[k] << endl;
            q += 1;
        }
        if (DisU){
            uniqLeaf[q] = Destination[k];
            outFS << Destination[k] << endl;
            q += 1;
        }
    };

    
    string temp;
    int fTotal = 0;
    int sTotal = 0;
    double tTotal = 0;
    for (int r=0; r<500; r++) {
        bool isSource = false;
        bool isDest = false;
        for (int n=0; n<1000; n++) {
            if (uniqLeaf[r] == Source[n] && uniqLeaf[r] != "") {
                fTotal += Bandwidth[n];
                isSource = true;
            }
            if (uniqLeaf[r] == Destination[n] && uniqLeaf[r] != "") {
                sTotal += Bandwidth[n];
                isDest = true;
            }
        }
        if (isDest && isSource) {
            tTotal = (double)(sTotal)/fTotal;
            outFS << endl << uniqLeaf[r] << " " << to_string(fTotal) << " " << to_string(sTotal) << " " << fixed << setprecision(2) << tTotal;
        }
        fTotal = 0;
        sTotal = 0;
        tTotal = 0;
    }

    inFS.close();
    outFS.close();
    
    return 0;
}