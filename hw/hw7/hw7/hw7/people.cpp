//
//  people.cpp
//  hw7
//
//  Created by Aditya Behal on 3/30/21.
//  Copyright © 2021 Aditya Behal. All rights reserved.
//

#include "people.hpp"

using namespace std;

// default constructor
People::People(const string& firstNameIn, const string& lastNameIn) {
    first_name_ = firstNameIn;
    last_name_ = lastNameIn;
}

// sorting names alphabetically
bool operator< (const People& person1, const People& person2) {
    return (person1.last() < person2.last() || (person1.last() == person2.last()
            && person1.first() < person2.first()));
}
