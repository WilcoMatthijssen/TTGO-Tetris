#include "point.h"


Point& Point::operator+=(const Point& other){
    this->x += other.x;
    this->y += other.y;
    return *this;
}

Point& Point::operator-=(const Point& other){
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}


Point Point::operator+(const Point& other) const{
    Point answer;
    answer.x = this->x + other.x;
    answer.y = this->y + other.y;
    return answer;
}

Point Point::operator-(const Point& other) const{
    Point answer;
    answer.x = this->x - other.x;
    answer.y = this->y - other.y;
    return answer;
}