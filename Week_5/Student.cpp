#include <iostream>
#include <string>
#include "Student.h"

using namespace std;

Student::Student() {}

Student::Student(int id, std::string name){
	this->id 	= id;
	this->name 	= name;
}

int Student::getID() const{
	return this->id;
}

std::string Student::getName() const{
	return this->name;
}

std::string Student::getDorm() const{
	return this->dorm;
}

void Student::setDorm(string dormName) {
	this->dorm = dormName;
}

