//
//  wordcombination.cpp
//  hw6-fresh
//
//  Created by Aditya Behal on 3/26/21.
//  Copyright © 2021 Aditya Behal. All rights reserved.
//

#include "wordcombination.hpp"

// overloading += operator
WordCombination& WordCombination::operator+= (const WordSolution& solutionWord)
{
    // concatenating string
    combinedWord_ += solutionWord.getWord();
    // appending to vectors
    individualWords_.push_back(solutionWord.getWord());
    type_.push_back(solutionWord.getType());
    // adding total to integers
    length_ += solutionWord.getLength();
    individualWordLength_ = solutionWord.getLength();
    // appending to path vector
    path_.push_back(solutionWord.getPath());
    return *this;
}

// clearing values of private member variables
void WordCombination::clear() {
    combinedWord_ = "";
    individualWords_.clear();
    type_.clear();
    length_ = 0;
    individualWordLength_ = 0;
    path_.clear();
}

// breaking up word combination into its multiple individual word components
vector<WordSolution> WordCombination::splitMultipleWords() const {
    vector<WordSolution> wordSolutions;
    for (unsigned int i = 0; i < individualWords_.size(); i++) {
        wordSolutions.push_back(WordSolution(WordInput(individualWords_[i],
                        individualWords_[i].size()), type_[i], path_[i][0]));
    }
    return wordSolutions;
}

// helper sorting function by length of individual word
bool individualWordLength(const WordCombination& word1, const WordCombination&
                          word2) {
    return (word1.getIndividualLength() < word2.getIndividualLength());
}
