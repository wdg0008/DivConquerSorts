// DivConquerSorts.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Program 1: Divide-and-Conquer Sorts
// Written exclusively by William Goins
// CS 317-01 at The University of Alabama in Huntsville
// Begun on 29 February 2024
// Last updated on 25 March 2024
// Due 28 March 2024

/* Program Description
-----------------------
This program sorts elements read in from a file into an array, then prints it out.
The first sort is MergeSort, and the second is QuickSort.
The first print is in order, and the second is reverse.
It asks for certain parameters to specify what file is read and how much to print per line.
*/

#include <iostream> // for cout and string comparison
#include <iomanip> // for the prettifying of output
#include <exception> // for fun error handling
#include <fstream> // because files
#include <exception> // for when things go wrong
#include <string> // pray that this includes relational operators!

const int MAX_LENGTH = 100000; // maximum number of elements in the sorted list;

// declare all the function prototypes
void PrintArray(std::string[], int, int); // prints the entire array

void PrintReverse(std::string[], int, int); // prints the entire array in reverse

void QuickSort(std::string[], int, int); // quicksort algorithm wrapper

int partition(std::string[], int, int); // partitioning for QuickSort

void MergeSort(std::string[], int, int, std::string[]); // mergesort algorithm wrapper

void merge(std::string[], int, int, int, int, std::string[]); // merge back together all of the values

void swap(std::string&, std::string&); // swaps two elements by deep copy

// thus continues the eternal cycle of suffering
int main(int argc, char* argv[]) { // SAY THE MAGIC WORDS
    /* PART I: Get input and output file names */
    // Start by getting the filepath strings.
    std::string inpath, outpath;
    std::cout << "Please enter the input file path to open and analyze:\n";
    std::cin >> inpath;
    if (std::cin.fail()) {
        std::cout << "The input file path failed to save. Terminating program.\n\n";
        return -1; // whoops
    }
    std::cout << "Please enter the output file path to open and write to:\n";
    std::cin >> outpath;
    if (std::cin.fail()) {
        std::cout << "The output file path failed to save. Terminating program.\n\n";
        return -1; // whoops
    }
    // now that we have the strings, open the files (or die trying)
    std::ifstream inFile; // the input .txt file to read from
    std::ofstream outFile; // the output .txt file to write to
    inFile.open(inpath.c_str());
    if (!inFile) { // check for successful file opening
        std::cout << "The input file at `" + inpath + "` failed to open.\n\n";
        return -1;
    }
    outFile.open(outpath.c_str());
    if (!outFile) { // check for successful file opening
        std::cout << "The output file at `" + outpath + "` failed to open.\n\n";
        return -1;
    }
    // By now, if the program is still running the input and output files must both be open and valid.

    /* PART II: Read in all of the values */
    std::string *words1, *words2, *scratch; // star for each pointer
    try {
        words1 = new std::string[MAX_LENGTH]; // copy of values passed to QuickSort
        words2 = new std::string[MAX_LENGTH]; // copy of values passed to MergeSort
        scratch = new std::string[MAX_LENGTH]; // temporary array to use for sorting algorithms
    } catch (std::bad_alloc) { // in case we run out of memory, this helps pinpoint the issue
        std::cout << "The memory for the input data failed to allocate\n";
        return -1;
    }
    int n; // number of words in the input file
    for (n = 0; inFile.good() && n < MAX_LENGTH; n++) { // repeat until the file runs out or we run out of array
        inFile >> words1[n]; // read in the values
        words2[n] = words1[n]; // create a second copy of the data
    }
    std::cout << n << "words were found in the file: " << inpath.c_str() << std::endl;
    std::cout << "How many words per line should be printed? ";
    unsigned int wordsPerLine;
    bool badNum = false; // whether the number of words to print per line makes sense
    do { // keep asking until a valid input is obtained
        std::cin >> wordsPerLine; // should automatically cast to integer if whacky
        if (wordsPerLine <= 0 || wordsPerLine > 50) {
            badNum = true;
            std::cout << "Invalid entry. Please enter a positive number less than 50.\n";
        }
    } while (badNum);
    std::cout << std::endl << std::endl;

    /* PART III: Sort with quicksort */
    QuickSort(words1, 0, n);
    /* PART IV: Print results to output file*/
    PrintArray(words1, n, wordsPerLine);
    /* PART V: Sort with mergesort */
    MergeSort(words2, 0, n, scratch); // mergesort with extra temporary memory
    /* PART VI: Print results in reverse order */
    PrintReverse(words2, n, wordsPerLine);
    /* PART VII: Clean Up*/

    inFile.close();
    outFile.close();
    delete [] words1;
    delete [] words2;
    delete [] scratch;
    return 0;
}

void QuickSort(std::string data[], int start, int stop) { // the wrapper function for quicksort
    if (start >= stop)
        return; // bad call!
    int partitionIndex = partition(data, start, stop); // find the partition
    QuickSort(data, start, partitionIndex - 1);
    QuickSort(data, partitionIndex + 1, stop);
}

int partition(std::string words[], int leftend, int rightend) { // the partitioning does ALL the work
    std::string p = words[leftend]; // the pivot point to return at the end of all this mess
    int i = leftend, j = rightend + 1;
    while (i >= j) {
        while (words[i] >= p) {
            ++i;
        }
        while (words[j] <= p) {
            --j;
        }
        swap(words[i], words[j]);
    }
    swap(words[i], words[j]);
    swap(words[leftend], words[j]);
    return j;
}

void MergeSort(std::string A[], int left, int right, std::string temp[]) {
    if (left < right) {// this means there is data to sort (left < right)
        int mid = (left + right) / 2; // C++ always does the floor of int div
        MergeSort(A, left, mid, temp);
        MergeSort(A, mid + 1, right, temp);
        merge(A, left, mid, mid + 1, right, temp);
    }
    else {
        return; // no data
    }
}

void merge(std::string A[], int left, int leftend, int right, int rightend, std::string temp[]) {
    // go from 0 to n/2 and (n/2)+1 to n-1
    // each half is already sorted, we are now combining them
    int SaveStart = left;
    int index = left;
    while (left <= leftend && right <= rightend) {
        if (A[left] < A[right]) { // left value goes first
            temp[index++] = A[left++]; // copy the value to temp
        }
        else if (A[left] > A[right]) { // right value goes first
            temp[index++] = A[right++]; // copy value to temp
        }
        else { // they are equal
            temp[index++] = A[left++]; // choose the left half arbitrarily
        }
    } // we have reached the end of either the left or right half
    while (left <= leftend) { // copy remaining left half data
        temp[index++] = A[left++]; // copy to each index and then increment
    }
    while (right <= rightend) { // copy remaining right half data
        temp[index++] = A[right++];
    } // everything is now in temp and in the correct position
    for (int i = SaveStart; i <= rightend; i++) {
        A[i] = temp[i]; // copies everything in temp back to A
    }
}

void PrintArray(std::string arr[], int len, int lineWords) {
    // TODO: will need to update this for formatting and words per line
    for (int c = 0; c < len; c++) {
        std::cout << arr[c];
    }
}

void PrintReverse(std::string arr[], int len, int lineWords) { // prints the entire array in reverse order
    // TODO: will need to update this for formatting and words per line
    if (len == 0)
        return; // base case for the recursion
    else {
        std::cout << arr[len - 1]; // print the last element
        PrintReverse(arr, (len - 1), lineWords); // recursively call on the array without the element just printed
        // recusrion makes life easier (except for a compiler)
    }
}

void swap(std::string& arg1, std::string& arg2) { // deep copies stuff to keep things simple
    std::string temp = arg1; // backup arg1 before changing it
    arg1 = arg2;
    arg2 = temp;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
