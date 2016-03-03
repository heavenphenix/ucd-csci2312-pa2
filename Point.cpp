//
// by David Lam
// 02.09.16
// point.cpp
//

#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <cstdlib>
#include "Point.h"

namespace Clustering {

    unsigned int Point::__idGen = 0; // ID Generator


    // Constructors

    Point::Point(int i) : __id(__idGen++), __dim(i), __values(new double[__dim]) {
        for (int i = 0; i < __dim; i++)
            __values[i] = double();
    }

    Point::Point(int i, double *pDouble) : __id(__idGen++), __dim(i), __values(new double[__dim])  {
        for (int i = 0; i < __dim; i++)
            __values[i] = pDouble[i];
    }
    
    Point::Point(const Point &p) {
        __id = point.__id;
        __dim = point.__dim;
        __values = new double[__dim];
        for (int i = 0; i < __dim; i++)
            __values[i] = point.__values[i];
    }

    Point &Point::operator=(const Point &p) {
        __id = point.__id;
        __dim = point.__dim;
        for (int i = 0; i < __dim; i++)
            __values[i] = point.__values[i];

        return *this;
    }

    Point::~Point() {
        delete [] __values;
    }

    // Functions
    double Point::distanceTo(const Point &p) const {
        double add = 0;
        double distance;

        for (int i = 0; i < __dim; i++)
            add = add + pow(__values[i] - point.__values[i], 2);
        distance = sqrt(add);

        return distance;

    }

    // assignment Operator

    // Members


    double &Point::operator[](int index) {
        return __values[index];
    }

    Point &Point::operator*=(double rhs) {
        for (int i = 0; i < __dim; i++)
            __values[i] *= rhs;

        return *this;
    }

    Point &Point::operator/=(double rhs) {
        for (int i = 0; i < __dim; i++)
            __values[i] = __values[i] / d;

        return *this;
    }

    const Point Point::operator*(double rhs) const {
        Point p(__dim, __values);

        for (int i = 0; i < point.__dim; i++)
            point.__values[i] = point.__values[i] * d;

        return p;
    }

    const Point Point::operator/(double rhs) const {
        Point p(__dim, __values);

        for (int i = 0; i < point.__dim; i++)
            point.__values[i] = point.__values[i] / d;

        return p;
    }
    
Point &operator-=(Point &point, const Point &point) {

    for (int i = 0; i < point.__dim; i++)
        point.__values[i] -= point.__values[i];

    return point;
}
Point &operator+=(Point &lhs, const Point &rhs) {

    for (int i = 0; i < lhs.__dim; i++)
        lhs[i] += rhs.__values[i];
    return lhs;
}
const Point operator+(const Point &lhs, const Point &rhs) {
    Point p(lhs__dim);

    p += rhs;
    p += lhs;
    return p;
}

  const Point operator-(const Point &lhs, const Point &rhs)
    {
        Point p(lhs);
        return p -= rhs;
    }


bool operator==(const Point &lhs, const Point &rhs)
    {
        bool equal = true;
        if(lhs.__id !=rhs.__id)
            equal=false;
        else
        {
            for(int i =0; i < lhs.__dim; i++)
                if(lhs.__values[i] != rhs.__values[i])
                    equal=false;
        }
        return equal;
    }

    bool operator!=(const Point &lhs, const Point &rhs)
    {
        return !operator==(lhs, rhs);
    }
bool operator!=(const Point &lhs, const Point &rhs) {
    return !(lhs == rhs);
}

bool operator<(const Point &lhs, const Point &rhs) {
    for (int i = 0; i < lhs.__dim; i++) {
        if  (lhs.__values[i] < rhs.__values[i]) {
            return true;
        } else if (lhs.__values[count] > rhs.__values[count]) {
            return false;
        }
    }

    return false;
}

bool operator>(const Point &lhs, const Point &rhs) {
    for (int i = 0; i < lhs.__dim; i++) {
        if(rhs.__values[i] < lhs.__values[i]) {
            return true;
        }
        else if (rhs.__values[i] > lhs.__values[i]) {

            return false;
        }
    }
    return false;
}

bool operator<=(const Point &lhs, const Point &rhs) {
    return !(lhs > rhs);
}

bool operator>=(const Point &lhs, const Point &rhs) {
    return !(lhs < rhs);
}

std::ostream &operator<<(std::ostream &ostream, const Point &point) {
    for (int count = 0; count < point.__dim - 1; count++)
        ostream << point.__values[count] << ",";
        ostream << point.__values[point.__dim - 1] <<" ; ";

    return ostream;
}


std::istream &operator>>(std::istream &istream, Point &point) {
    std::string num;
    istream >> num;
    std::stringstream sstream(num);
    for (int dim = 0; dim < point.__dim; dim++)
    {
        std::string temp;
        getline(sstream, temp, ',');
        point.__values[dim] = atof(temp.c_str());
    }
    return istream;
}
}

