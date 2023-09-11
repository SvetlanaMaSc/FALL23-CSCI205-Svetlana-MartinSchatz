#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "Fraction.h"

using namespace std;

/**
 * Parses a line from the file into a Fraction object
*/
Fraction parseFraction(string s) {
    vector<string> numAndDen;
    // I found an article on tutorialpoint that explained how to split strings by deliminator using stringstream. The stream takes the line and splits the line in two using the comma as a break point.
    stringstream s_stream(s);
    while (s_stream.good()) {
        string substr;
        getline(s_stream, substr, ',');
        numAndDen.push_back(substr);
    }
    // convert string into integer 
    int num = stoi(numAndDen.front());
    int den = stoi(numAndDen.back());

    // build and return new Fraction object
    return Fraction(num, den);
}

/**
 * Find the largest fraction
*/
Fraction find_largest(vector<Fraction> fractions) {
    Fraction largest(0, 1);
    for (int i = 0; i < fractions.size(); i++) {
        Fraction current = fractions[i];
        if (current >= largest) {
            largest = current;
        }
    }
    return largest;
}

/**
 * Read the fractions from the text, convert strings to fractions, and return vector of fractions
*/
vector<Fraction> getFractions() {
    vector<Fraction> fractions;
    fstream newFile;
    newFile.open("fractions.txt", ios::in);
    if (newFile.is_open()) {
        string line;
        while(getline(newFile, line)) {
            Fraction f = parseFraction(line);
            fractions.push_back(f);
        }
    }
    return fractions;
}

/**
 * Print the fractions in a neat 5 x 25 display
*/
void print(vector<Fraction> fractions) {
    int fSize = fractions.size();
    for (int i = 0; i < fSize; i++) {
        Fraction f = fractions[i];
        cout << f << " ";
        if (i % 5 == 0) {
            cout << "\n";
        }
    }
    cout << "\n";
}

int main() {
    // Initiate vector of Fractions
    vector<Fraction> fractions = getFractions();
    // print fractions
    print(fractions);
    Fraction largest = find_largest(fractions);
    cout << "largest: " << largest << endl;

    // // Fractions that will be calculated with each fraction in the vector
    Fraction a(3, 7); 
    Fraction b(-4, 6); 
    for (int i = 0; i < 10; i++) {
        Fraction current = fractions[i];
        // // Add
        Fraction add1 = current + a;
        Fraction add2 = current + b;
        // // Subtraction
        Fraction sub1 = current - a;
        Fraction sub2 = current - b;
        // // Multiplication
        Fraction mult1 = current * a;
        Fraction mult2 = current * b;
        // // Division
        Fraction div1 = current / a;
        Fraction div2 = current / b;

        cout << "current (" << current << ") + a (" << a << ") = " << add1 << endl;
        cout << "current (" << current << ") + b (" << b << ") = " << add2 << endl;
        cout << "current (" << current << ") - a (" << a << ") = " << sub1 << endl;
        cout << "current (" << current << ") - b (" << b << ") = " << sub2 << endl;
        cout << "current (" << current << ") * a (" << a << ") = " << mult1 << endl;
        cout << "current (" << current << ") * b (" << b << ") = " << mult2 << endl;
        cout << "current (" << current << ") / a (" << a << ") = " << div1 << endl;
        cout << "current (" << current << ") / b (" << b << ") = " << div2 << endl;
        cout << "\n";
    }
}