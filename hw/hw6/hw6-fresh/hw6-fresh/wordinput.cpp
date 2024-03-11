//
//  wordinput.cpp
//  hw6-fresh
//
//  Created by Aditya Behal on 3/25/21.
//  Copyright © 2021 Aditya Behal. All rights reserved.
//

#include "wordinput.hpp"

using namespace std;

// initializing word and its length 
WordInput::WordInput(const string& wordIn, unsigned int lengthIn) {
    word_ = wordIn;
    length_ = lengthIn;
}
