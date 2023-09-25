#include <iostream>
#include <string>

#include "Stack.h"

/**
 * Check if an expression has balanced parentheses
*/
bool isValidBrackets(string token) {
    Stack<string> parentheses(15);
    for (size_t i = 0; i < token.length(); i++) {
        char c = token[i];
        string s = "";
        s += c;
        if ( s == "(") {
            parentheses.push(s);
        }
        else if (s == ")") {
           string p = parentheses.pop();
           if (p != "(") {
            return false;
           }
        }
    }
    if (parentheses.is_empty() == false) {
        // if the stack isn't empty, then not everything was paired making it invalid;
        return false;
    }
    else {
        // if the stack is empty, everything got paired or there weren't any parentheses at all
        return true;
    }
}

/**
 * Compare the precedence of operators. Check if the first operator is of higher precedence then the second
*/
bool compareOp(string first, string second) {
    string opHi = "*/";
    string opLow = "+-";
    string parentheses = "()";
    if (parentheses.find(second) != string::npos) {
        // A parenthesis is not an operator so it has no precedence;
        return true;
    }
    else {
        if (opHi.find(first) != string::npos) {
            if (opLow.find(second) != string::npos) {
                return true;
            }
        }
    }
    return false;
    // first is a high precedent operator
}

/**
 * convert infix to postfix
*/
string infixToPostfix(string token) {
    string postfix = "";
    // Check if Brackets match
    if (isValidBrackets(token) == true) {
        Stack <string> stack(15);
        // string of operators to look for 
        string operators = "+-*/()";
        // postfix string
        for (size_t i = 0; i < token.length() + 1; i++) {
            char c = token[i];
            string s = "";
            s += c;
            // check if it's an operand
            if (c != 0 && operators.find(s) == string::npos) {
                // add straight to the postfix string if so
                postfix += s;
            } 
            else {
                // check the precedence
                /**
                 * 1: ()
                 * 2: *\/
                 * 3: +-
                 */
                if (s == "(") {
                    stack.push(s);
                } 
                else if (s == ")") {
                    // pop operators off the stack until you find a )
                    string popped = stack.pop();
                    while (popped != "(") {
                        // add to postfix string
                        postfix += popped;
                        popped = stack.pop();
                    }
                }
                else {
                    string top = stack.peek();
                    if (top == "" || compareOp(s, top) == true) {
                        stack.push(s);
                    }
                    else {
                        while (compareOp(s, top) == false && stack.is_empty() == false) {
                            string popped = stack.pop();
                            if (popped != "(" && popped != ")") {
                                postfix += popped;
                            }
                            top = stack.peek();
                        }
                        stack.push(s);

                    }
                }
            }
            // stack.print();
        }
    }
    else {
        postfix = "invalid";
    }
    return postfix;
}

/**
 * Evaluate Postfix expression
*/
string postfixEvalutor(string token) {
    Stack<string> operators(15);
    Stack<string> operands(15);
    string ops = "+-*/";
    for (size_t i = 0; i < token.length(); i++) {
        char c = token[i];
        string s = "";
        s += c;
        // Is an operand
        if (c != 0 && ops.find(s) == string::npos) {
            operands.push(s);
        }
        // is an operator
        else {
            string a_s = operands.pop();
            string b_s = operands.pop();
            int a = stoi(a_s);
            int b = stoi(b_s);
            int result = 0;
            if (s == "+") {
                result = a + b;
            }
            else if (s == "-") {
                result = a - b;
            }
            else if (s == "*") {
                result = a * b;
            }
            else {
                result = a / b;
            }
            string resultString = std::to_string(result);
            operands.push(resultString);
        }
    }
    string expression = operands.pop();
    return expression;

}