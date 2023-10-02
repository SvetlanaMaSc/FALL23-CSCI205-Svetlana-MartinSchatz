#ifndef DORM_H
#define DORM_H

#include <iostream>
#include <string>
#include "LinkedList.h"
#include "Student.h"

class Dorm {
    private:
        std::string name;
        LinkedList<Student> students;
    
    public:
        Dorm(std::string dormName);
        void enroll(Student student);           // Adds one more student to the roster
        void enroll(LinkedList<Student> students);   /// Adds a list of students to the roster
        std::string getName();
        LinkedList<Student> getStudents();
        void boot(int pos)
;};

#endif