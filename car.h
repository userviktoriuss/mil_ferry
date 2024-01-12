#ifndef CAR_H
#define CAR_H


#include <string>

using std::string;

struct Car {
    string call;
    double X, Y;
    double width, length;
    string position;

    Car(string call, double X, double Y, double width, double length, string position="") {
        this->call = call;
        this->X = X;
        this->Y = Y;
        this->width = width;
        this->length = length;
        this->position = position;
    }
};

#endif // CAR_H
