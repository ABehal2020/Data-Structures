//
//  point.hpp
//  hw6-new
//
//  Created by Aditya Behal on 3/23/21.
//  Copyright © 2021 Aditya Behal. All rights reserved.
//

#ifndef point_hpp
#define point_hpp

#include <stdio.h>

class Point {
public:
    Point (unsigned int xIn, unsigned int yIn) : x(xIn), y(yIn) {}
    unsigned int x;
    unsigned int y;
};

bool operator==(const Point& point1, const Point& point2);

#endif /* point_hpp */
