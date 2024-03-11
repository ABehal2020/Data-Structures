//
//  point.hpp
//  hw6-fresh
//
//  Created by Aditya Behal on 3/25/21.
//  Copyright © 2021 Aditya Behal. All rights reserved.
//

#ifndef point_hpp
#define point_hpp

#include <stdio.h>

class Point {
public:
    // CONSTRUCTORS
    Point(unsigned int xIn, unsigned int yIn) : x(xIn), y(yIn) {}
    // REPRESENTATION (member variables)
    unsigned int x;
    unsigned int y;
};

#endif /* point_hpp */
