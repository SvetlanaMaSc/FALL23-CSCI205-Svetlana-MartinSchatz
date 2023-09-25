#ifndef TASKSWITCHER_H
#define TASKSWITCHER_H

#include "Queue.h"
#include "Task.h"

using namespace std;

class TaskSwitcher {
    private:
        Queue<Task> tasks;

    public:
        TaskSwitcher();
        Task buildTask(string line);
        void read(string file);
        void robinSwitching();
};

#endif