#include <iostream>
#include <string>
#include "Task.h"
using namespace std;

Task::Task() {
    pid = 0;
    command = "Unkmown command";
    time = "??";
    mem = 0;
}

Task::Task(string pidS, string commandS, string timeS, string memS) {
    // randomly generate pid
    pid = stoi(pidS);
    command = commandS;
    time = timeS;
    mem = stoi(memS);
}

string Task::getCommand() {
    return command;
}

int Task::getPID() {
    return pid;
}

string Task::getTime() {
    return time;
}

void Task::updateTime(int x) {
    time += x;
}

int Task::getMem() {
    return mem;
}

ostream& operator<<( std::ostream& stream, Task& task ) {
	stream << "PID: " <<  task.getPID() << endl;
	stream << "Command: " << task.getCommand() << endl;
	stream << "Time: " << task.getTime() << endl;
	stream << "Memory: " << task.getMem() << endl;

	return stream;
}