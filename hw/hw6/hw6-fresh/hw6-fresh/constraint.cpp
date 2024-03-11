//
//  constraint.cpp
//  hw6-fresh
//
//  Created by Aditya Behal on 3/25/21.
//  Copyright © 2021 Aditya Behal. All rights reserved.
//

#include "constraint.hpp"

// initializing length and frequency of constraint
Constraint::Constraint(unsigned int lengthIn, unsigned int frequencyIn) {
    length_ = lengthIn;
    frequency_ = frequencyIn;
}

// sorting by length of constraint
bool constraintLength(const Constraint& constraint1, const Constraint&
                      constraint2) {
    return (constraint1.getLength() < constraint2.getLength());
}
