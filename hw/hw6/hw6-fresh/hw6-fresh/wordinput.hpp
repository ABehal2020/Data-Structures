//
//  wordinput.hpp
//  hw6-fresh
//
//  Created by Aditya Behal on 3/25/21.
//  Copyright © 2021 Aditya Behal. All rights reserved.
//

#ifndef wordinput_hpp
#define wordinput_hpp

#include <stdio.h>
#include <string>

using namespace std;

class WordInput {
public:
    // CONSTRUCTORS
    WordInput(const string& wordIn, unsigned int lengthIn);
    // ACCESSORS
    const string& getWord() const { return word_; }
    unsigned int getLength() const { return length_; }
private: // REPRESENTATION (member variables)
    string word_;
    unsigned int length_;
};

#endif /* wordinput_hpp */
