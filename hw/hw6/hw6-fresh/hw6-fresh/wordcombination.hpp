//
//  wordcombination.hpp
//  hw6-fresh
//
//  Created by Aditya Behal on 3/26/21.
//  Copyright © 2021 Aditya Behal. All rights reserved.
//

#ifndef wordcombination_hpp
#define wordcombination_hpp

#include <string>
#include <vector>
#include <stdio.h>
#include "wordinput.hpp"
#include "wordsolution.hpp"
#include "point.hpp"

using namespace std;

class WordCombination {
public:
    // CONSTRUCTORS
    WordCombination() : length_(0), individualWordLength_(0) {}
    // ACCESSORS
    const string& getCombinedWord() const { return combinedWord_; }
    int getIndividualLength() const { return individualWordLength_; }
    vector<WordSolution> splitMultipleWords() const;
    // MODIFIERS
    WordCombination& operator+= (const WordSolution& solutionWord);
    void clear();
private: // REPRESENTATION (member variables)
    string combinedWord_;
    vector<string> individualWords_;
    vector<string> type_;
    unsigned int length_;
    unsigned int individualWordLength_;
    vector<vector<Point> > path_;
};

// non-member helper sorting function
bool individualWordLength(const WordCombination& word1, const WordCombination&
                          word2);

#endif /* wordcombination_hpp */
