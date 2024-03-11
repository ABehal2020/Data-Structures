//
//  wordsolution.cpp
//  hw6-fresh
//
//  Created by Aditya Behal on 3/25/21.
//  Copyright © 2021 Aditya Behal. All rights reserved.
//

#include "wordsolution.hpp"

/* initializing word, length, and type and path using starting point and
   word length */
WordSolution::WordSolution(const WordInput& word, const string& typeIn, const
                           Point& successfulSearchStart) {
    word_ = word.getWord();
    length_ = word.getLength();
    type_ = typeIn;
    path_.push_back(successfulSearchStart);
    Point addPoint = successfulSearchStart;
    if (typeIn == "across") {
        for (int i = length_ - 1; i > 0; i--) {
            addPoint.y++;
            path_.push_back(addPoint);
        }
    } else if (typeIn == "down") {
        for (int i = length_ - 1; i > 0; i--) {
            addPoint.x++;
            path_.push_back(addPoint);
        }
    }
}

// sorting by length of word and then alphabetical ordering to break any ties
bool wordLength(const WordSolution& word1, const WordSolution& word2) {
    return (word1.getLength() < word2.getLength() || (word1.getLength() ==
                    word2.getLength() && word1.getWord() < word2.getWord()));
}
