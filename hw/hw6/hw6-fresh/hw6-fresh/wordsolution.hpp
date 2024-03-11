//
//  wordsolution.hpp
//  hw6-fresh
//
//  Created by Aditya Behal on 3/25/21.
//  Copyright © 2021 Aditya Behal. All rights reserved.
//

#ifndef wordsolution_hpp
#define wordsolution_hpp

#include <string>
#include <vector>
#include <stdio.h>
#include "wordinput.hpp"
#include "point.hpp"

using namespace std;

class WordSolution {
public:
    // CONSTRUCTORS
    WordSolution(const WordInput& word, const string& typeIn, const Point&
                 successfulSearchStart);
    // ACCESSORS
    const string& getWord() const { return word_; }
    const string& getType() const { return type_; }
    int getLength() const { return length_; }
    const vector<Point>& getPath() const { return path_; }
private: // REPRESENTATION (member variables)
    string word_;
    string type_;
    unsigned int length_;
    vector<Point> path_;
};

// non-member helper sorting function
bool wordLength(const WordSolution& word1, const WordSolution& word2);

#endif /* wordsolution_hpp */
