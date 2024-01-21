#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <math.h>
using namespace std;

bool CompareString(string word1, string word2, vector<int>& places) {
   int place;
   for (int i = 0; i < (int)places.size(); i++) {
      place = places[i];

      char word1Char;
      char word2Char;

      if (place >= (int)word1.length()) {
         word1Char = '0';
      } else {
         word1Char = word1[place];
      }
      
      if (place >= (int)word2.length()) {
         word2Char = '0';
      } else {
         word2Char = word2[place];
      }

      if (word1Char < word2Char) {
         return true;
      }
      if (word1Char > word2Char) {
         return false;
      }
   }
   return true;
}


bool CompareInt(string word1, string word2, vector<int>& places) {
   int place;
   for (int i = 0; i < (int)places.size(); i++) {
      place = places[i];

      int word1Index = word1.length() -1 -place;
      int word2Index = word2.length() -1 -place;

      char word1Char;
      char word2Char;

      if (word1Index < 0) {
         word1Char = '0';
      } else {
         word1Char = word1[word1Index];
      }
      
      if (word2Index < 0) {
         word2Char = '0';
      } else {
         word2Char = word2[word2Index];
      }

      if (word1Char < word2Char) {
         return true;
      }
      if (word1Char > word2Char) {
         return false;
      }
   }
   return true;
}


void Merge(vector<string>& numbers, int i, int j, int k, char data, vector<int>& places) {
   int mergedSize;                            // Size of merged partition
   int mergePos;                              // Position to insert merged number
   int leftPos;                               // Position of elements in left partition
   int rightPos;                              // Position of elements in right partition
   string* mergedNumbers = nullptr;

   mergePos = 0;
   mergedSize = k - i + 1;
   leftPos = i;                               // Initialize left partition position
   rightPos = j + 1;                          // Initialize right partition position
   mergedNumbers = new string[mergedSize];       // Dynamically allocates temporary array
                                              // for merged numbers
   
   // Add smallest element from left or right partition to merged numbers
   while (leftPos <= j && rightPos <= k) {
      if (data == 'i') {
         if (CompareInt(numbers[leftPos], numbers[rightPos], places)) {
            mergedNumbers[mergePos] = numbers[leftPos];
            ++leftPos;
         }
         else {
            mergedNumbers[mergePos] = numbers[rightPos];
            ++rightPos;         
         }
         ++mergePos;
      } else {
         if (CompareString(numbers[leftPos], numbers[rightPos], places)) {
            mergedNumbers[mergePos] = numbers[leftPos];
            ++leftPos;
         }
         else {
            mergedNumbers[mergePos] = numbers[rightPos];
            ++rightPos;         
         }
         ++mergePos;
      }
   }
   
   // If left partition is not empty, add remaining elements to merged numbers
   while (leftPos <= j) {
      mergedNumbers[mergePos] = numbers[leftPos];
      ++leftPos;
      ++mergePos;
   }
   
   // If right partition is not empty, add remaining elements to merged numbers
   while (rightPos <= k) {
      mergedNumbers[mergePos] = numbers[rightPos];
      ++rightPos;
      ++mergePos;
   }
   
   // Copy merge number back to numbers
   for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
      numbers[i + mergePos] = mergedNumbers[mergePos];
   }
   delete[] mergedNumbers;
}

void MergeSort(vector<string>& numbers, int i, int k, char dataty, vector<int>& places) {
   int j;
   
   if (i < k) {
      j = (i + k) / 2;  // Find the midpoint in the partition
      
      // Recursively sort left and right partitions
      MergeSort(numbers, i, j, dataty, places);
      MergeSort(numbers, j + 1, k, dataty, places);
      
      // Merge left and right partition in sorted order
      Merge(numbers, i, j, k, dataty, places);
   }
}

int main(int argc, char*argv[]) {
   if (argc != 5) {
      cout << "Usage: ./a.out i|s sort_filename input_filename output_filename" << endl;
      return 0;
   }
    char* datatype;
    string sort, input, output;

    datatype = argv[1];
    sort = argv[2];
    input = argv[3];
    output = argv[4];

   if (datatype[0] != 's' && datatype[0] != 'i') {
      cout << "Invalid datatype \"" << datatype << "\" (must be \"i\" or \"s\")" << endl;
      return 0;
   }
   

    //read in sort nums
    ifstream inFS;
    inFS.open(sort);
    vector<int> sortNums;
    if (!inFS.is_open()) {
      cout << "Unable to open sort file" << endl;
      return 0;
    }
    int temp;
    while (!inFS.fail()) {
        inFS >> temp;
        sortNums.push_back(temp);
    }
    inFS.close();

    //read in input
    ifstream inFS2;
    inFS2.open(input);
    if (!inFS2.is_open()) {
      cout << "Unable to open input file" << endl;
      return 0;
    }
    vector<string> inputNums;
    int tempOb;
    string anotherTemp;
    if (datatype[0] == 'i') {
      while (inFS2 >> tempOb) {
         anotherTemp = to_string(tempOb);
         inputNums.push_back(anotherTemp);
      }
    }
    else if (datatype[0] == 's') {
      while (inFS2 >> anotherTemp) {
         inputNums.push_back(anotherTemp);
      }
    }

    inFS2.close();

    //setting up output
    ofstream outFS;
    outFS.open(output);
    if (!outFS.is_open()) {
      cout << "Unable to open output file" << endl;
      return 0;
    }

   const int NUMBERS_SIZE = inputNums.size();
   int i;
   
   
   MergeSort(inputNums, 0, NUMBERS_SIZE - 1, datatype[0], sortNums);
   
   for(i = 0; i < NUMBERS_SIZE; ++i) {
      outFS << inputNums[i] << endl;
   }
   outFS.close();
   
   return 0;
}