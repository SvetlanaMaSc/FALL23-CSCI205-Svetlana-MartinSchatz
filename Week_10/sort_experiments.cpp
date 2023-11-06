#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <ctime>
using namespace std;

void quickSort(vector<int> &avector, int first, int last);
int  partition(vector<int> &avector, int first, int last);
int  partition2(vector<int> &avector, int low, int high);
int  medianOf3(vector<int> &v, int left, int right);
void printl(vector<int> avector);

int comparisonCount = 0;
int swapCount  = 0;
int memoryCount = 0;

void swap(vector<int>& vec, int a, int b){
	int temp	= vec[a];
	vec[a]		= vec[b];
	vec[b]		= temp;
}

void resetCounters() {
	comparisonCount = 0;
	swapCount = 0;
	memoryCount = 0;
}


//recursive function that quicksorts a given vector
// Big O: time -> O(n log n) where n is the vector size, space -> O(1)
void quickSort(vector<int> &avector, int first, int last) {
	int splitpoint = 0;	// partition splitpoint index

	if (first<last) {									// if there is more than one element in the vector
		comparisonCount++;
		splitpoint = partition(avector, first, last);	// partition the vector from first to last
		//splitpoint = partition2(avector, first, last);
		quickSort(avector, first, splitpoint - 1);		// lower half
		memoryCount++;
		quickSort(avector, splitpoint + 1, last);		// upper half
		memoryCount++;
	}
}

void insertionSort(vector<int> &avector, int first, int last) {
    for (int i = first+1; i <= last; i++) {
		memoryCount++;
        int key = avector[i];
        int j = i - 1;
        while (j >= first && avector[j] > key) {
			comparisonCount += 2;
			memoryCount += 2;
            avector[j+1] = avector[j];
			memoryCount += 2;
            j = j - 1;
        }
        avector[j+1] = key;
		memoryCount++;
    }
}

void quickSort2(vector<int> &avector, int first, int last) {
    if (first+10 <= last) { // Cutoff for insertion sort
        int splitpoint = partition(avector, first, last);
        quickSort(avector, first, splitpoint - 1);
        quickSort(avector, splitpoint + 1, last);
    } else {
        insertionSort(avector, first, last);
    }
}

void threeWay(vector<int> &avector, int pivot) {
	int i = 0;
	int j = 0;
	int n = avector.size() - 1;
	while (j < n) {
		comparisonCount++;
		if (avector[j] < pivot) {
			comparisonCount++;
			memoryCount++;
			swap(avector[j], avector[i]);
			swapCount++;
			i++;
			j++;
		}
		else if (avector[j] == pivot) {
			comparisonCount++;
			memoryCount++;
			j++;
		}
		else {
			swap(avector[j], avector[n]);
			swapCount++;
			memoryCount += 2;
			j--;
			n--;
		}
	}
}
 
//function partitions vector around a pivot value
// returns the splitpoint index
// Big O: time -> O(n) where n is the sub-vector size, space -> O(1)
int partition(vector<int> &avector, int first, int last){
	int pivotValue = avector[last];	// grab the pivot (lazy approach: either first, last or middle element)
	memoryCount++;
	//int pivotValue = medianOf3(avector, first, last);

	int rightmark  = last - 1;		// establish right pointer
	int leftmark   = first;			// establish left pointer

	bool done = false;				// flag to indicate when done


	while (!done){					// while not done
		comparisonCount++;
		// increment left pointer until a value larger than the pivot is found
		// while pointers haven't crossed and value at left pointer is less than or equal to pivot
		while (leftmark <= rightmark && avector[leftmark] <= pivotValue) {
			comparisonCount++;
			memoryCount++;
			leftmark++;
		}

		// decrement right pointer until a value smaller than the pivot is found
		// while pointers haven't crossed and value at right pointer is greater than or equal to pivot
		while (rightmark >= leftmark && avector[rightmark] >= pivotValue) {
			comparisonCount++;
			memoryCount++;
			rightmark--;
		}
		
		if (rightmark < leftmark) {
			comparisonCount++;
			done = true;
		}				// if pointers cross, the partition is done
		else {
			swap(avector[rightmark], avector[leftmark]);
			swapCount++;
			memoryCount += 3;
		}	// pointers haven't crossed, perform a swap
	}
	
	// partition is done, put pivot in it's place. This will be it's final place in the sorted vector
	swap(avector[leftmark], avector[last]);
	swapCount++;	// place the pivot at splitpoint
	return leftmark;						// return split point
}

// function partitions vector around a pivot value
// Big O: time -> O(n) where n is the sub-vector size, space -> O(1)
int partition2(vector<int> &avector, int low, int high){
	// pivot (Element to be placed at right position)
	//int pivot = avector[high];				// grab the pivot (lazy approach: either first, last or middle element)

	int pivot = medianOf3(avector, low, high);	// better pivot choice
	int i = low - 1; 							// marker for the partition split point

	// traverse through all elements, compare each element with pivot
	// place smaller elements at the beginning of the partition (position i)
	for (int j = low; j <= high - 1; j++){
		memoryCount++;
		if (avector[j] < pivot){				// If current element is smaller than the pivot
			memoryCount++;
			comparisonCount++;
			i++; 								// increment index of smaller element
			swap(avector[i], avector[j]);		// swap items at i and j (j being smaller than pivot)
			swapCount++;
			memoryCount += 3;

		}
	}

	swap(avector[i + 1], avector[high]);		// after partitioning, put pivot in it's place at splitpoint
	swapCount++;
	memoryCount += 3;
	return i + 1;								// return the splitpoint
}

// function returns the median of three values (left, center, right)
// Big O: time -> O(1), space -> O(1)
int medianOf3(vector<int> &v, int left, int right){
	int center = (left + right) / 2;	// find center
	swap(v[left], v[center]);			// get ready to sort the three
	swapCount++;
	if( v[left] > v[right] ) {
		comparisonCount++;
		memoryCount += 2;
		swap(v[left], v[right]);		// swap if necessary
		swapCount++;
		memoryCount += 3;
	}			// look at left and right
	if(v[center] > v[right] ) {
		comparisonCount++;
		memoryCount += 2;
		swap(v[center], v[right]);		// swap if necessary
		swapCount++;
		memoryCount += 3;
	}			// look at center and right
	swap(v[center], v[right]);			// put pivot on right
	swapCount++;
	memoryCount += 4;
	return v[right];					// return pivot value
}

int tukeysNinther(vector<int> &v, int left, int right) {
    int length = right - left + 1;
    int step = length / 3; // dividing array into thirds

    // Finding medians of thirds using your medianOf3 function
    int median1 = medianOf3(v, left, left + step - 1);
    int median2 = medianOf3(v, left + step, left + 2 * step - 1);
    int median3 = medianOf3(v, left + 2 * step, right);

    // Creating a small array to store medians
    vector<int> medians = {median1, median2, median3};
	memoryCount += 4;

    // Finding and returning the median of the medians (ninther)
    return medianOf3(medians, 0, 2);
}

void dualPivotQuickSort(vector<int> &v, int left, int right) {
    if (left < right) {
        // Choose two pivots
        int P1 = v[left];   // Pivot 1
		memoryCount++;
        int P2 = v[right];  // Pivot 2
		memoryCount++;
        if (P1 > P2) {
			comparisonCount++;
			
            swap(v[left], v[right]);
			swapCount++;
			memoryCount += 3;
            P1 = v[left];
			memoryCount++;
            P2 = v[right];
			memoryCount++;
        }
        // Initialize pointers
        int L = left + 1;
        int G = right - 1;
        int K = L;
        
        while (K <= G) {
			comparisonCount++;
            // If current element is less than P1
            if (v[K] < P1) {
				memoryCount += 2;
				memoryCount++;
                swap(v[K], v[L]);
				swapCount++;
				memoryCount += 3;
                L++;
            }
            // If current element is greater than P2
            else if (v[K] > P2) {
				comparisonCount++;
				memoryCount += 2;
                while (v[G] > P2 && K < G) {
					memoryCount += 2;
					comparisonCount++;
                    G--;
                }
                swap(v[K], v[G]);
				swapCount++;
				memoryCount += 3;
                G--;
                if (v[K] < P1) {
					comparisonCount += 2;
					memoryCount++;
                    swap(v[K], v[L]);
					swapCount++;
					memoryCount += 3;
                    L++;
                }
            }
            K++;
        }
        L--;
        G++;

        // Swap pivots to final position
        swap(v[left], v[L]);
		swapCount++;
		memoryCount += 3;
        swap(v[right], v[G]);
		swapCount++;
		memoryCount += 3;

        // Recursively sort sub-arrays
        dualPivotQuickSort(v, left, L - 1);
        dualPivotQuickSort(v, L + 1, G - 1);
        dualPivotQuickSort(v, G + 1, right);
    }
}

/**
 * Kept getting a quick_sort.cpp:312:14: error: no matching function for call to ‘merge(std::vector<int>&, std::vector<int>&, std::vector<int>&)’
  312 |         merge(avector, lefthalf, righthalf);
      |      
	  errior and nothing i did ixed it
*/
// vector<int> mergeSort(vector<int> avector) {
// 	int size = avector.size();				// get vector size
// 	if (size>1) {							// base case, range of 1 is sorted
// 		int mid = size/2;					// calculate mid point

// 		// split vector at midpoint: auxiliary memory created. These are new vectors
// 		vector<int> lefthalf(avector.begin(),avector.begin()+mid);
// 		vector<int> righthalf(avector.begin()+mid,avector.begin()+size);

// 		// merge sort the halves
// 		lefthalf  = mergeSort(lefthalf);	// recursive call to mergeSort the left half
// 		righthalf = mergeSort(righthalf);	// recursive call to mergeSort the right half
		
// 		// merge sorted sub vectors back into original vector
// 		merge(avector, lefthalf, righthalf);
// 	}
// 	return avector;
// }

// // function merges two sorted vectors
// // Big O: time -> O(n) where n is the sub-vector size, space -> O(1)
// void merge(vector<int> &avector, vector<int> left, vector<int> right){
// 	unsigned i = 0;	// left vector index
// 	unsigned j = 0;	// right vector index
// 	unsigned k = 0;	// merged vector index

// 	// while there are elements in both sub vectors
// 	while (i < left.size() && j < right.size()){
// 		comparisonCount += 2;
// 		if (left[i] < right[j]) {
// 			comparisonCount++;
// 			memoryCount += 2;
// 			avector[k] = left[i++];		// copy from left
// 			memoryCount += 2;
// 			swapCount++;
// 		}
// 		else {
// 			avector[k] = right[j++];	// copy from right
// 			memoryCount += 2;
// 			swapCount++;
// 		}
// 		k++;
// 	}
// 	// one of the vectors is exhausted. Can unconditionally copy from here
// 	while (i < left.size()) {
// 		comparisonCount++;
// 		avector[k++] = left[i++];		// copy from left
// 		memoryCount += 2;
// 		swapCount++;
// 	}

// 	while (j < right.size()) { 
// 		avector[k++] = right[j++];		// copy from right
// 		memoryCount += 2;
// 		swapCount++;
// 	}
// }


//utility function to print a vector
void printl(vector<int> avector){
	for (unsigned i = 0; i < avector.size(); i++)
		cout << avector[i] << " ";
	cout << endl;
}



int main(){
	// ==================================
	// || I ran this program multiple times with things commented out to get all the plot points needed
	// ==================================

	/**
	 * Experiment 1
	*/
	// ofstream graph1("experiment_1_quicksort_with_lazy_pivot.txt");
	// // // int worst_case[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	// // // int arr[] = {54, 26, 93, 17, 77, 31, 44, 55, 47};
	// // //int arr[] = {6, 9, 4, 3, 10, 5, 7, 8, 1, 2};
	// // //vector<int> avector(worst_case, worst_case + sizeof(worst_case) / sizeof(worst_case[0]));
	// for (int size = 5; size <= 50; size += 5) {
	// // 	// create a inversely sorted vector of size
	// 	vector<int> avector(size);
	// 	iota(avector.begin(), avector.end(), 1);
	// 	reverse(avector.begin(), avector.end());
	// 	clock_t start = clock();
	// 	quickSort(avector, 0, avector.size() - 1);
	// 	clock_t end = clock();
	// 	double timeTaken = double (end - start) / CLOCKS_PER_SEC;
	// 	graph1 << size << " " << timeTaken << endl;
	// }
	// graph1.close();
	// resetCounters();
	/**
	 * Experimment 2
	*/
	// ofstream graph2("experiment_2_quicksort_comparisons.txt");
	// ofstream graph3("experiment_2_quicksort_swaps.txt");
	// ofstream graph4("experiment_2_median_comparisons.txt");
	// ofstream graph5("experiment_2_median_swaps.txt");
	// ofstream graph6("experiment_2_tukey_comparisons.txt");
	// ofstream graph7("experiment_2_tukey_swaps.txt");
	// for (int size = 5; size <= 50; size += 5) {
		// create a inversely sorted vector of size
		// vector<int> avector(size);
		// iota(avector.begin(), avector.end(), 1);
		// reverse(avector.begin(), avector.end());
		// quickSort(avector, 0, avector.size() - 1);
		// graph2 << size << " " << comparisonCount << endl;
		// graph3 << size << " " << swapCount << endl;
		// resetCounters();
		// medianOf3(avector, 0, avector.size() - 1);
		// graph4 << size << " " << comparisonCount << endl;
		// graph5 << size << " " << swapCount << endl;
		// resetCounters();
		// tukeysNinther(avector, 0, avector.size() - 1);
		// graph6 << size << " " << comparisonCount << endl;
		// graph7 << size << " " << swapCount << endl;
		// resetCounters();
	// }
	// graph2.close();
	// graph3.close();
	// graph4.close();
	// graph5.close();
	// graph6.close();
	// graph7.close();
	/**
	 * Experiment 3
	*/
	// ofstream graph8("experiment_3_dualpivot_memory.txt");
	// ofstream graph9("experiment_3_dualpivot_memory_with_cutoff.txt");
	// ofstream graph10("experiment_3_median_memory.txt");
	// ofstream graph11("experiment_3_median_memory_with_cutoff.txt");
	// ofstream graph12("experiment_3_Tukey's_memory.txt");
	// ofstream graph13("experiment_3_Tukey's_memory_with_cutoff.txt");
	// for (int size = 5; size <= 50; size += 5) {
	// 	// create a inversely sorted vector of size
	// 	vector<int> avector(size);
	// 	iota(avector.begin(), avector.end(), 1);
	// 	reverse(avector.begin(), avector.end());
	// 	dualPivotQuickSort(avector, 0, avector.size() - 1);
	// 	graph8 << size << " " << memoryCount << endl;
	// 	resetCounters();
	// 	medianOf3(avector, 0, avector.size() - 1);
	// 	graph10 << size << " " << memoryCount << endl;
	// 	resetCounters();
	// 	tukeysNinther(avector, 0, avector.size() - 1);
	// 	graph12 << size << " " << memoryCount << endl;
	// 	resetCounters();
	// }
	// for (int size = 5; size <= 50; size += 5) {
	// 	// create a inversely sorted vector of size
	// 	vector<int> avector(size);
	// 	if (size <= 15) {
	// 		insertionSort(avector, 0, avector.size() - 1);
	// 	}
	// 	else {
	// 		iota(avector.begin(), avector.end(), 1);
	// 		reverse(avector.begin(), avector.end());
	// 		dualPivotQuickSort(avector, 0, avector.size() - 1);
	// 		graph9 << size << " " << memoryCount << endl;
	// 		resetCounters();
	// 		medianOf3(avector, 0, avector.size() - 1);
	// 		graph11 << size << " " << memoryCount << endl;
	// 		resetCounters();
	// 		tukeysNinther(avector, 0, avector.size() - 1);
	// 		graph13 << size << " " << memoryCount << endl;
	// 		resetCounters();
	// 	}
	// }
	// graph8.close();
	// graph9.close();
	// vector<int> avector(arr, arr + sizeof(arr) / sizeof(arr[0]));

	// printl(avector);
	// quickSort(avector, 0, avector.size() - 1);
	// printl(avector);
	/**
	 * Experiment 4
	*/
	// ofstream graph14("experiment_4_dualpivot_swaps.txt");
	// ofstream graph15("experiment_4_threeway_swaps.txt");
	// ofstream graph16("experiment_4_median_swaps.txt");
	// ofstream graph17("experiment_4_tukeys_swaps.txt");
	// ofstream graph18("experiment_4_dualpivot_comparisons.txt");
	// ofstream graph19("experiment_4_threeway_comparisons.txt");
	// ofstream graph20("experiment_4_median_comparisons.txt");
	// ofstream graph21("experiment_4_tukeys_comparisons.txt");
	// for (int size = 5; size <= 50; size += 5) {
	// 	// create a inversely sorted vector of size
	// 	vector<int> avector(size);
	// 	iota(avector.begin(), avector.end(), 1);
	// 	reverse(avector.begin(), avector.end());
	// 	quickSort(avector, 0, avector.size() - 1);
	// 	// graph14 << size << " " << comparisonCount << endl;
	// 	graph18 << size << " " << swapCount << endl;
	// 	resetCounters();
	// 	threeWay(avector, 10);
	// 	// graph15 << size << " " << comparisonCount << endl;
	// 	graph19 << size << " " << swapCount << endl;
	// 	resetCounters();
	// 	medianOf3(avector, 0, avector.size() - 1);
	// 	// graph16 << size << " " << comparisonCount << endl;
	// 	graph20 << size << " " << swapCount << endl;
	// 	resetCounters();
	// 	tukeysNinther(avector, 0, avector.size() - 1);
	// 	// graph17 << size << " " << comparisonCount << endl;
	// 	graph21 << size << " " << swapCount << endl;
	// 	resetCounters();
	// }

	return 0;
}