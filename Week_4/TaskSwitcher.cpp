#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include "Queue.h"
#include "Task.h"
#include "TaskSwitcher.h"

using namespace std;

TaskSwitcher::TaskSwitcher() {
    /*
    Task
    submit print task -> added to waiting list (queue)
        printer completes task -> checks queue
    page (1-20)
        20 prints per hour
            task -> 180 sec
    */
    Queue<Task> tasks(100);
}

Task TaskSwitcher::buildTask(string line) {
    string strings[4];
    stringstream s_stream(line);
    int i = 0;
    string substr;
    while (getline(s_stream, substr, '\t')) {
        strings[i] = substr;
        i++;
    }
    Task t = Task(
        strings[0],
        strings[1],
        strings[2],
        strings[3]
    );

    return t;
}

void TaskSwitcher::read(string file) {
    fstream newFile;
    newFile.open(file, ios::in);
    if (newFile.is_open()) {
        string line;
        while(getline(newFile, line)) {
            // build tasks
            Task t = buildTask(line);
            // add to queue
            tasks.enque(t);
        }
    }
    newFile.close();
}

void TaskSwitcher::robinSwitching() {
    while (true) {
        Task t = tasks.deque();
        cout << t << endl;
        sleep(5);
        tasks.enque(t);
    }
}