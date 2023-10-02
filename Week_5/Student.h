#ifndef H_STUDENT
#define H_STUDENT
#include <iostream>
#include <string>

using namespace std;

class Student{
	private:
		int id;
		std::string name;
		std::string dorm;

	public:
		Student();
		Student(int, std::string);
		int getID() const;
		std::string getName() const;
		std::string getDorm() const;
		void setDorm(string dormName);
};
#endif