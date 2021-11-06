#include "point2d.h"


Point2D& Point2D::operator+=(const Point2D& other){
    this->x += other.x;
    this->y += other.y;
    return *this;
}

Point2D& Point2D::operator-=(const Point2D& other){
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}


Point2D Point2D::operator+(const Point2D& other) const{
    Point2D answer;
    answer.x = this->x + other.x;
    answer.y = this->y + other.y;
    return answer;
}

Point2D Point2D::operator-(const Point2D& other) const{
    Point2D answer;
    answer.x = this->x - other.x;
    answer.y = this->y - other.y;
    return answer;
}