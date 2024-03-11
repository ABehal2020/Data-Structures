//
//  main.cpp
//  hw6
//
//  Created by Aditya Behal on 3/21/21.
//  Copyright © 2021 Aditya Behal. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include "point.hpp"

using namespace std;

// sorting by length of cord
bool wordLength(const string& word1, const string& word2) {
    return (word1.size() < word2.size());
}

void parseDictionary(ifstream& dictionary, vector<string>& dictionaryWords) {
    string word;
    while (dictionary >> word) {
        dictionaryWords.push_back(word);
    }
    sort(dictionaryWords.begin(), dictionaryWords.end(), wordLength);
    cout << "debug" << endl;
}

void parsePuzzleInput(ifstream& puzzleInput, vector<int>& constraints, vector<vector<char>>& board) {
    string puzzleLine;
    vector<char> puzzleLineVector;
    while (puzzleInput >> puzzleLine) {
        if (puzzleLine[0] == '!') {
            continue;
        } else if (puzzleLine[0] == '+') {
            string constraintLength = puzzleLine.substr(1);
            constraints.push_back(stoi(constraintLength));
        } else {
            for (string::iterator itr = puzzleLine.begin(); itr != puzzleLine.end(); itr++) {
                puzzleLineVector.push_back(*itr);
            }
            board.push_back(puzzleLineVector);
            puzzleLineVector.clear();
        }
    }
    sort(constraints.begin(), constraints.end());
    cout << "debug" << endl;
}

void searchAcross() {
    
}

void searchDown() {
    
}

void searchWords(ifstream& puzzleInput) {
    
}

void Combinations(vector<string> a, int requiredLength, int start, int currentLength, vector<bool>& checking, vector<string>& wordCombos)
{
    if (currentLength > requiredLength) {
        return;
    } else if (currentLength == requiredLength) {
        for (int i = 0; i < a.size(); i++) {
            if (checking[i] == true) {
                wordCombos.push_back(a[i]);
            }
        }
        return;
    }
    if (start == a.size()) {
        return;
    }
    checking[start] = true;
    Combinations(a, requiredLength, start + 1, currentLength + 1, checking, wordCombos);
    checking[start] = false;
    Combinations(a, requiredLength, start + 1, currentLength, checking, wordCombos);
}

void pointCombosRecursive(const vector<vector<Point>>& pointCombos, unsigned int currentIndex, unsigned int comboDimensions, unsigned int i) {
    if (currentIndex == comboDimensions - 1) {
        // cout << pointCombos[currentIndex][i].x << " " << pointCombos[currentIndex][i].y << endl;
        cout << pointCombos[0][i].x << " " << pointCombos[0][i].y << " " << pointCombos[1][i].x << " " << pointCombos[1][i].y << " " << pointCombos[2][i].x << " " << pointCombos[2][i].y << endl;
        return;
    } else {
        for (unsigned int i = 0; i < pointCombos[currentIndex].size(); i++) {
            pointCombosRecursive(pointCombos, currentIndex + 1, comboDimensions, i);
        }
        /*
         counter = 0;
         
         for (unsigned int i = 0; i < pointCombos[0].size(); i++) {
         for (unsigned int j = 0; j < pointCombos[1].size(); j++) {
         for (unsigned k = 0; k < pointCombos[2].size(); k++) {
         cout << pointCombos[0][i].x << " " << pointCombos[0][i].y << " " << pointCombos[1][j].x << " " << pointCombos[1][j].y << " " << pointCombos[2][k].x << " " << pointCombos[2][k].y << endl;
         counter++;
         }
         }
         }
         
         cout << counter << endl;
         */
    }
}

/*
counter = 0;

for (unsigned int i = 0; i < pointCombos[0].size(); i++) {
    for (unsigned int j = 0; j < pointCombos[1].size(); j++) {
        for (unsigned k = 0; k < pointCombos[2].size(); k++) {
            cout << pointCombos[0][i].x << " " << pointCombos[0][i].y << " " << pointCombos[1][j].x << " " << pointCombos[1][j].y << " " << pointCombos[2][k].x << " " << pointCombos[2][k].y << endl;
            counter++;
            }
            }
            }
*/

void findWordCombinations(const vector<int>& constraints, const vector<string>& dictionaryWords, vector<vector<string>>& searchCombinationsInput, vector<vector<string>>& searchCombinations, vector<vector<string>>& finalizedCombinations) {
    vector<int> frequency;
    int currentFrequency = 1;
    int currentValue = constraints[0];
    for (unsigned int i = 1; i < constraints.size(); i++) {
        if (currentValue == constraints[i]) {
            currentFrequency++;
        } else if (constraints[i] > currentValue) {
            frequency.push_back(currentFrequency);
            currentFrequency = 1;
            currentValue = constraints[i];
        }
    }
    frequency.push_back(currentFrequency);
    
    vector<string> word;
    unsigned int currentSize = dictionaryWords[0].size();
    word.push_back(dictionaryWords[0]);
    for (unsigned int i = 1; i < dictionaryWords.size(); i++) {
        if (currentSize == dictionaryWords[i].size()) {
            word.push_back(dictionaryWords[i]);
        } else {
            currentSize = dictionaryWords[i].size();
            searchCombinationsInput.push_back(word);
            word.clear();
            word.push_back(dictionaryWords[i]);
        }
    }
    searchCombinationsInput.push_back(word);
    
    vector<string> wordCombos;
    int counter = 0;
    for (unsigned int i = 0; i < searchCombinationsInput.size(); i++) {
        unsigned int checkSize = searchCombinationsInput[i].size();
        vector<bool> check = {false};
        Combinations(searchCombinationsInput[i], frequency[counter], 0, 0, check, wordCombos);
        counter++;
        searchCombinations.push_back(wordCombos);
        wordCombos.clear();
    }
    
    vector<vector<vector<string>>> allPossibleCombos;
    vector<vector<string>> singleCombo;
    vector<string> words;
    counter = 0;
    unsigned int cycles = 0;
    for (unsigned int i = 0; i < searchCombinations.size(); i++) {
        for (unsigned int j = 0; j < searchCombinations[i].size(); j++) {
            if (cycles < frequency[counter]) {
                words.push_back(searchCombinations[i][j]);
                /*
                 for (unsigned int i = 0; i < words.size(); i++) {
                 cout << words[i] << endl;
                 }
                 cout << endl;
                 */
                cycles++;
                // cout << "cycles: " << cycles << endl;
            } else {
                singleCombo.push_back(words);
                words.clear();
                words.push_back(searchCombinations[i][j]);
                cycles = 1;
            }
        }
        singleCombo.push_back(words);
        allPossibleCombos.push_back(singleCombo);
        words.clear();
        singleCombo.clear();
        cycles = 0;
        counter++;
    }
    
    vector<string> finalCombo;
    vector<vector<Point>> pointCombos;
    vector<Point> pointCombo;
    for (unsigned int i = 0; i < allPossibleCombos.size(); i++) {
        for (unsigned int j = 0; j <= frequency[i]; j++) {
            pointCombo.push_back(Point(i, j));
        }
        pointCombos.push_back(pointCombo);
        pointCombo.clear();
    }
    
    unsigned int comboDimensions = pointCombos.size();
    // unsigned int currentIndex = 0;
    // pointCombosRecursive(pointCombos);
    
    // pointCombosRecursive(pointCombos, currentIndex, comboDimensions, 0);
    
     counter = 0;
     
     for (unsigned int i = 0; i < pointCombos[0].size(); i++) {
         for (unsigned int j = 0; j < pointCombos[1].size(); j++) {
             for (unsigned k = 0; k < pointCombos[2].size(); k++) {
                 cout << pointCombos[0][i].x << " " << pointCombos[0][i].y << " " << pointCombos[1][j].x << " " << pointCombos[1][j].y << " " << pointCombos[2][k].x << " " << pointCombos[2][k].y << endl;
                 counter++;
             }
         }
     }
     
     cout << counter << endl;
    
    /*
     unsigned int iRef;
     unsigned int jRef;
     
     for (unsigned int i = 0; i < pointCombos.size(); i++) {
     for (unsigned int j = 0; j < pointCombos[i].size(); j++) {
     iRef = pointCombos[i][j].x;
     jRef = pointCombos[i][j].y;
     cout << "iRef: " << iRef << ", jRef: " << jRef << endl;
     finalCombo.insert(finalCombo.end(), allPossibleCombos[iRef][jRef].begin(), allPossibleCombos[iRef][jRef].end());
     finalizedCombinations.push_back(finalCombo);
     finalCombo.clear();
     }
     }
     */
    
    /*
     // vector<string> finalCombo;
     unsigned int i = 0;
     unsigned int j = 0;
     unsigned int trackerI = i;
     unsigned int counterCombos = 0;
     while (i < allPossibleCombos.size()) {
     while (j < allPossibleCombos[i].size()) {
     cout << "i: " << i << ", j: " << j << endl;
     finalCombo.insert(finalCombo.end(), allPossibleCombos[i][j].begin(), allPossibleCombos[i][j].end());
     i++;
     }
     finalizedCombinations.push_back(finalCombo);
     finalCombo.clear();
     i = trackerI;
     
     }
     for (unsigned int i = 0; i < allPossibleCombos.size(); i++) {
     for (unsigned int j = 0; j < allPossibleCombos[i].size(); j++) {
     finalCombo = allPossibleCombos[i][j];
     finalizedCombinations.push_back(finalCombo);
     finalCombo.clear();
     i++;
     }
     }
     */
    
    cout << "debug" << endl;
}

int main(int argc, const char * argv[]) {
    // error checking to make sure correct number of arguments are supplied
    if (argc != 5 && argc != 6) {
        cerr << "Invalid number of command line arguments supplied.";
        cerr << "Only 4 or 5 arguments may be supplied." << endl;
        return 1;
    }
    // initializing input and output streams
    ifstream dictionary(argv[1]);
    ifstream puzzleInput(argv[2]);
    string solution_mode = string(argv[3]);
    string output_mode = string(argv[4]);
    string extra_credit_mode = "";
    vector<string> dictionaryWords;
    vector<int> constraints;
    vector<vector<char>> board;
    vector<vector<string>> searchCombinationsInput;
    vector<vector<string>> searchCombinations;
    vector<vector<string>> finalizedCombinations;
    if (argc == 6) {
        extra_credit_mode = string(argv[5]);
    }
    if (solution_mode != string("one_solution") && solution_mode !=
        string("all_solutions")) {
        cerr << "Invalid argument for solution mode option" << endl;
        return 1;
    }
    if (output_mode != string("count_only") && output_mode !=
        string("print_boards")) {
        cerr << "Invalid argument for output mode option" << endl;
        return 1;
    }
    if (extra_credit_mode != string("gc") && extra_credit_mode != "") {
        cerr << "Invalid argument for extra credit option" << endl;
        return 1;
    }
    /*
     error checking to make sure that input file streams are working correctly
     for dictionary and input
     */
    if (!dictionary.good()) {
        cerr << "Unable to open and read crossword puzzle dictionary file: " <<
        argv[1] <<
        endl << endl;
        return 1;
    }
    if (!puzzleInput.good()) {
        cerr << "Unable to open and read crossword puzzle input file: " <<
        argv[1] <<
        endl << endl;
        return 1;
    }
    parseDictionary(dictionary, dictionaryWords);
    parsePuzzleInput(puzzleInput, constraints, board);
    findWordCombinations(constraints, dictionaryWords, searchCombinationsInput, searchCombinations, finalizedCombinations);
    return 0;
}
