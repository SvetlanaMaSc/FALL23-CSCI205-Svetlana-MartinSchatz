#include <iostream>
#include <string>
#include "ArrayList.h"
#include "LinkedList.h"
#include "Dorm.h"
#include "Student.h"

#include <iostream>
#include <string>

// ==================================
// || Constructors
// ==================================
Dorm::Dorm(std::string dorMname) {
    name = dorMname;
}

// ==================================
// || Methods
// ==================================

/**
 * Add a student to the roster of students
*/
void Dorm::enroll(Student student) {
    // Convert to node
    students.append(student);

}

/**
 * Add a list of students to this list
*/
void Dorm::enroll(LinkedList<Student> students) {
    students.append(students);
}

/**
 * Kick student out of dorm
*/
void Dorm::boot(int pos) {
    students.remove(pos);
}

/**
 * Return name of the dorm
*/
std::string Dorm::getName() {
    return name;
}

/**
 * Return students
*/

LinkedList<Student> Dorm::getStudents() {
    return students;
}