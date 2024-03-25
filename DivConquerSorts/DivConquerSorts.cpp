// DivConquerSorts.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Program 1: Divide-and-Conquer Sorts
// Written exclusively by William Goins
// CS 317-01 at The University of Alabama in Huntsville
// Begun on 29 February 2024
// Last updated on 19 March 2024
// Due 28 March 2024

/* Program Desxription
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

constexpr auto MAX_LENGTH = 100000; // maximum number of elements in the sorted list;

// declare all the function prototypes
template <typename DataType>
void PrintArray(DataType[], int, int);

template <typename DataType>
void PrintReverse(DataType[], int, int);

template <typename DataType>
void QuickSort(DataType[], int, int, DataType[]); // quicksort algorithm generic

template <typename DataType>
void MergeSort(DataType[], int, int, DataType[]); // mergesort algorithm generic

template <typename DataType>
void swap(DataType&, DataType&); // swaps two elements by deep copy

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
    std::ifstream inFile;
    std::ofstream outFile;
    inFile.open(inpath.c_str());
    if (!inFile) {
        std::cout << "The input file at `" + inpath + "` failed to open.";
        return -1;
    }
    outFile.open(outpath.c_str());
    if (!outFile) {
        std::cout << "The output file at `" + outpath + "` failed to open.";
        return -1;
    }
    // By now, if the program is still running the input and output files must both be open and valid.

    /* PART II: Read in all of the values */
    
    /* PART III: Sort with quicksort */
    /* PART IV: Print results to output file*/
    /* Part V: Sort with mergesort */
    /* PART VI: Print results in reverse order */
    inFile.close();
    outFile.close();
    return 0;
}

template <typename DataType>
void PrintArray(DataType arr[], int len, int lineWords) {
    // TODO: will need to update this for formatting and words per line
    for (int c = 0; c < len; c++) {
        std::cout << arr[c];
    }
}

template <typename DataType> // works for any data type, unless I screw it up :P
void PrintReverse(DataType arr[], int len, int lineWords) { // prints the entire array in reverse order
    // TODO: will need to update this for formatting and words per line
    if (len == 0)
        return; // base case for the recursion
    else {
        std::cout << arr[len - 1]; // print the last element
        PrintReverse(arr, len - 1); // recursively call on the array without the element just printed
        // recusrion makes life easier (except for a compiler)
    }
}

template <typename DataType>
void swap(DataType& arg1, DataType& arg2) { // deep copies stuff to keep things simple
    DataType temp = arg1; // backup arg1 before changing it
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
