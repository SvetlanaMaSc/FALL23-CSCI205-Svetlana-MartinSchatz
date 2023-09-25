#ifndef TASK_H
#define TASK_H

#include <string>
using namespace std;

class Task {
    private:
        int pid;
        string command;
        string time;
        int mem;

    public:
        Task();
        Task(
            string pid, 
            string command, 
            string time,
            string mem
        );
        string getCommand();
        int getPID();
        string getTime();
        void updateTime(int x);
        int getMem();

        friend std::ostream& operator<<(std::ostream& stream, Task& task);

};

#endif