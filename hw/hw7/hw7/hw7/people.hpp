//
//  people.hpp
//  hw7
//
//  Created by Aditya Behal on 3/30/21.
//  Copyright © 2021 Aditya Behal. All rights reserved.
//

#ifndef people_hpp
#define people_hpp

#include <string>
#include <stdio.h>

using namespace std;

class People {
public:
    // CONSTRUCTORS
    People(const string& firstNameIn, const string& lastNameIn);
    // ACCESSORS
    const string& first() const { return first_name_; };
    const string& last() const { return last_name_; };
private: // REPRESENTATION (member variables)
    string first_name_;
    string last_name_;
};

// overloading operator < for alphabetical sorting
bool operator< (const People& person1, const People& person2);

#endif /* people_hpp */
