//
//  word.cpp
//  hw6-new
//
//  Created by Aditya Behal on 3/23/21.
//  Copyright © 2021 Aditya Behal. All rights reserved.
//

#include "word.hpp"

using namespace std;

Word::Word (const string& wordIn, const unsigned int directionIn, const Point& pointIn) :
point_(pointIn) {
    word_ = wordIn;
    direction_ = directionIn;
}

bool operator==(const Word& word1, const Word& word2) {
    return (word1.getWord() == word2.getWord() && word1.getDirection() ==
            word2.getDirection() && word1.getPoint() == word2.getPoint());
}
