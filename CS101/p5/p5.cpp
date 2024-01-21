#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

class Character {
   public:
      Character() {
         key = '\0';
         freq = 0;
         leftChild = nullptr;
         rightChild = nullptr;
      }
      ~Character() {};
      char getKey() {return key;}
      int getFreq() {return freq;}
      void setFreq(int freq1) {freq = freq1;}
      void setKey(char key1) {key = key1;}
      
     Character * leftChild;
     Character * rightChild;
   private:
      int freq;
      char key;
};


class HuffmanTree {
 public:
   string arr[128];
   void encode(Character * curr, string code) {
      if (curr->getKey() != '\0') {
         arr[curr->getKey()] = code;
         return;
      };
      encode(curr->leftChild, code+"0");
      encode(curr->rightChild, code+"1");
   };
};



class QueueCompare {
public:
    // Compare the keys of the nodes
    // return true if x's key > y's key; false otherwise
    // bool operator()(T x, T y) where T is the type of the priority_queue
   bool operator()(Character * x, Character * y) {
        return (x->getFreq() > y->getFreq());
    }
};
 
int main(int argc, char *argv[]) {
    priority_queue<Character *, vector<Character *>, QueueCompare> minQueue;
    
    Character * arr[128];
    Character * charPointer;
    
    HuffmanTree HuffTree;
    
    for (int i = 0; i < 128; i++) {
         charPointer = new Character;
         charPointer->setFreq(0);
         charPointer->setKey('\0');
         arr[i] = charPointer;
    }
    
    ifstream inFS;
    inFS.open(argv[1]);
    char temp;
    int index;
    int numChars = -1;
    int uncompressedLength = -8;
    while (!inFS.fail()) {
         inFS.get(temp);
         numChars += 1;
         uncompressedLength += sizeof(temp)*8;
         index = temp;
         arr[index]->setKey(temp);
         arr[index]->setFreq((arr[index]->getFreq())+1);
    };
    arr[index]->setFreq((arr[index]->getFreq())-1);
    
    
    for (int i = 0; i < 128; i++) {
     if(arr[i]->getFreq() > 0) {
       minQueue.push((arr[i]));
     }
    }

    while (minQueue.size() > 1) {
       Character * left = minQueue.top();
       minQueue.pop();
       Character * right = minQueue.top();
       minQueue.pop();
       Character * newChar = new Character;
       newChar->setFreq(left->getFreq()+right->getFreq());
       newChar->leftChild = left;
       newChar->rightChild = right;
       minQueue.push(newChar);
    }
    HuffTree.encode(minQueue.top(), "");
    
    int compressedLength = 0;
    for(int j = 0; j<128; j++) {
       compressedLength = (HuffTree.arr[j].length())*(arr[j]->getFreq()) + compressedLength;
    }
   
    cout << "Uncompressed length: " << uncompressedLength << " bits" << endl;
    cout << "Compressed length: " << compressedLength << " bits" << endl;
    cout << "CHAR|FREQ|CODE_LEN" << endl;
    for (int i = 0; i < 128; i++) {
       if (arr[i]->getFreq() != 0) {
         cout << "'" << arr[i]->getKey() << "' | " << arr[i]->getFreq() << " | " << HuffTree.arr[i].length() << endl;
       }
    }
   
    for (int i = 0; i < 128; i++) {
       delete arr[i];
       arr[i] = NULL;
    }
   
    return 0;
}
