#pragma once
#include "../common.h"
#include <cmath>

struct Point
{
    int16_t x;
    int16_t z;

    Point() {}
    Point(int16_t _x, int16_t _z) : x(_x), z(_z) {}
};

bool doOverlap(Point l1, Point r1, Point l2, Point r2)
{
    if (l1.x > r2.x || l2.x > r1.x) {
        return false;
    }

    // inverse logic cuz of axis directions
    if (r1.z < l2.z || r2.z < l1.z) {
        return false;
    }

    return true;
}

uint16_t distanceBetweenTwoPoints(Point p1, Point p2)
{
    return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.z - p1.z, 2));
}

uint16_t distanceScalar(uint16_t p1, uint16_t p2)
{
    return std::abs(p2 - p1);
}