#include <iostream>
#include <string>
#include "Stack.h"
#include "LinkedList.h"

using namespace std;

/**
 * Reverse string in an iterative way
*/
string reverseStringIterative(string str) {
    Stack<char> stack;
    // push onto stack
    for (size_t i = 0; i < str.length(); i++) {
        stack.push(str[i]);
    }
    // pop into array
    string rev = "";
    while (stack.is_empty() == false) {;
        rev += stack.pop();
    }
    
    // return new string
    return rev;    
}

/**
 * Reverse a string recursively 
*/
string reverseStringRecursie(string str) {
    // base case
    if (str.length() <= 1) {
        return str;
    }

    // Recursive case. Prepend last character of string onto str and call the function with that new string
    return str[str.length() - 1] + reverseStringRecursie(str.substr(0, str.length() - 1));
}

/**
 * Print the numbers 1-N recursively 
*/
void print50(int n) {
    // Quit once we hit 50
    if (n > 50) {
        return;
    }

    // print current n
    cout << n << " ";
    print50(n + 1);
}

/**
 * Calculate sum of numbers in an array
*/
int sum(int array[], int length, int n) {
    if (n >= length) {
        return 0;
    }

    return array[n] + sum(array, length, n + 1);
}

/**
 * Find the length of a digit
*/
int len(int num) {
    // if dividing by 10 = 0 then we're at a single digit
    if (num / 10 == 0) {
        return 1;
    }

    return 1 + len(num / 10);
}

/**
 * Count the number of ears on puppies
*/
int ears(int puppies) {
    if (puppies == 0) {
        return 0;
    }

    if (puppies % 2 == 0) {
        return 3 + ears(puppies - 1);
    }
    else {
        return 2 + ears(puppies - 1);
    }
}

/**
 * Search for given character in string and remove it 
*/
string strip(string text, char letter) {
    if (text.length() == 0) {
        return "";
    }
    
    if (text[0] == letter) {
        return strip(text.substr(1), letter);
    }
    else {
        return text[0] + strip(text.substr(1), letter);
    }
}

/**
 * Check for Nested Parentheses
*/

bool checkParentheses(string word) {
    if (word.length() == 0) {
        return true;
    }
    if (word[0] == '(' && word[word.length() - 1] == ')') {
        return checkParentheses(word.substr(1, word.length() - 2));
    }
    else {
        return false;
    }
}

int main() {
    /**
     * Reverse a string iteratively
    */
    cout << "Reverse a String Iteratively" << endl;
    cout << "----------------------------" << endl;
    string start = "string";
    string rev = reverseStringIterative(start);
    cout << "string: \"" << start << "\" reverse: \"" << rev << "\" " << endl;
    cout << endl;


    /**
     * Reverse string recurisively
    */
    cout << "Reverse a String Recursively" << endl;
    cout << "----------------------------" << endl;
    rev = reverseStringRecursie(start);
    cout << "string: \"" << start << "\" reverse: \"" << rev << "\" " << endl;
    cout << endl;


    /**
     * Countto 50 
    */
    cout << "Print 50" << endl;
    cout << "--------" << endl;
    print50(1);
    cout << endl;
    cout << endl;
    
    /**
     * Sum of numbers in an array
    */
    cout << "Sum of Numbers" << endl;
    cout << "--------------" << endl;
    int arr[] = {1, 2, 3, 4, 5};
    // The length of the 
    int length = sizeof(arr) / sizeof(arr[0]);
    cout << "Numbers: ";
    for (int i = 0; i < length; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    int s = sum(arr, length, 0);
    cout << "Sum: " << s << endl;
    cout << endl;

    /**
     * Find length of digit
    */
    cout << "Length of a Digit" << endl;
    cout << "-----------------" << endl;
    int one = 1;
    int two = 11;
    int three = 111;
    int four = 1111;
    int five = 11111;

    cout << one << ": " << len(one) << endl;
    cout << two << ": " << len(two) << endl;
    cout << three << ": " << len(three) << endl;
    cout << four << ": " << len(four) << endl;
    cout << five << ": " << len(five) << endl;

    cout << endl;
    /**
     * Count ears on normal and chernobyl puppies
    */
    cout << "Puppy Ears" << endl;
    cout << "----------" << endl;
    int puppies = 10;

    cout << "Puppies: " << puppies << " Ears: " << ears(puppies) << endl;
    cout << endl;

    /**
     * Strip a Sentence
    */
    cout << "Strip a Sentence" << endl;
    cout << "----------------" << endl;
    string sentence = "123-45-6789";
    char token = '-';
    string stripped = strip(sentence, token);
    cout << "Sentence \"" << sentence << "\": Stripped: \"" << stripped << "\"" << endl;
    cout << endl;

    /**
     * Check if Paretheses are Matched
    */
    cout << "Check for Nested Parenthses" << endl;
    cout << "---------------------------" << endl;
    string correctOne = "((()))";
    string correctTwo = "(())";
    string wrong = "(()";
    cout << "CorrectOne: " << checkParentheses(correctOne) << endl;
    cout << "CorrectTwo: " << checkParentheses(correctTwo) << endl;
    cout << "Wrong: " << checkParentheses(wrong) << endl;
    cout << endl;

    // ==================================
    // || Linked Lists
    // ==================================
    LinkedList<int> link;
    
    for (int i = 0; i < 9; i++) {
        link.insert(i);
    }
    Node<int>* h1 = link.getHead();

    // /**
    //  * Recursive Print
    // */
    cout << "Print the List Recursively" << endl;
    cout << "--------------------------" << endl;
    link.printRecursive(h1);
    cout << endl;

    /**
     * Recursive Reverse
    */
    cout << "Reverse the List Recursively" << endl;
    cout << "----------------------------" << endl;
    link.print();
    Node<int>* h2 = link.getHead();
    link.reverseRecursive(h2);
    link.print();
    return 0;
}