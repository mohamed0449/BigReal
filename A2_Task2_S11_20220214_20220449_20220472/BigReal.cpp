#include "BigReal.h"
#include <iostream>
#include <regex>
using namespace std;

BigReal::BigReal(){
    sign =' ';
    number = "0.0";
    integer = "0";
    fraction = "0";
}



BigReal::BigReal(string real) {
    if (isValidReal(real)) {
        if (real[0] == '-') {
            sign = '-';
            real[0] = '0';
        } else if (real[0] == '+') {
            sign = '+';
            real[0] = '0';
        }
        else if(isdigit(real[0]) || real[0]=='.'){
            sign=' ';
            if(real[0]=='.'){
                integer="";
            }
        }
        number = real;
        if(real.find('.')==string::npos){
            integer=number;
            fraction="";
        }
        else{
            integer = real.substr(0, real.find('.'));
            fraction = real.substr(integer.size() + 1, real.size() - 1);
        }
    }
}

bool BigReal::isValidReal(string number) {
    while(!(regex_match(number,regex("[+-]?\\d*\\.?\\d*"))))
    {
        cout<<"Invalid. Enter again please: ";
        cin>>number;
    }
    return true;
}

bool BigReal::operator==(BigReal realEqual) {
    this->padding(realEqual);
    if(sign==realEqual.sign || (sign==' '&&realEqual.sign=='+') || (sign='+'&&realEqual.sign==' ')){
        for(int i=0;i<number.length();i++){
            if(number[i]!=realEqual.number[i]){
                return false;
            }
        }
    }
    return true;
}



bool BigReal::operator>(BigReal realGreater) {
    this->padding(realGreater);//-3.5 -2.5 /-3.5 +2.5
    if( (sign=='+' && realGreater.sign=='-') || (sign==' ' && realGreater.sign=='-')  ){
        return true;
    }
    else if( (sign=='-' && realGreater.sign=='+') || (sign=='-' && realGreater.sign==' ')  ){
        return false;
    }
    else if(sign=='-' && realGreater.sign=='-') {
        for(int i=0;i<number.length();i++) {
            if(number[i]<realGreater.number[i]){
                return true;
            }
        }
    }
    else{
        for(int i=0;i<number.length();i++){
            if(number[i]>realGreater.number[i]){
                return true;
            }
        }
    }
    return false;
}

bool BigReal::operator<(BigReal realSmaller) {
    this->padding(realSmaller);
    if( (sign=='-' && realSmaller.sign=='+') || (sign=='-' && realSmaller.sign==' ') ){
        return true;
    }
    else if( (sign=='+' && realSmaller.sign=='-') || (sign==' ' && realSmaller.sign=='-')  ){
        return false;
    }
    else if(sign=='-' && realSmaller.sign=='-') {
        for(int i=0;i<number.length();i++) {
            if(number[i]<realSmaller.number[i]){
                return false;
            }
        }
    }
    else{
        for(int i=0;i<number.length();i++){
            if(number[i]<realSmaller.number[i]){
                return true;
            }
        }
    }
    return false;
}

ostream& operator<<(ostream& out, const BigReal& num) {
    out << num.number;
    return out;
}

void BigReal::padding(BigReal realPad) {

    if(integer<realPad.integer || integer==""){
        while(integer.length() < realPad.integer.length()){
            integer='0'+integer;
        }
    }
    else if(integer>realPad.integer || realPad.integer==""){
        while(integer.length() > realPad.integer.length()){
            realPad.integer='0'+realPad.integer;
        }
    }

    if(fraction<realPad.fraction || fraction==""){
        if(fraction==""){
            fraction='.';
        }
        while(fraction.length() < realPad.fraction.length()){
            fraction=fraction+'0';
        }
    }
    else if(fraction>realPad.fraction || realPad.fraction==""){
        if(realPad.fraction==""){
            realPad.fraction='.';
        }
        while(fraction.length() > realPad.fraction.length()){
            realPad.fraction=realPad.fraction+'0';
        }
    }
}

BigReal BigReal::operator+(BigReal& other) {
    this->padding(other);
    BigReal result;
    result.sign = sign; // Use the sign of the left operand
    int carry = 0;

    for (int i = number.length() - 1; i >= 0; i--) {
        if (number[i] == '.')
            result.number[i] = '.';
        else {
            int sum = (number[i] - '0') + (other.number[i] - '0') + carry;
            result.number[i] = (sum % 10) + '0';
            carry = sum / 10;
        }
    }

    return result;
}

BigReal BigReal::operator-(BigReal& other) {
    this->padding(other);
    BigReal result;
    result.sign = sign; // Use the sign of the left operand
    int borrow = 0;

    for (int i = number.length() - 1; i >= 0; i--) {
        if (number[i] == '.')
            result.number[i] = '.';
        else {
            int diff = (number[i] - '0') - (other.number[i] - '0') - borrow;
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result.number[i] = diff + '0';
        }
    }

    return result;
}
