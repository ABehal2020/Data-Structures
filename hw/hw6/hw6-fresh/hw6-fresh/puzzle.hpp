//
//  puzzle.hpp
//  hw6-fresh
//
//  Created by Aditya Behal on 3/25/21.
//  Copyright © 2021 Aditya Behal. All rights reserved.
//

#ifndef puzzle_hpp
#define puzzle_hpp

#include <stdio.h>
#include <vector>
#include "wordinput.hpp"
#include "wordsolution.hpp"

using namespace std;

class Puzzle {
public:
    // CONSTRUCTORS
    Puzzle(vector<vector<char> >& boardIn);
    // ACCESSORS
    unsigned int getRows() const { return rows_; }
    unsigned int getCols() const { return cols_; }
    const vector<vector<char> >& getBoard() const { return board_; }
    bool searchAcrossPossible(const WordInput& word, unsigned int rowSearchIndex
                              , unsigned int colSearchIndex) const;
    bool searchDownPossible(const WordInput& word, unsigned int rowSearchIndex,
                            unsigned int colSearchIndex) const;
    const vector<WordSolution>& getPromisedWords() const;
    // MODIFIERS
    void initializePromisedWords(const vector<WordSolution>& promisedWordsIn);
private: // REPRESENTATION (member variables)
    vector<vector<char> > board_;
    vector<WordSolution> promised_words_;
    unsigned int rows_;
    unsigned int cols_;
};

#endif /* puzzle_hpp */
