#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>

using namespace std;

uint64_t djb2(string str) {
    const char *ptr = str.c_str();
    uint64_t hash = 5381;
    int c;
    while ((c = *ptr++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

class Person {
public:
    string id;
    string first;
    string last;
    string email;
    string phone;
    string city;
    string state;
    string postalCode;

    string key;
};
std::ostream &operator<<(std::ostream &os, Person const &m) { 
    return os << m.key;
}

class HashTable {
public:
    vector<list<Person>> HT;
};

void getVal(istream &is, string &str) {
    char ch;
    string line;

    is >> ch;
    getline(is, line);

    str = ch + line;
}

bool isValidKey(const string &key) {
    string validKeys[8] = { "Id", "FirstName", "LastName", "Email", "Phone", "City", "State", "PostalCode" };
    for (int i = 0; i < 8; i++) {
        if (key == validKeys[i]) {
            return true;
        }
    }
    return false;
}

int main(int argc, char **argv) {
    if (argc != 4) {
        cout << "Usage: ./a.out filename.txt table_size key" << endl;
        return 1;
    }

    string filename = argv[1];
    int tableSize = stoi(argv[2]);
    string key = argv[3];

    ifstream file(filename);
    if (!file) {
        cout << "Unable to open " << filename << endl;
        return 2;
    }

    if (!isValidKey(key)) {
        cout << "Invalid key: " << key << endl;
        return 3;
    }
   

    string Keys[8] = {"Id", "FirstName", "LastName", "Email", "Phone", "City", "State", "PostalCode"};
    HashTable *main = new HashTable();
    main->HT.resize(tableSize);
    // This is an example of how to retreive the tokens from the input file
    // You will need to modify this to fit your needs to build the hash table
    string line, token;
    int index;
    getline(file, line); // consume header line
    while (getline(file, line)) {
        istringstream iss(line);
        Person *x = new Person();
        for (int k = 0; k < 8; k++) {
            getline(iss, token, '\t');
            Keys[k] = token;
        }
        x->id = Keys[0];
        x->first = Keys[1];
        x->last = Keys[2];
        x->email = Keys[3];
        x->phone = Keys[4];
        x->city = Keys[5];
        x->state = Keys[6];
        x->postalCode = Keys[7];
        if (key == "Id")  x->key = x->id;
        if (key == "FirstName")  x->key = x->first;
        if (key == "LastName")  x->key = x->last;
        if (key == "Email")  x->key = x->email;
        if (key == "Phone")  x->key = x->phone;
        if (key == "City")  x->key = x->city;
        if (key == "State")  x->key = x->state;
        if (key == "PostalCode")  x->key = x->postalCode;

        index = djb2(x->key) % main->HT.size();
        if ((main->HT[index].empty())) {
            main->HT[index].push_back(*x);
            // cout << *x << " : " << index << endl;
        }
        else if (main->HT[index].front().key == x->key){
            main->HT[index].push_back(*x);
            // cout << *x << " : " << index << endl;
        }
        else {
            int j = 1;
            // cout << *x << " : " << index << "*" << endl;
            int origIndex = index;
            while (x->key != main->HT[index].front().key && !(main->HT[index].empty())) {
                index = (origIndex + j*(43-(djb2(x->key) % 43))) % main->HT.size();
                j++;
                // cout << *x << " : " << index << "**" << endl;
            }
            main->HT[index].push_back(*x);
        }
    }

    cout << "Commands:" << endl << "\tprint" << endl << "\tlookup <key>" << endl << "\tquit" << endl;
    string cmd, val;
    while (1) {
        cout << endl << "Enter a command:" << endl;
        cin >> cmd;
        if (cmd == "quit") {
            break;
        }
        else if (cmd == "print") {
            for (int p=0; p < main->HT.size(); p++) {
                if (!(main->HT[p].empty())) {
                    cout << p << ": " << main->HT[p].front().key << "(" << main->HT[p].size() << ")" << "," << endl;
                }
            }
        }
        else if (cmd == "lookup") {
            getVal(cin, val);
            int notThere = 0;
            int tempIndex = djb2(val) % main->HT.size();
            // cout << val << "VAL" << endl;
            int origIndex2 = tempIndex;
            int k = 1;
            while ((main->HT[tempIndex].front().key) != val) {
                tempIndex = (origIndex2 + k*(43-(djb2(val) % 43))) % main->HT.size();
                k++;
                if (k > main->HT.size()) {
                    cout << "No results" << endl;
                    notThere = 1;
                    break;
                }
            }
            if (!notThere) {
                cout << "Id,FirstName,LastName,Email,Phone,City,State,PostalCode" << endl;
                list<Person>::iterator iterator;
                for (iterator = main->HT[tempIndex].begin(); iterator != main->HT[tempIndex].end(); ++iterator) {
                    cout << iterator->id << ",";
                    cout << iterator->first << ",";
                    cout << iterator->last << ",";
                    cout << iterator->email << ",";
                    cout << iterator->phone << ",";
                    cout << iterator->city << ",";
                    cout << iterator->state << ",";
                    cout << iterator->postalCode;
                    cout << endl;
                };
            }
            // cout << "looking up: " << val << endl;
        }
        else {
            getline(cin, val);
            cout << "Invalid command" << endl;
        }
    }

    return 0;
}
