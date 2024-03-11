//
//  constraint.hpp
//  hw6-fresh
//
//  Created by Aditya Behal on 3/25/21.
//  Copyright © 2021 Aditya Behal. All rights reserved.
//

#ifndef constraint_hpp
#define constraint_hpp

#include <stdio.h>

class Constraint {
public:
    // CONSTRUCTORS
    Constraint(unsigned int lengthIn, unsigned int frequencyIn);
    // ACCESSORS
    unsigned int getLength() const { return length_; }
    unsigned int getFrequency() const { return frequency_; }
    // MODIFIERS
    void incrementFrequency() { frequency_++; }
private: // REPRESENTATION (member variables)
    unsigned int length_;
    unsigned int frequency_;
};

// sorting by length of constraint
bool constraintLength(const Constraint& constraint1,
                      const Constraint& constraint2);

#endif /* constraint_hpp */
