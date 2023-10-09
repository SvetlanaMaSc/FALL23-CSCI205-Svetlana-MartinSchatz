#include <iostream>
#include <string>
#include "Disk.h"
#include "LinkedList.h"

using namespace std;


void moveDisk(LinkedList<Disk>& fp, LinkedList<Disk>& tp){
    Disk disk = fp.pop();
    tp.insert(disk);
    cout << "\nMoved disk (" << disk.getName() << ") of size " << disk.getSize() << " from pole " << fp.getName() << " to pole " << tp.getName() << endl;
}

void moveTower(int height, LinkedList<Disk>& fromPole, LinkedList<Disk>& toPole, LinkedList<Disk>& withPole){
        if (height >= 1 ) {
            if (height >= 1 ) {
            cout << "Starting moveTower call with height " << height << ", from " << fromPole.getName() << " to " << toPole.getName() << " with " << withPole.getName() << endl;

            moveTower(height-1, fromPole, withPole, toPole); //Recursive call
            moveDisk(fromPole, toPole);
            moveTower(height-1, withPole, toPole, fromPole); //Recursive call

            cout << "Finishing moveTower call with height " << height << endl;
        }
    }
}

void towers_of_hanoi(int disks) {
    LinkedList<Disk> A("A");
    LinkedList<Disk> B("B");
    LinkedList<Disk> C("C");

    for (int i = disks; i > 0; i--) {
        Disk d(to_string(i), i,  i);
        A.insert(d);
    }
    
    cout << "Initial state of the towers:" << endl;
    cout << "A: "; A.print();
    cout << "B: "; B.print();
    cout << "C: "; C.print();
    cout << "===============================" << endl;

    moveTower(disks, A, B, C);

    cout << "Final state of the towers:" << endl;
    cout << "A: "; A.print();  // Note: 'A' should be accessible here if you move its declaration to a higher scope.
    cout << "B: "; B.print();  // Similar for B and C.
    cout << "C: "; C.print();
}

int main() {
    towers_of_hanoi(7);
}

