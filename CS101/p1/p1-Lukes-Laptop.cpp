#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
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
    vector<string> Source;
    vector<string> Destination;
    vector<int> Bandwidth;

    fileIN = argv[1];
    fileOUT = argv[2];
    
    inFS.open(fileIN);

    string sourceZ, destZ;
    int bandZ;

    while (!inFS.fail()) {
        inFS >> sourceZ;
        inFS >> destZ;
        inFS >> bandZ;
        Source.push_back(toUpper(sourceZ));
        Destination.push_back(toUpper(destZ));
        Bandwidth.push_back(bandZ);
    };


    ofstream outFS;
    outFS.open(fileOUT);
    int q = 0;
    vector<string> uniqLeaf;
    for (int k=0; k<Source.size(); k++) {
        bool SisU = true;
        bool DisU = true;
        for(int g=0; g<uniqLeaf.size(); g++) {
            if (Source[k] == uniqLeaf[g]){
                SisU = false;
            }
            if (Destination[k] == uniqLeaf[g]){
                DisU = false;
            }
        };
        if (SisU){
            uniqLeaf.push_back(Source[k]);
            outFS << Source[k] << endl;
            q += 1;
        }
        if (DisU){
            uniqLeaf.push_back(Destination[k]);
            outFS << Destination[k] << endl;
            q += 1;
        }
    };

    
    string temp;
    int fTotal = 0;
    int sTotal = 0;
    double tTotal = 0;
    for (int r=0; r<uniqLeaf.size(); r++) {
        bool isSource = false;
        bool isDest = false;
        for (int n=0; n<(Destination.size()-1); n++) {
            if (uniqLeaf[r] == Destination[n] && uniqLeaf[r] != "") {
                sTotal += Bandwidth[n];
                isDest = true;
            }
            if (uniqLeaf[r] == Source[n] && uniqLeaf[r] != "") {
                fTotal += Bandwidth[n];
                isSource = true;
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

    outFS << endl;

    inFS.close();
    outFS.close();
    
    return 0;
}