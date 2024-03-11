//
//  point.hpp
//  hw6
//
//  Created by Aditya Behal on 3/21/21.
//  Copyright © 2021 Aditya Behal. All rights reserved.
//

#ifndef point_hpp
#define point_hpp

#include <stdio.h>

class Point {
public:
    Point (unsigned int xIn, unsigned int yIn) : x(xIn), y(yIn) {}
    unsigned int x, y;
};

#endif /* point_hpp */
