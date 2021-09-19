#pragma once
#include <Arduino.h>

struct Point{
    int8_t x, y;

    Point& operator+=(const Point& other);

    Point& operator-=(const Point& other);

    Point operator+(const Point& other) const;

    Point operator-(const Point& other) const;

};