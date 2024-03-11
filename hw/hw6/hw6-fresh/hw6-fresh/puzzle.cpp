//
//  puzzle.cpp
//  hw6-fresh
//
//  Created by Aditya Behal on 3/25/21.
//  Copyright © 2021 Aditya Behal. All rights reserved.
//

#include "puzzle.hpp"

using namespace std;

// initializing board, rows, and columns based on dimensions of boardIn
Puzzle::Puzzle(vector<vector<char>>& boardIn) {
    board_ = boardIn;
    rows_ = board_.size();
    cols_ = board_[0].size();
}

/* calculating if search across is possible based on length of word and
   search position and boundaries of grid */
bool Puzzle::searchAcrossPossible(const WordInput& word, unsigned int
                        rowSearchIndex, unsigned int colSearchIndex) const {
    if (rowSearchIndex >= rows_ || colSearchIndex >= cols_) {
        return false;
    } else if (colSearchIndex + word.getLength() > cols_) {
        return false;
    } else {
        return true;
    }
}

/* calculating if search down is possible based on length of word and
   search position and boundaries of grid */
bool Puzzle::searchDownPossible(const WordInput& word,
            unsigned int rowSearchIndex, unsigned int colSearchIndex) const {
    if (rowSearchIndex >= rows_ || colSearchIndex >= cols_) {
        return false;
    } else if (rowSearchIndex + word.getLength() > rows_) {
        return false;
    } else {
        return true;
    }
}

// initialzing words that are supposed to be found in this solution grid
void Puzzle::initializePromisedWords(const vector<WordSolution>&
                                     promisedWordsIn) {
    promised_words_ = promisedWordsIn;
}

// accessor function to return promised_words_
const vector<WordSolution>& Puzzle::getPromisedWords() const {
    return promised_words_;
}
