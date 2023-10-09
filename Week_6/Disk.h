#ifndef DISK_H
#define DISK_H
using namespace std;

class Disk {
    private:
        int value;
        int size;
        string name;

    public:
        Disk();
        Disk(string name, int value, int size);
        ~Disk();
        int getSize();
        string getName();

        friend ostream& operator<<(ostream& os, const Disk& dt);
};

#endif