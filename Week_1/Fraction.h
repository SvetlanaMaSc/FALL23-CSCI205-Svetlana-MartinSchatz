#ifndef FRACTION_H
#define FRACTION_H

class Fraction {
    private:
        int num;
        int den;


    public:
        Fraction(int top, int bottom);
        // ~Fraction();

        int getNumerator();
        int getDenominator();
        Fraction operator +(Fraction otherFrac);
        void operator +=(Fraction otherFrac);
        Fraction operator -(Fraction otherFrac);
        Fraction operator *(Fraction otherFrac);
        Fraction operator /(Fraction otherFrac);
        bool operator >(Fraction otherFrac);
        bool operator >=(Fraction otherFrac);
        bool operator <(Fraction otherFrac);
        bool operator <=(Fraction otherFrac);
        bool operator !=(Fraction otherFrac);

    friend std::ostream& operator<<(std::ostream& stream, Fraction& fraction);
};

#endif