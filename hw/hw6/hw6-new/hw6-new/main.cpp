//
//  main.cpp
//  hw6-new
//
//  Created by Aditya Behal on 3/23/21.
//  Copyright © 2021 Aditya Behal. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include "word.hpp"

using namespace std;

/*
// sorting by length of word
bool wordLength(const string& word1, const string& word2) {
    return (word1.size() < word2.size());
}
*/

void parseDictionary(ifstream& dictionary, vector<string>& dictionaryWords) {
    string word;
    while (dictionary >> word) {
        dictionaryWords.push_back(word);
    }
    // sort(dictionaryWords.begin(), dictionaryWords.end(), wordLength);
    cout << "debug" << endl;
}

void parsePuzzleInput(ifstream& puzzleInput, vector<vector<int>>& constraints, vector<vector<char>>& board) {
    string puzzleLine;
    vector<char> puzzleLineVector;
    vector<int> constraint;
    bool found = false;
    while (puzzleInput >> puzzleLine) {
        if (puzzleLine[0] == '!') {
            continue;
        } else if (puzzleLine[0] == '+') {
            string constraintLength = puzzleLine.substr(1);
            for (unsigned int i = 0; i < constraints.size(); i++) {
                if (stoi(constraintLength) == constraints[i][0]) {
                    constraints[i][1]++;
                    found = true;
                    break;
                }
            }
            if (!found) {
                constraint.push_back(stoi(constraintLength));
                constraint.push_back(1);
                constraints.push_back(constraint);
                constraint.clear();
            }
            found = false;
        } else {
            for (string::iterator itr = puzzleLine.begin(); itr != puzzleLine.end(); itr++) {
                puzzleLineVector.push_back(*itr);
            }
            board.push_back(puzzleLineVector);
            puzzleLineVector.clear();
        }
    }
    sort(constraints.rbegin(), constraints.rend());
    cout << "debug" << endl;
}

void rotateBoard (const vector<vector<char>>& board, vector<vector<char>>& boardRotated, const int numBoardRows, const int numBoardCols) {
    unsigned int i = 0;
    unsigned int j = 0;
    while (i < numBoardCols) {
        vector<char> flip;
        while (j < numBoardRows) {
            flip.push_back(board[j][i]);
            j++;
        }
        boardRotated.push_back(flip);
        i++;
    }
}

bool dictFound(const string& wordSearch, const vector<string>& dictionaryWords) {
    unsigned int i = 0;
    while (i < dictionaryWords.size()) {
        if (wordSearch == dictionaryWords[i]) {
            return true;
        }
        i++;
    }
    return false;
}

void recursiveSearch(const string& wordSearch, const unsigned int rowNum, unsigned int& startPos, unsigned int& length, const unsigned int direction, vector<Word>& wordsFound, const vector<string>& dictionaryWords) {
    string wordPart = wordSearch.substr(startPos, length);
    if (direction == 0 && dictFound(wordPart, dictionaryWords)) {
        wordsFound.push_back(Word(wordPart, 0, Point(rowNum, startPos)));
    } else if (direction == 1 && dictFound(wordPart, dictionaryWords)) {
        wordsFound.push_back(Word(wordPart, 0, Point(startPos, rowNum)));
    }
    
    if (startPos > wordSearch.size() - 3) {
        return;
    }
    
    if (startPos + length + 1 > wordSearch.size()) {
        length = 3;
        startPos = startPos + 1;
        recursiveSearch(wordSearch, rowNum, startPos, length, direction, wordsFound, dictionaryWords);
    } else if (startPos + length - 1 < wordSearch.size()) {
        length = length + 1;
        recursiveSearch(wordSearch, rowNum, startPos, length, direction, wordsFound, dictionaryWords);
    }
}

void horizontalSearch(const vector<vector<char>>& board, unsigned int direction, vector<Word>& wordsFound, const vector<string>& dictionaryWords) {
    unsigned int startPos = 0;
    unsigned int rowNum;
    unsigned int length = 3;
    direction = 0;
    unsigned int i = 0;
    while (i < board.size()) {
        string wordSearch(board[i].begin(), board[i].end());
        rowNum = i;
        recursiveSearch(wordSearch, rowNum, startPos, length, direction, wordsFound, dictionaryWords);
    }
}

void verticalSearch(const vector<vector<char>>& boardRotated, unsigned int direction, vector<Word>& wordsFound, const vector<string>& dictionaryWords) {
    unsigned int startPos = 0;
    unsigned int rowNum;
    unsigned int length = 3;
    direction = 1;
    unsigned int i = 0;
    while (i < boardRotated.size()) {
        string wordSearch(boardRotated[i].begin(), boardRotated[i].end());
        rowNum = i;
        recursiveSearch(wordSearch, rowNum, startPos, length, direction, wordsFound, dictionaryWords);
    }
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
    vector<vector<int>> constraints;
    vector<vector<char>> board;
    vector<vector<char>> boardRotated;
    vector<Word> wordsFound;
    unsigned int wordType;
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
    unsigned int numBoardRows = board.size();
    unsigned int numBoardCols = board[0].size();
    
    vector<unsigned int> boardSize;
    boardSize.push_back(0);
    boardSize.push_back(numBoardRows);
    boardSize.push_back(0);
    boardSize.push_back(numBoardCols);
    
    rotateBoard(board, boardRotated, numBoardRows, numBoardCols);
    horizontalSearch(board, wordType, wordsFound, dictionaryWords);
    verticalSearch(boardRotated, wordType, wordsFound, dictionaryWords);
    
    return 0;
}
