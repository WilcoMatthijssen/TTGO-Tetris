#pragma once
#include <Arduino.h>

struct Point2D{
    int8_t x, y;

    Point2D& operator+=(const Point2D& other);

    Point2D& operator-=(const Point2D& other);

    Point2D operator+(const Point2D& other) const;

    Point2D operator-(const Point2D& other) const;

};