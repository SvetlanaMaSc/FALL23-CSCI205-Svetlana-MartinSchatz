#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>

using namespace std;

/**
 * Constant Time
 */
int *constantTime(vector<int> nums)
{
    int n = nums.size();
    int half = nums.size() / 2;
    // return the middle item, problem size and the loop count (which here is just 1 because there is no loop)
    int* ret = new int[3] {nums[half], n, 1};
    return ret;
}

/**
 * Linear Time
 */
int *linearTime(vector<int> nums)
{
    int n = nums.size();
    int min = nums[0];
    int max = nums[0];
    int counts = 0;
    // Find the largest and smallest number
    for (size_t i = 0; i < nums.size(); i++)
    {
        int num = nums[i];
        if (num < min)
        {
            min = num;
        }
        if (num > max)
        {
            max = num;
        }
        counts++;
    }
    // Calculate range
    int range = max - min;
    // return range, n, and couts
    int* ret = new int[3] {range, n, counts};
    return ret;
}

/**
 * Exponential Time
 * 
 * I could not come up with a wayy to make this have exponential growth.
 */
int* exponentialTime(int x, int n)
{
    int counts = 0;
    int result = 1;
    for (int i = 0; i < n; i++) {
        result *= x;
        counts++;
    }

    // return power, n, and counts
    int* ret = new int[2] {result, counts};
    return ret;
}

/**
 * Max Element
 *
 */
int* maxElement(vector<vector<int>> matrix)
{

    int n = matrix.size() * matrix[0].size();
    int rows = (matrix.size()) - 1;
    int cols = (matrix[0].size()) - 1;
    int largest = 0;
    int counts = 0;
    for (int i = 0; i < cols; i++)
    {
        counts++;
        for (int j = 0; j < rows; j++)
        {
            counts++;
            int a = matrix[i][j];
            if (a > largest)
            {
                largest = a;
            }
        }
    }

    // return largest, n, and counts
    int* ret = new int[3] {largest, n, counts};
    return ret;
}

/**
 * Factorials
 */
int* factorial(int limit)
{
    int n = limit;
    int total = 1;
    int counts = 0;
    for (int i = 1; i < limit + 1; i++)
    {
        total *= i;
        counts++;
    }

    int* ret = new int[3] {total, n, counts};
    return ret;
}

/**
 * Fibonacci Series
 */
int* fibonacci(int limit)
{
    int n = limit;
    int counts = 0;
    int first = 0;
    int second = 1;
    for (int i = 0; i < limit + 1; i++)
    {
        int next = first + second;
        first = second;
        second = next;
        counts++;
    }

    int* ret = new int[2] {n, counts};
    return ret;
}

/**
 * Prime Numbers
 */
int *primes(int num) 
{
    int n = num;
    int isPrime = 1;
    int sqrtN = sqrt(num);
    int counts = 0;

    for (int i = 2; i <= sqrtN; i++)
    {
        counts++;
        if (num % i == 0)
        {
            isPrime = 0;
            break;
        }
    }

    int* ret = new int[3] {isPrime, n, counts};
    return ret;
}

/**
 * Matrix Multiplication
 */
int *matrix(vector<vector<int>> m1, vector<vector<int>> m2)
{
    int total = 0;
    int counts = 0;
    // Check if rows == cols
    int m1rows = (m1.size()) - 1;
    int m1cols = (m1[0].size())- 1;
    int m2rows = (m2.size()) - 1;
    int m2cols = (m2[0].size()) - 1;
    int n = (m1rows * m1cols) + (m2rows * m2cols);
    for (int i = 0; i < m1cols; i++)
    {
        vector<int> colToCalc;
        vector<int> rowToCalc;
        for (int j = 0; j < m2rows; j++)
        {
            int a = m2[j][i];
            colToCalc.push_back(a);
            counts++;
        }
        for (int k = 0; k < m1cols; k++)
        {
            int b = m1[i][k];
            rowToCalc.push_back(b);
            counts++;
        }
        // multiply
        for (size_t l = 0; l < rowToCalc.size(); l++)
        {
            int row = rowToCalc[l];
            int col = colToCalc[l];
            total += row * col;
            counts++;
        }
    }

    int* ret = new int[3] {total, n, counts};
    return ret;
}

/**
 * Primes Up to One Million
 *
 */
int* primesOneMil(int limit)
{
    int n = limit;
    vector<int> nums;
    int counts = 0;
    // build the array
    for (int i = 2; i < limit + 1; i++)
    {
        nums.push_back(i);
    }
    for (size_t i = 0; i < nums.size(); i++)
    {
        counts++;
        for (size_t j = 0; j < nums.size(); j++)
        {
            counts++;
            int numI = nums[i];
            int numJ = nums[j];
            if (numJ % numI == 0 && numJ >= pow(numI, 2))
            {
                vector<int>::iterator it = std::find(nums.begin(), nums.end(), numJ);

                nums.erase(it);
            }
        }
    }

    int* ret = new int[3] {n, counts};
    return ret;
}

int printToText(vector<int> problemSize, vector<int> counts, string title)
{
    ofstream outputFile(title + ".txt");

    if (!outputFile.is_open())
    {
        cerr << "Failed to open the file." << std::endl;
        return 1; // Return an error code
    }

    for (size_t i = 0; i < problemSize.size(); i++)
    {
        outputFile << problemSize[i] << " " << counts[i] << endl;
    }

    outputFile.close();
    return 0;
}

vector<vector<int>> buildRandomVector(int size)
{
    // Makes a vector to carry the arrays
    srand(std::time(nullptr));
    vector<vector<int>> arrays1;
    vector<int> arrays2;
    arrays1.reserve(size);
    int a = 10;

    for (int i = 1; i < size; i++)
    {
        // generate a random length for the array
        int length = i * 10;
        for (int j = 0; j < length; j++)
        {
            // generate a random number
            arrays2.push_back(rand() % 10000 + 1);
        }
        arrays1.push_back(arrays2);
        arrays2.clear();
        a += 10;
    }

    return arrays1;
}

vector<vector<int>> buildRandomVector(int cols, int rows) {
        // Makes a vector to carry the arrays
    vector<vector<int>> arrays1;
    vector<int> arrays2;
    int a = 10;

    for (int i = 1; i < cols + 1; i++)
    {
        // generate a random length for the array
        int length = i * 10;
        for (int j = 0; j < rows; j++)
        {
            // generate a random number
            arrays2.push_back(rand() % 10000 + 1);
        }
        arrays1.push_back(arrays2);
        arrays2.clear();
        a += 10;
    }

    return arrays1;
}

/**
 * Loops through the time functions to calculate the notation and plot the graph
 */
void timeLoop()
{
    vector<int> ct_counts;
    /**
     * Constant Time
     */
    // Build random vector of vectors
    vector<vector<int>> ct_vector = buildRandomVector(100);
    // Cycle through arrays
    vector<int> ns;
    vector<int> counts;
    for (size_t i = 0; i < ct_vector.size(); i++)
    {
        int *ret = constantTime(ct_vector[i]);
        ns.push_back(ret[1]);
        counts.push_back(ret[2]);
        printToText(ns, counts, "constant_time.txt");
    }

    /**
     * Linear Time
     */
    vector<vector<int>> lin_vector = buildRandomVector(100);
    ns.clear();
    counts.clear();
    for (size_t i = 0; i < lin_vector.size(); i++) {
        int* ret = linearTime(lin_vector[i]);
        ns.push_back(ret[1]);
        counts.push_back(ret[2]);
        printToText(ns, counts, "linear_time.txt");
    }

    /**
     * Exponential Time
    */
    ns.clear();
    counts.clear();
    for (int i = 1; i < 100; i++) {
        int* ret = exponentialTime(i, i * 2);
        ns.push_back(ret[0]);
        counts.push_back(ret[1]);
        printToText(ns, counts, "exponential_time.txt");
    }

    /**
     * Max Element
    */
    ns.clear();
    counts.clear();    
    for (int i = 1; i < 100; i++) {
        vector<vector<int>> m = buildRandomVector(i * 10);
        int* ret = maxElement(m);
        ns.push_back(ret[1]);
        counts.push_back(ret[2]);
        printToText(ns, counts, "max_element_time.txt");
    }
    cout << "done" << endl;

    /**
     * Factorial
    */
    ns.clear();
    counts.clear();
    for (int i = 1; i < 100; i++) {
        int* ret = factorial(i * 10);
        ns.push_back(ret[1]);
        counts.push_back(ret[2]);
        printToText(ns, counts, "factorial_time.txt");
    }

    /**
     * Fibonacci
    */
    ns.clear();
    counts.clear();
    for (int i = 1; i < 100; i++) {
        int* ret = fibonacci(i * 10);
        ns.push_back(ret[0]);
        counts.push_back(ret[1]);
        printToText(ns, counts, "fibonacci_time.txt");
    }

    /**
     * Prime Numbers
    */
    ns.clear();
    counts.clear();
    for (int i = 1; i < 100; i++) {
        int* ret = primes(i * 10);
        ns.push_back(ret[1]);
        counts.push_back(ret[2]);
        printToText(ns, counts, "prime_time.txt");
    }

    /**
     * Matrix Multiplication
    */
    ns.clear();
    counts.clear();
    for (int i = 1; i < 1000; i++) {
        vector<vector<int>> a = buildRandomVector(rand() % 100 + 1); 
        // get column and row length
        int rows = (a.size());
        int cols = (a[0].size());
        vector<vector<int>> b = buildRandomVector(cols, rows); 
        int* ret = matrix(a, b);
        ns.push_back(ret[1]);
        counts.push_back(ret[2]);
        printToText(ns, counts, "matrix_time.txt");
    }

    /**
     * Primes Up to One Million
    */
    ns.clear();
    counts.clear();
    for (int i = 0; i < 100; i++) {
        int* ret = primesOneMil(i * 10);
        ns.push_back(ret[1]);
        counts.push_back(ret[2]);
        printToText(ns, counts, "prime_one_million_time.txt");
    }
    // clock_t start = clock();								// start
    // primesOneMil(1000000);
	// clock_t end = clock();									// end clock
	// double time = (double)(end - start) / CLOCKS_PER_SEC;	// compute time
    // cout << "time: " << time << endl;
}

int main()
{
    timeLoop();
}