#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>
#include "ArrayList.h"
#include "LinkedList.h"
#include "Dorm.h"
#include "Student.h"

using namespace std;

/**
 * TODO: try appending in an empty array.
 * TODO: payload constructor
*/

const int CYCLES = 10;

int main() {

    // ==================================
    // || ArrayList tests
    // ==================================
    // Initiate the array
    ArrayList<int> arrayL(CYCLES);
    // Start the clock

    /**
     * Insert
    */
    for (int i = 0; i < CYCLES; i++) {
            arrayL.insert(i);
    }
    
    arrayL.print();

    /**
     * Remove
    */
    for (int i = 0; i < CYCLES/2; i++) {
        int point = rand() % CYCLES /2 ;
        arrayL.remove(point);
    }

    arrayL.print();

   /**
    * Insert, Position
   */
    for (int i = 0; i < CYCLES/4; i++) {
        int point = rand() % CYCLES /2 ;
        arrayL.insert(point);
    }

    arrayL.print();

    /**
     * Append
    */
    for (int i = 0; i < CYCLES/4; i++) {
        int point = rand() % CYCLES /2 ;
        arrayL.insert(point);
    }

    arrayL.print();

    /**
     * Rmove Duplicates
    */
    arrayL.remove_duplicates();

    arrayL.print();

    /**
     * Reverse 
    */
    arrayL.reverse();

    arrayL.print();

    /**
     * Apppend and Resise
    */
    ArrayList<int> arrayL2;
    for (int i = 0; i < 10; i++) {
        arrayL2.insert(i);
    }
    arrayL.append(arrayL2);

    arrayL.print();

    // ==================================
    // || LinkedList tests
    // ==================================
    LinkedList<int> linkedL;

    /**
     * Insert
    */
    for (int i = 0; i < CYCLES; i++) {
            linkedL.insert(i);
    }

    linkedL.print();

    /**
     * Remove
    */
   for (int i = 0; i < CYCLES/2; i++) {
        int point = rand() % CYCLES /2 ;
        linkedL.remove(point);
    }

    linkedL.print();

   /**
    * Insert, Position
   */
    for (int i = 0; i < CYCLES/4; i++) {
        int point = rand() % CYCLES /2 ;
        linkedL.insert(point);
    }
    linkedL.print();

    /**
     * Append
    */
    for (int i = 0; i < CYCLES/4; i++) {
        int point = rand() % CYCLES /2 ;
        linkedL.insert(point);
    }
    
    linkedL.print();

    /**
     * Rmove Duplicates
    */
    linkedL.remove_duplicates();

    linkedL.print();

    /**
     * Reverse
    */
    linkedL.reverse();
    linkedL.print();

    /**
     * Apppend and Resise
    */
    LinkedList<int> linkedL2;

    for (int i = 0; i < 10; i++) {
        linkedL2.insert(i);
    }
    linkedL.append(linkedL2);

    linkedL.print();

    // ==================================
    // || Dorms and Students
    // ==================================

    /**
     * Build Dorms
    */
    vector<Dorm> dorms;

    fstream dormFile;;
    // read dorms  file
    dormFile.open("dormFile.txt", ios::in);
    if (dormFile.is_open()) {
        string line;
        regex pattern("\r");
        while(getline(dormFile, line)) {
             // strip the "\r"
            line = regex_replace(line, pattern, "");
            Dorm d(line);
            dorms.push_back(d);
        }
    }

    dormFile.close();

    /**
     * Build Students
    */
    fstream studentFile;
    studentFile.open("studentFile.txt", ios::in);
    if (studentFile.is_open()) {
        string line;
        // regex patern to separate the number and name
        regex pattern("(\\d+)\\s+(\\w+)");
        int dormPointer = 0;
        while(getline(studentFile, line)) {
            smatch match;
            if (regex_search(line, match, pattern)) {
                int num = stoi(match.str(1));   // get the number
                string name = match.str(2);     // get the name
                // create the student
                Student s(num, name);
                // add to dorm
                // Dorm currentDorm = dorms[dormPointer];
                s.setDorm(dorms[dormPointer].getName());
                dorms[dormPointer].enroll(s);
                if (dormPointer == 3) {
                    dormPointer = 0;
                }
                else {
                    dormPointer++;

                }
            }
        }
    }

    studentFile.close();
    /**
     * Swap Students
    */
    // for (size_t i = 0; i < dorms.size(); i++) {
    //     Dorm d = dorms[i];
    //     LinkedList<Student> students = d.getStudents();
    //     for (int j = 0; j < students.length(); j++) {
    //         Student s = students.get(j);
    //         int random = rand() % 3;
    //         while (random == i) {
    //             random = rand() % 3;
    //         }
    //         // enroll in new
    //         dorms[random].enroll(s);
    //         d.boot(i);
    //     } 
    // }

    // Print roster
    // ofstream roster;
    // roster.open("Roster.txt", ios::out);
    // if (roster.is_open()) {
    //     for (int i = 0; i < dorms.size(); i++) {
    //         Dorm d = dorms[i];
    //         roster << "===== " << d.getName() << " ===" << endl;
    //         LinkedList<Student> students = d.getStudents();
    //         for (int j = 0; j < students.length(); j++) {
    //             Student s = students.get(j);
    //             roster << "ID: " << s.getID() << " Name: " << s.getName() << endl;
    //         }
    //     }
    // }
    // roster.close();

    return 0;
}