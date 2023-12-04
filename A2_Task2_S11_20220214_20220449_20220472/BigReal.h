#include <iostream>
using namespace std;

#ifndef OOP_A2_BIGREAL_H
#define OOP_A2_BIGREAL_H


class BigReal {
private:
    char sign;
    string number,integer,fraction;
public:
    BigReal(string real);
    BigReal();
    bool isValidReal(string realNumber);
    bool operator== (BigReal realEqual);
    bool operator> (BigReal realGreater);
    bool operator< (BigReal realSmaller);
    BigReal operator+(BigReal& other);
    BigReal operator-(BigReal& other);
    void padding(BigReal realPad);
    friend ostream& operator << (ostream& out, const BigReal& num);

};


#endif //OOP_A2_BIGREAL_H