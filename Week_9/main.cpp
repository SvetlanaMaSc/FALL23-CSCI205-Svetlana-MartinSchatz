#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <fstream>
#include "LinkedList.hpp"

using namespace std;

void swap(vector<int>& vec, int a, int b){
	int temp	= vec[a];
	vec[a]		= vec[b];
	vec[b]		= temp;
}

/**
 * Comb Sort
*/
int combSort(vector<int> &list) {
    int numSwaps = 0;
    int gap = list.size();
    float shrink = 1.3;
    bool sorted = false;

    while (sorted == false) {
        gap = floor(gap/shrink);
        if (gap > 1) {
            sorted = false;
        }
        else {
            gap = 1;
            sorted = true;
        }

        int i = 0;
        while (i + gap < list.size()) {
            if (list[i] > list[i + gap]) {
                swap(list[i], list[i + gap]);
                numSwaps++;
                sorted = false;
            }
            i++;
        }
    }

    return numSwaps;
}

/**
 * Shell Sort
*/
int shellSort(vector<int>& list, vector<int>& sequence) {
    int numSwaps = 0;
    for (int gap : sequence) {
        for (int i = gap; i < list.size(); i++) {
            int temp = list[i];
            int j;
            for (j = i; j >= gap && list[j - gap] > temp; j -= gap) {
                list[j] = list[j - gap];
                numSwaps++;
            }
            list[j] = temp;
        }
    }

    return numSwaps;
}

/**
 * Shell Sort Hibbard Dequence
*/
vector<int> hibbard(int size) {
    vector<int> seq;
    int h = 1;
    while (h < size) {
        seq.push_back(h);
        h = (2 * h) - 1;
    }
    return seq;
}

/**
 * Shell Sort Sedgewick Sequence
*/
vector<int> sedgewick(int size) {
    vector<int> seq;
    int h1 = 0;
    int h2 = 0;
    while (true) {
        // Set 1
        h1 = (9 * (pow(4, h1 - pow(2, h1))));
        h1++;
        if (h1 < size) {
            seq.push_back(h1);
        }
        else {
            break;
        }
        // Set 2
        h2 = pow(2, h2 + 2) * (pow(2, h2 + 2) - 3) + 1;
        h2++;
        if (h2 < size) {
            seq.push_back(h2);
        }
        else {
            break;
        }
    }
    return seq;
}


/**
 * Shell Sort Knuth Sequence
*/
vector<int> knuth(int size) {
    vector<int> seq;
    int h = 1;
    while (h < size) {
        seq.push_back(h);
        h = (3 * h) + 1;
    }
    return seq;
}


/**
 * Generate Randomness
*/
vector<int> generateRandom(int count, char t) {
    vector<int> seq;
    int h = 1;
    // if random
    if (t == 'R') {
        for (int i = 0; i < count; i++) {
            h = rand();
            seq.push_back(h);
        }
    }
    else if (t == 'I') {
        for (int i = count; i > 0; i--) {
            seq.push_back(i);
        }
    }
    else {
        for (int i = count; i > 0; i--) {
            if (i % 2 == 0) {
                seq.push_back(i);
            }
            else {
                int modI = i + rand();
                seq.push_back(modI);
            }
        }
    }
    return seq;
}

/**
 * Bubble Sort
*/
int bubbleSort(vector<int>& avector) { // O(n ^ 2)
	// iterate N, N-1, N-2, N-3 . . . etc times
    int numSwaps = 0;
	for (int passnum = avector.size()-1; passnum > 0; passnum -= 1)
		for (int i = 0; i < passnum; i++)
			if (avector[i] > avector[i+1]) {
				swap(avector, i, i+1);
                numSwaps++;
            }
	return numSwaps;
}

/**
 * Insertion Sort
*/
int insertionSort(vector<int>& avector) {
    int numSwaps = 0;
	for (unsigned int index =1; index<avector.size(); index++) {
		int currentvalue 	= avector[index];			// remember current item
		int position 		= index;					// need current position to move towards front
		while (position>0 && avector[position-1]>currentvalue) {
			avector[position] = avector[position-1];	// shift by 1 spot
            numSwaps++;
			position--; 								// keep moving towards front of vector
		}
		avector[position] = currentvalue;				// place current item in opened spot
	}
    return numSwaps;
}

/**
 * Selection Sort
*/
int selectionSort(vector<int>& avector) {
	// iterate N, N-1, N-2, N-3 . . . etc times
    int numSwaps = 0;
	for (int fillslot = avector.size() - 1; fillslot >= 0; fillslot--) {
		int positionOfMax = 0;
		for (int location = 1; location < fillslot + 1; location++)
			if (avector[location] > avector[positionOfMax])
				positionOfMax = location;
		swap(avector, fillslot, positionOfMax);
        numSwaps++;
	}
    return numSwaps;
}

/**
 * Counting Sort
*/
vector<int> countingSort(vector<int> orig) {
    int maxValue = *max_element(orig.begin(), orig.end());
    // histogram array
    vector<int> histo(maxValue + 1, 0);
    vector<int> sorted(orig.size(), 0);
    for (int i = 0; i < orig.size(); i++) {
        histo[orig[i]] = histo[orig[i]] + 1;
    }
    // Prefix
    int newNum = 0;
    for (int i = 0; i < histo.size(); i++) {
        newNum += histo[i];
        histo[i] = newNum;
    }
    for (int i = orig.size() - 1; i >= 0; i--) {
        sorted[histo[orig[i]] - 1] = orig[i];
        histo[orig[i]]--;
    }

    return sorted;
}

/**
 * Counting Radix Sort
*/
void radix(vector<int> &orig, int radix) {
    int maxValue = *max_element(orig.begin(), orig.end());
    vector<int> lsds(orig.size());
    int count = 0;
    int n = 1;
    // find length
    while (n) {
        count++;
        n /= 10;
    }
    int mult = 10;
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < orig.size(); j++) {
            int lsd = orig[i] % mult;
            lsds[i] = lsd;
        }
        orig = countingSort(lsds);
        mult *= 10;
    } 
}

/**
 * Bucket Sort
*/
void bucket(vector<int> orig, int radix) {
    // Queues
    LinkedList<int> q0;
    LinkedList<int> q1;
    LinkedList<int> q2;
    LinkedList<int> q3;
    LinkedList<int> q4;
    LinkedList<int> q5;
    LinkedList<int> q6;
    LinkedList<int> q7;
    LinkedList<int> q8;
    LinkedList<int> q9;
    for (int i = 0; i < orig.size(); i++) {
        int lsd = orig[i] % 10;
        switch (lsd) {
            case 0:
                q0.append(orig[i]);
                break;
            case 1:
                q1.append(orig[i]);
                break;
            case 2:
                q2.append(orig[i]);
                break;
            case 3:
                q3.append(orig[i]);
                break;
            case 4:
                q4.append(orig[i]);
                break;
            case 5:
                q5.append(orig[i]);
                break;
            case 6:
                q6.append(orig[i]);
                break;
            case 7:
                q7.append(orig[i]);
                break;
            case 8:
                q8.append(orig[i]);
                break;
            case 9:
                q9.append(orig[i]);
                break;
        }
    }
}

vector<int> ranVect(int limit) {
    vector<int> rv;
    for (int i = 0; i < limit; i++) {
        int a = rand() % 500 + 1;
        rv.push_back(a);
    }
    return rv;
}

vector<int> generateRandomGaps(int size, int limit) {
    vector<int> gaps;
    for (int i = 0; i < size; ++i) {
        gaps.push_back(rand() % limit + 1);
    }
    gaps.push_back(1);

    sort(gaps.begin(), gaps.end());
    gaps.erase(unique(gaps.begin(), gaps.end()), gaps.end());

    reverse(gaps.begin(), gaps.end());

    return gaps;
}

int main() {
    // files
    ofstream combfile("comb sort.txt");
    ofstream shellfile("shell sort.txt");
    ofstream bubblefile("bubble sort.txt");
    ofstream insertfile("insert sort.txt");
    ofstream selectfile("select sort.txt");


    // ==================================
    // || Comb Sort
    // ==================================
    vector<int> cSmall = ranVect(500);
    vector<int> cLarge1 = ranVect(1000);
    vector<int> cLarge2 = ranVect(2000);
    vector<int> cLarge3 = ranVect(5000);
    int combSmall = combSort(cSmall);
    int combLarge1 = combSort(cLarge1); 
    int combLarge2 = combSort(cLarge2); 
    int combLarge3 = combSort(cLarge3); 
    combfile << "500," << combSmall << endl;
    combfile << "1000," << combLarge1 << endl;
    combfile << "2000," << combLarge2 << endl;
    combfile << "5000," << combLarge3 << endl;

    
    // ==================================
    // || Shell Sort
    // ==================================
    vector<int> gaps1 = generateRandomGaps(12, 500);
    vector<int> gaps2 = generateRandomGaps(15, 1000);
    vector<int> gaps3 = generateRandomGaps(20, 2000);
    vector<int> gaps4 = generateRandomGaps(30, 5000);
    vector<int> sSmall = ranVect(500);
    vector<int> sLarge1 = ranVect(1000);
    vector<int> sLarge2 = ranVect(2000);
    vector<int> sLarge3 = ranVect(5000);
    int shellSmall = shellSort(sSmall, gaps1);
    int shellLarge1 = shellSort(sLarge1, gaps2);
    int shellLarge2 = shellSort(sLarge2, gaps3);
    int shellLarge3 = shellSort(sLarge3, gaps4);
    shellfile << "500," << shellSmall << endl;
    shellfile << "1000," << shellLarge1 << endl;
    shellfile << "2000," << shellLarge2 << endl;
    shellfile << "5000," << shellLarge3 << endl;

    // // ==================================
    // // || Hibbard Sequence
    // // ==================================
    // vector<int> hSmall = hibbard(500);
    // vector<int> hLarge1 = hibbard(1000);
    // vector<int> hLarge2 = hibbard(2000);
    // vector<int> hLarge3 = hibbard(5000);

    // // ==================================
    // // || Sedgewick Sequence
    // // ==================================
    // vector<int> sedSmall = sedgewick(500);
    // vector<int> sedLarge1 = sedgewick(1000);
    // vector<int> sedLarge2 = sedgewick(2000);
    // vector<int> sedLarge3 = sedgewick(5000);

    // // ==================================
    // // || Sedgewick Sequence
    // // ==================================
    // vector<int> kSmall = knuth(500);
    // vector<int> kLarge1 = knuth(1000);
    // vector<int> kLarge2 = knuth(2000);
    // vector<int> kLarge3 = knuth(5000);

    // ==================================
    // || Bubble Sort
    // ==================================
    vector<int> bSmall = ranVect(500);
    vector<int> bLarge1 = ranVect(1000);
    vector<int> bLarge2 = ranVect(2000);
    vector<int> bLarge3 = ranVect(5000);
    int bubbSmall = bubbleSort(bSmall);
    int bubbLarge1 = bubbleSort(bLarge1);
    int bubbLarge2 = bubbleSort(bLarge2);
    int bubbLarge3 = bubbleSort(bLarge3);
    bubblefile << "500," << bubbSmall << endl;
    bubblefile << "1000," << bubbLarge1 << endl;
    bubblefile << "2000," << bubbLarge2 << endl;
    bubblefile << "5000," << bubbLarge3 << endl;

    // ==================================
    // || Insertion Sort
    // ==================================
    vector<int> iSmall = ranVect(500);
    vector<int> iLarge1 = ranVect(1000);
    vector<int> iLarge2 = ranVect(2000);
    vector<int> iLarge3 = ranVect(5000);
    int insertSmall = insertionSort(iSmall);
    int insertLarge1 = insertionSort(iLarge1);
    int insertLarge2 = insertionSort(iLarge2);
    int insertLarge3 = insertionSort(iLarge3);
    insertfile << "500," << insertSmall << endl;
    insertfile << "1000," << insertLarge1 << endl;
    insertfile << "2000," << insertLarge2 << endl;
    insertfile << "5000," << insertLarge3 << endl;

    // ==================================
    // || Selection Sort
    // ==================================
    vector<int> selSmall = ranVect(500);
    vector<int> selLarge1 = ranVect(1000);
    vector<int> selLarge2 = ranVect(2000);
    vector<int> selLarge3 = ranVect(5000);
    int selectSmall = selectionSort(selSmall);
    int selectLarge1 = selectionSort(selLarge1);
    int selectLarge2 = selectionSort(selLarge2);
    int selectLarge3 = selectionSort(selLarge3);
    selectfile << "500," << selectSmall << endl;
    selectfile << "1000," << selectLarge1 << endl;
    selectfile << "2000," << selectLarge2 << endl;
    selectfile << "5000," << selectLarge3 << endl;

    combfile.close();
    shellfile.close();
    bubblefile.close();
    insertfile.close();
    selectfile.close();

    return 0;
}