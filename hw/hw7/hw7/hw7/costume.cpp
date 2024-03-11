//
//  costume.cpp
//  hw7
//
//  Created by Aditya Behal on 3/30/21.
//  Copyright © 2021 Aditya Behal. All rights reserved.
//

#include "costume.hpp"

using namespace std;

// default constructor
Costume::Costume(const string& costumeNameIn) {
    costume_name_ = costumeNameIn;
}

// sorting names alphabetically
bool operator< (const Costume& costume1, const Costume& costume2) {
    return (costume1.name() < costume2.name());
}
