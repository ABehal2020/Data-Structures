//
//  point.cpp
//  hw6-new
//
//  Created by Aditya Behal on 3/23/21.
//  Copyright © 2021 Aditya Behal. All rights reserved.
//

#include "point.hpp"

bool operator==(const Point& point1, const Point& point2) {
    return (point1.x == point2.x && point1.y == point2.y);
}
