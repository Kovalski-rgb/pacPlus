#pragma once

#include <vector>
#include "axis.h"

class IPathFinder{
    public:

    // Implemented by variations of Pathfinder, should return a vector of size 2, with directions [Y,X] calculated by the function
    virtual std::vector<Axis> turnDirection() = 0;

};