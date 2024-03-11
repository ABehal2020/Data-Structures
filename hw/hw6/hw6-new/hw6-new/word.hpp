//
//  word.hpp
//  hw6-new
//
//  Created by Aditya Behal on 3/23/21.
//  Copyright © 2021 Aditya Behal. All rights reserved.
//

#ifndef word_hpp
#define word_hpp

#include <stdio.h>
#include <string>
#include "point.hpp"

using namespace std;

class Word {
public:
    Word (const string& wordIn, const unsigned int direction, const Point& pointIn);
    const string& getWord() const { return word_; }
    const unsigned int getDirection() const { return direction_; }
    const Point& getPoint() const { return point_; }
private:
    string word_;
    unsigned int direction_;
    Point point_;
};

bool operator==(const Word& word1, const Word& word2);

#endif /* word_hpp */
