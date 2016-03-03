//
// by David Lam
// 02.09.16
// cluster.cpp
//

#include <iostream>
#inlcude <sstream>
#include <algorithm>
#include <string>
#include "Point.h"
#include "Cluster.h"

using namespace std;
using namespace Clustering;
namespace Clustering {

    // LNode Constructor
    LNode::LNode(const Point &p, LNodePtr n) : point(p), next(n) {}

    // The big three:
    // copy constructor
    Cluster::Cluster(const Cluster & clusterA){

        __size = 0;
        __pointA = nullptr;

        if(clusterA.__pointA == nullptr)
        {
            if(clusterA.__size == 0)
                __pointA = nullptr;
        }
        else
        {
            LNodePtr currNode = clusterA.__pointA;

            while (currNode != nullptr){

                add(currNode->pointA);

                currNode = currNode->next;
            }
        }
    }

    //  overloaded operator=
    Cluster & Cluster::operator=(const Cluster &rhs){


        if(this == &rhs)
            return *this;

        LNodePtr curr = __pointA;
        LNodePtr next;


        while (curr != nullptr) {

            next = curr->next;
            delete curr;
            curr = next;
            __size--;

        }

        __size = 0;
        __pointA = nullptr;

        LNodePtr rhs_ptr = rhs.__pointA;


        for (int index = 0; index < rhs.getSize() ; ++index) {

            add(rhs_ptr->pointA);

            rhs_ptr = rhs_ptr->next;
        }

        return *this;
    }

    // Destructor
    Cluster::~Cluster(){

        LNodePtr curr;
        while (__pointA != nullptr)
        {

            curr = __pointA;
            __pointA = curr->next;

            delete curr;
        }

        // Size Count
        int Cluster::getSize() const {
            return __size;
        }

        // Functions

        // Add Point
        void Cluster::add(const Point &point) {
            LNodePtr newNode = new LNode(point ,nullptr);
            LNodePtr curr;
            LNodePtr previous;
            newNode->pointA = point;

            if (__pointA == nullptr) {
                __pointA = newNode;
                newNode->next = nullptr;
            }
            else if (pointA->point > point){
                newNode->next = pointA;
                __pointA = newNode;
            }
            else {
                previous = __pointA;
                curr = __pointA->next;

                while (true) {
                    if (curr == nullptr || curr->point > point) {
                        previous->next = newNode;
                        newNode->next = curr;
                        break;
                    }
                    previous = curr;
                    curr = curr->next;
                }
            }
            __size++;
        }

        // Remove Point
        const Point &Cluster::remove(const Point &point) {
            LNodePtr temp;
            LNodePtr previous = __pointA;

            if (__pointA == nullptr)
                return point;

            if (__pointA->point == point) {
                temp = __pointA->next;
                delete __pointA;
                __pointA = temp;
            } else {
                temp = __pointA;
                while ((temp != nullptr) && (temp->point != point)) {
                    previous = temp;
                    temp = temp->next;
                }
                if (temp) {
                    previous->next = temp->next;
                    delete temp;
                }
            }
            __size--;

            return point;
        }

        // Point in *this
        bool Cluster::contains(const Point &point) {
            LNodePtr temp = __pointA;

            while (temp != nullptr) {
                if (temp->point == point) {
                    return true;
                }
                temp = temp->next;
            }

            return false;
        }

        // Sort Cluster
        void Cluster::sort() {
        }


        // Overloaded operators

        // Members
        const Point &Cluster::operator[](unsigned int index) const
        {
            LNodePtr cursor = __pointA;

            if (cursor != NULL)
            {
                for (int i=0; i<index; i++)
                {
                    cursor = cursor->next;
                }
            }
            return cursor->point;

        }


        Cluster &Cluster::operator+=(const Point &more)
        {
            LNodePtr cursor = __pointA;
            cursor->point += more;
        }

        Cluster &Cluster::operator-=(const Point &less)
        {
            LNodePtr cursor = __pointA;
            cursor->point -= less;
        }

        // union
        Cluster &Cluster::operator+=(const Cluster &)
        {

        }

        // difference
        Cluster &Cluster::operator-=(const Cluster &)
        {

        }

    // FRIEND FUNCTION

    // Equality
    bool operator==(const Cluster &lhs, const Cluster &rhs) {
        LNodePtr temp0 = lhs.__pointA;
        LNodePtr temp1 = rhs.__pointA;

        while (true) {
            if ((temp0 == nullptr) && (temp2 == nullptr))
                return true;

            if ((temp0 == nullptr) || (temp2 == nullptr))
                return false;

            if ((temp0->point) != (temp2->point))
                return false;

            temp0 = temp0->next;
            temp1 = temp1->next;
        }
    }

    // Inequality
    bool operator!=(const Cluster &lhs, const Cluster &rhs) {
        return !(lhs == rhs);
    }

    const Cluster operator+(const Cluster &c, const Point &p) {
        Cluster temp = c;

        temp.add(p);

        return temp;
    }

    const Cluster operator-(const Cluster &c, const Point &p) {
        Cluster temp = c;

        temp.remove(p);

        return temp;
    }

    const Cluster operator+(const Cluster &lhs, const Cluster &rhs) {
        Cluster temp(lhs);

        temp += rhs;

        return temp;
    }
        
    const Cluster operator-(const Cluster &lhs, const Cluster &rhs) {
        Cluster temp(lhs);

        temp -= rhs;

        return temp;
    }
}
std::ostream &operator<<(std::ostream &ostream, const Cluster &c1)
{
    LNodePtr cursor=c1.__pointA;
    for(int count = 0; count < c1.__size; count++)
    {
        ostream << cursor->point << std::endl;
        cursor = cursor->next;
    }
    return ostream;
}

std::istream &operator>>(std::istream &input, Cluster &c1)
{
    std::string line;
    while (getline(input,line)) {

        if (line.empty()) {
            return input;
        }

        int count = std::count(line.begin(), line.end(), ',');
        Point ptr(count + 1);

        std::istringstream ss(line);
        ss >> ptr;

        c1.add(ptr);
    }
    return input;
}

}
