//
//  costume.hpp
//  hw7
//
//  Created by Aditya Behal on 3/30/21.
//  Copyright © 2021 Aditya Behal. All rights reserved.
//

#ifndef costume_hpp
#define costume_hpp

#include <string>
#include <stdio.h>

using namespace std;

class Costume {
public:
    // CONSTRUCTORS
    Costume(const string& costumeNameIn);
    // ACCESSORS
    const string& name() const { return costume_name_; }
private: // REPRESENTATION (member variables)
    string costume_name_;
};

// overloading operator < for alphabetical sorting
bool operator< (const Costume& costume1, const Costume& costume2);

#endif /* costume_hpp */
