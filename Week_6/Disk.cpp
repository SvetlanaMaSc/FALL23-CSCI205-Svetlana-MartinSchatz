#include <iostream>
#include "Disk.h"

using namespace std;

Disk::Disk() {
    name = "";
    value = 0;
    size = 1;
}

Disk::Disk(string n, int v, int s) : name(n), value(0), size(0) {
    name = n;
    value = v;
    size = s;
}

Disk::~Disk() {
    
}

int Disk::getSize() {
    return size;
}

string Disk::getName() {
    return name;
}

ostream& operator<<(ostream& os, const Disk& d)
{
    os << d.name << " " << d.value << " " << d.size;
    return os;
}