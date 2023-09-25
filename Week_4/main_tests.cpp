#include <iostream>
#include "infix_calculator.cpp"
#include "Task.h"
#include "TaskSwitcher.h"
#include "Deque.h"
#include "Queue.h"
#include "Stack.h"

using namespace std;

int main() {

    /**
     * Deques, Stacks, and Queues
    */
    Deque<int> d(5);
    d.push_front(1);
    d.push_front(2);
    d.push_front(3);
    d.push_front(4);
    d.push_front(5);
    while (d.is_empty() == false) {
        d.remove_front();
    }
    d.push_back(6);
    d.push_back(7);
    d.push_back(8);
    d.push_back(9);
    d.push_back(10);
    d.push_back(11);
    while (d.is_empty() == false)
    {
        d.remove_back();
    }
    
    Stack<int> s(5);
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);
    while (!s.is_empty()) {
        s.pop();
    }
    s.pop();

    Queue<int> q(5);
    q.enque(1);
    q.enque(2);
    q.enque(3);
    q.enque(4);
    q.enque(5);
    while (!q.is_empty()) {
        q.deque();
    }

    /**
     * Infix Problems
    */
    string pf1 = infixToPostfix("A+B-C");
    cout << pf1 << endl;
    string pf2 = infixToPostfix("A*B/C");
    cout << pf2 << endl;
    string pf3 = infixToPostfix("A+B*C");
    cout << pf3 << endl;
    // I know this one is wrong but it was very late when i noticed it and the print function i was using for debugging suddenly caused segmentation errors. So I left it .
    string pf4 = infixToPostfix("A+B*(C-D/(E+F))");
    cout << pf4 << endl;
    /**
     * Postfix Evaluator
    */
    cout << postfixEvalutor("234*+5+") << endl;
    /**
     * Task Switcher
    */
    TaskSwitcher ts = TaskSwitcher();
    ts.read("tasks.txt");
    ts.robinSwitching();


    return 0;
}