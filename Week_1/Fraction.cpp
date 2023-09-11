#include <iostream>
#include "Fraction.h"

using namespace std;

/**
 * Get the Greatest Common Denominator 
*/
int gcd(int m, int n) {
    while (m%n != 0) {
        int oldm = m;
        int oldn = n;

        m = oldn;
        n = oldm%oldn;
    }

    return n;
}

/**
* Get the Least Common Multiple. Calculated by multiplying m and n by the GCD of and m.
*/
int lcm(int m, int n) {
    int lcm = (m * n) / gcd(m, n);
    return lcm;
}

// constructor implementation 
Fraction :: Fraction(int top, int bottom) {
    num = top;
    den = bottom;
    if (den < 0) {
        den *= -1;
        num *= -1;
    }

    int common = gcd(num, den);
    num = num/common;
    den = den/common;
    if (den < 0) {
        den *= -1;
        num *= -1;
    }

}

std::ostream& operator<<(ostream& stream, Fraction& fraction) {
    stream << fraction.getNumerator() << "/" << fraction.getDenominator();

    return stream;
}

int Fraction :: getNumerator() {
    return num;
}
int Fraction :: getDenominator() {
    return den;
}

/**
 * Addition
*/
Fraction Fraction :: operator +(Fraction otherFrac) {
    int newnum = this->getNumerator()*otherFrac.getDenominator() + this->getDenominator()*otherFrac.getNumerator();
    int newden = this->getDenominator()*otherFrac.getDenominator();

    return Fraction(newnum, newden);
    
}

void Fraction :: operator +=(Fraction otherFrac) {
    *this = *this + otherFrac;
}

/**
 * Subtraction
*/
Fraction Fraction :: operator -(Fraction otherFrac) {
    int newden = lcm(this->getDenominator(), otherFrac.getDenominator());
    int a = newden / this->getDenominator();
    int b = newden / otherFrac.getDenominator();
    int newNumThis = this->getNumerator() * a;
    int newNumOther = otherFrac.getNumerator() * b;
    int newnum =  newNumThis - newNumOther;
    
    return Fraction(newnum, newden);
    
}

/**
 * Multiplication
*/
Fraction Fraction :: operator *(Fraction otherFrac) {
    int newnum = this->getNumerator() * otherFrac.getNumerator();
    int newden = this->getDenominator() * otherFrac.getDenominator();


    return Fraction(newnum, newden);
    
}


/**
 * Division
*/
Fraction Fraction :: operator /(Fraction otherFrac) {
    int newnum = this->getNumerator() * otherFrac.getDenominator();
    int newden = this->getDenominator() * otherFrac.getNumerator();


    return Fraction(newnum, newden);
    
}

/**
 * Greater Than.
 * Calculate the numerator divided by the denominator of both fractions and compare the results.
*/
bool Fraction :: operator >(Fraction otherFrac) {
    int a = this->getNumerator() / this->getDenominator();
    int b = otherFrac.getNumerator() / otherFrac.getDenominator();

    return a > b;
    
}

/**
 * Greater Than or Equal.
 * Calculate the numerator divided by the denominator of both fractions and compare the results.
*/
bool Fraction :: operator >=(Fraction otherFrac) {
    int a = this->getNumerator() / this->getDenominator();
    int b = otherFrac.getNumerator() / otherFrac.getDenominator();

    return a >= b;
    
}

/**
 * Less Than.
 * Calculate the numerator divided by the denominator of both fractions and compare the results.
*/
bool Fraction :: operator <(Fraction otherFrac) {
    int a = this->getNumerator() / this->getDenominator();
    int b = otherFrac.getNumerator() / otherFrac.getDenominator();

    return a < b;
    
}

/**
 * Less Than or Equal.
 * Calculate the numerator divided by the denominator of both fractions and compare the results.
*/
bool Fraction :: operator <=(Fraction otherFrac) {
    int a = this->getNumerator() / this->getDenominator();
    int b = otherFrac.getNumerator() / otherFrac.getDenominator();

    return a <= b;
    
}

/**
 * Not Equal.
 * Check if numerator and denominator
*/
bool Fraction :: operator !=(Fraction otherFrac) {
    
    return this->getNumerator() != otherFrac.getNumerator() || this->getDenominator() != otherFrac.getDenominator();

}