#include "hw2.h"

//
//  Point.cpp
//  HW2
//
//  Created by Alan Zhong on 6/11/19.
//  Copyright © 2019 Alan Zhong. All rights reserved.
//


Point::Point() : x(0), y(0), z(0) {}

Point::Point(double xIn, double yIn) : x(xIn), y(yIn), z(0) {}

Point::Point(double xIn, double yIn, double zIn) : x(xIn), y(yIn), z(zIn) {}

Point::Point(const Point &other) : x(other.getX()), y(other.getY()), z(other.getZ()) {}

inline double Point::getX() const {
    return this->x;
}

inline double Point::getY() const {
    return this->y;
}

inline double Point::getZ() const {
    return this->z;
}

inline void Point::setX(double xIn) {
    x = xIn;
}

inline void Point::setY(double yIn) {
    y = yIn;
}

inline void Point::setZ(double zIn) {
    z = zIn;
}

inline void Point::setXY(double xIn, double yIn) {
    x = xIn;
    y = yIn;
}

inline void Point::setXYZ(double xIn, double yIn, double zIn) {
    x = xIn;
    y = yIn;
    z = zIn;
}

void Point::print() const {
    std::cout << "(" << getX() << ", " << getY() << ", " << getZ() << ")\n";
}

std::ostream& operator<<(std::ostream &out, const Point &other) {
    out << "(" << other.getX() << ", " << other.getY() << ", " << other.getZ() << ")\n";
    return out;
}

std::istream& operator>>(std::istream &in, Point &other) {
    std::string xHolder, yHolder, zHolder;
    in >> xHolder >> yHolder >> zHolder;
    other = Point(stod(xHolder), stod(yHolder), stod(zHolder));
    return in;
}

double Point::distance() const {
    return sqrt(pow(getX(), 2) + pow(getY(), 2) + pow(getZ(), 2));
}

double Point::distance(const Point &other) const {
    return sqrt(pow(x-other.getX(),2) + pow(y-other.getY(),2) + pow(z-other.getZ(),2));
}

double Point::distSquared(const Point &other) const {
    return pow(x-other.getX(),2) + pow(y-other.getY(),2) + pow(z-other.getZ(),2);
}

bool Point::origin() const{
    return (getX() == 0 && getY() == 0 && getZ() == 0);
}

bool Point::line(const Point &other) const {
    double magnitude = sqrt(pow(getX(),2) + pow(getY(),2) + pow(getZ(),2));
    Point normalized = Point(getX()/magnitude, getY()/magnitude, getZ()/magnitude);
    double otherMag = sqrt(pow(other.getX(),2) + pow(other.getY(),2) + pow(other.getZ(),2));
    Point otherNorm = Point(other.getX()/otherMag, other.getY()/otherMag, other.getZ()/otherMag);
    return normalized.getX() == otherNorm.getX() && normalized.getY() == otherNorm.getY() && normalized.getZ() == otherNorm.getZ();
}

Point Point::cross(const Point &other) const {
    return Point(getY()*other.getZ() - getZ()*other.getY(), -(getZ()*other.getX() - getX()*other.getZ()), getX()*other.getY() - getY()*other.getX());
}

Point operator+ (const Point &a, const Point &b) {
    Point C = Point(a.getX() + b.getX(), a.getY() + b.getY(), a.getZ() + b.getZ());
    return C;
}

Point operator- (const Point &a, const Point &b) {
    Point C = Point(a.getX() - b.getX(), a.getY() - b.getY(), a.getZ() - b.getZ());
    return C;
}

// Precondition: ar must have exactly 3 elements inside
bool plane(Point ar[], const Point &target) {
    Point u = ar[1] - ar[0];
    Point v = ar[2] - ar[0];
    Point cross = u.cross(v);
    std::cout << cross.getX() << "(x - " << ar[0].getX() << ") - " << cross.getY() << "(y - " << ar[0].getY() << ") + " << cross.getZ() << "(z - " << ar[0].getZ() << ") = 0" << std::endl;
    if (cross.getX()*(target.getX() - ar[0].getX()) - cross.getY()*(target.getY() - ar[0].getY()) + cross.getZ()*(target.getZ() - ar[0].getZ()) != 0) {
        return false;
    }
    return true;
}



bool square(Point ar[], size_t size) {
    for (int i = 0; i < size - 3; i++) {
        for (int j = i + 1; j < size - 2; j++) {
            for (int k = j + 1; k < size - 1; k++) {
                for (int l = k + 1; l < size; l++) {
                    if(isSquare(ar[i], ar[j], ar[k], ar[l])) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool isSquare(const Point &p1, const Point &p2, const Point &p3, const Point &p4) {
    Point ar[3] = {p1, p2, p3};
    if (!plane(ar, p4)) {
        return false;
    }
    double dist12 = p1.distance(p2);
    double dist13 = p1.distance(p3);
    double dist14 = p1.distance(p4);
    std::cout << "dist12: " << dist12 << " dist13: " << dist13 << " dist14: " << dist14 << std::endl;
    std::cout << "dist42: " << p4.distance(p2) << " dist43: " << p4.distance(p3) << " dist23: " << p2.distance(p3) << std::endl;
    
    if (dist12 == dist13  && 2*p1.distSquared(p2) == p1.distSquared(p4)) {
        //int dist = pow(p2.distance(p4),2);
        return (p2.distance(p4) == dist12 && p3.distance(p4) == dist12 && dist14 == p2.distance(p3));
    }
    
    if (dist13 == dist14 && 2*p1.distSquared(p3) == p1.distSquared(p2)) {
        //int dist = pow(p2.distance(p3),2);
        return (dist13 == p2.distance(p3) && dist13 == p2.distance(p4) && dist12 == p3.distance(p4));
    }
    
    if (dist12 == dist14 && 2*p1.distSquared(p2) == p1.distSquared(p3)) {
        //int dist = pow(p2.distance(p3),2);
        return (dist12 == p3.distance(p4) && dist12 == p3.distance(p2) && dist13 == p2.distance(p4));
    }
    
    return false;
}

Point centroid(Point ar[], size_t size) {
    if (size == 0) {
        return Point(0, 0, 0);
    }
    double cenX = 0;
    double cenY = 0;
    double cenZ = 0;
    for (int i = 0; i < size; i++) {
        cenX += ar[i].getX();
        cenY += ar[i].getY();
        cenZ += ar[i].getZ();
    }
    cenX = cenX / size;
    cenY = cenY / size;
    cenZ = cenZ / size;
    return Point(cenX, cenY, cenZ);
}

// Put your functions/prototype here




