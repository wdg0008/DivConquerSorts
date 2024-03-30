// DivConquerSorts.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Program 1: Divide-and-Conquer Sorts
// Written exclusively by William D. Goins V (a.k.a. "Quin")
// CS 317-01 at The University of Alabama in Huntsville
// Begun on 29 February 2024
// Last updated on 29 March 2024
// Due 29 March 2024

/* Program Description
-----------------------
This program sorts elements read in from a file into an array, then prints it out.
The first sort is MergeSort, and the second is QuickSort.
The first print is in order, and the second is reverse.
It asks for certain parameters to specify what file is read and how much to print per line.
*/

#include <iostream>  // for cout and string comparison
#include <iomanip>   // for the prettifying of output
#include <exception> // for fun error handling
#include <fstream>   // because files
#include <exception> // for when things go wrong
#include <string>    // pray that this includes relational operators!
#include <locale>    // I need the tolower function!

const int MAX_LENGTH = 100000; // maximum number of elements in the sorted list;
const int FIELD_WIDTH = 16; // field width for writing output to file

void PrintArray(const std::string[], int, int, std::ofstream&); // prints the entire array

void ReverseArray(std::string[], int, int); // reverse the contents of the array

void QuickSort(std::string[], int, int); // quicksort algorithm wrapper

int partition(std::string[], int, int); // partitioning for QuickSort

void MergeSort(std::string[], int, int, std::string[]); // mergesort algorithm wrapper

void merge(std::string[], int, int, int, int, std::string[]); // merge back together all of the values

void TestDump(const std::string[], int, int); // prints entire array of strings to cout

std::string LowerString(const std::string&); // returns the ASCII lowercase of the argument

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
        std::cout << "The memory for the input data failed to allocate. Terminating program.\n\n";
        return -1;
    }
    int n; // number of words in the input file
    for (n = 0; inFile.good() && n < MAX_LENGTH; n++) { // repeat until the file runs out or we run out of array
        inFile >> words1[n]; // read in the values
        words2[n] = words1[n]; // create a second copy of the data
    }
    std::cout << n << " words were found in the file: " << inpath.c_str() << std::endl;
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
    // TestDump(words1, n, wordsPerLine); // TODO: REMOVE BEFORE FLIGHT!!!!!!

    /* PART III: Sort with quicksort */
    QuickSort(words1, 0, n-1);
    /* PART IV: Print results to output file*/
    outFile << n << " words were sorted using quicksort:\n\n";
    PrintArray(words1, n, wordsPerLine, outFile); // print the sorted results to the file
    /* PART V: Sort with mergesort */
    MergeSort(words2, 0, n-1, scratch); // mergesort with extra temporary memory
    /* PART VI: Print results in reverse order */
    outFile << n <<  " words were sorted using mergesort, printed in reverse order:\n\n";
    ReverseArray(words2, 0, n - 1); // reverse the array instead of writing another print :P
    PrintArray(words2, n, wordsPerLine, outFile); // print reverse sorted results to file
    /* PART VII: Clean Up*/

    inFile.close();
    outFile.close();
    delete[] words1;
    delete[] words2;
    delete[] scratch;
    return 0;
}

void QuickSort(std::string data[], int start, int stop) { // the wrapper function for quicksort
    if (start < stop) { // the call is valid because there are elements to sort
        int partitionIndex = partition(data, start, stop); // find the partition
        QuickSort(data, start, partitionIndex - 1);
        QuickSort(data, partitionIndex + 1, stop);
        // TestDump(data, stop - start, 5); // TODO: REMOVE BEFORE FLIGHT!!!!!
    }
    return; // skips to here on a bad call, arrives here on a good one
}

int partition(std::string words[], int leftend, int rightend) { // the partitioning does ALL the work
    std::string pivot = words[(leftend+rightend)/2]; // the pivot point to start the chaos
    // the pivot is selected at the middle in case it is already sorted
    pivot = LowerString(pivot); // comparisons should all be based on lowercase strings
    int i = leftend - 1; // left-hand iteraror variable
    int j = rightend + 1; // right-hand iterator variable
    while (true) { // looks weird, but lets the return be more elegant
        do { // do-whiles ensure that variables are always valid indices
            i++; // moves i from Left to Right (LTR)
        } while (LowerString(words[i]).compare(pivot) < 0);
        do {
            j--; // moves j from RIght to Left (RTL)
        } while (LowerString(words[j]).compare(pivot) > 0);
        if (i >= j) // we got to the middle
            return j; // all done here
        std::swap(words[i], words[j]); // swaps like the book, but doesn't have to undo
    }
}

void MergeSort(std::string A[], int left, int right, std::string temp[]) {
    if (left < right) { // this means there is data to sort (left < right)
        int mid = (left + right) / 2; // C++ always does the floor of int div
        MergeSort(A, left, mid, temp);
        MergeSort(A, mid + 1, right, temp);
        merge(A, left, mid, mid + 1, right, temp);
        // TestDump(A, left - right, 5); // TODO: REMOVE BEFORE FLIGHT!!!!!
    }
    return; // explicit calls to return make me happier (not much, but it helps)
}

void merge(std::string A[], int left, int leftend, int right, int rightend, std::string temp[]) {
    // go from 0 to n/2 and (n/2)+1 to n-1
    // each half is already sorted, we are now combining them
    int SaveStart = left;
    int index = left;
    while (left <= leftend && right <= rightend) { // is this correct? Might should be >= leftend
        // all comparisons are based on lowercase version of ASCII strings
        // the LowerString.compare part kind of hurt to write, but the lecture helped a lot.
        if (LowerString(A[left]).compare(LowerString(A[right])) < 0) { // left value goes first
            temp[index++] = A[left++]; // copy the value to temp
        }
        else if (LowerString(A[left]).compare(LowerString(A[right])) > 0) { // right value goes first
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

void PrintArray(const std::string arr[], int len, int lineWords, std::ofstream& writeFile) { // prints out the entire array
    int c; // counter accessible to rest of function
    for (c = 0; c < len / lineWords; c++) { // repeat for every FULL line
        for (int i = 0; i < lineWords; i++) { // repeat within the line for each slot
            writeFile << std::setw(FIELD_WIDTH) << std::right << arr[c * lineWords + i] << ',';
        } // there may still be a few characters in a partial line
        writeFile << std::endl;
    }
    for (int i = c * lineWords; i < len; i++) { // prints out the last few words that are not a complete line
        writeFile << std::setw(FIELD_WIDTH) << std::right << arr[len - i] << ',';
    } // FINISH HIM!!!
    writeFile << std::endl << std::endl; // make room for the next best thing
    return;
}

void ReverseArray(std::string arr[], int start, int end) { // reorders the array to reverse its elements
    while (start < end) { // no overlap, but bring them together
        std::swap(arr[start], arr[end]); // man this function is so useful
        start++; // creep towards the center
        end--;
    }
}

std::string LowerString(const std::string& inputString) { // takes an ASCII string (for simplicity) and returns a lowercase copy of it
    std::string ls; // the lowercase string variable to return
    ls.reserve(inputString.size()); // apparently, this makes it more efficient
    for (char c : inputString) { // range-based for loop from C++11 iterates over each character
        ls += std::tolower(c); // now it can directly operate on that character, appending it
    }
    return ls; // give it back!
}

void TestDump(const std::string info[], int len, int lineWords) { // test funciton to tell me what is up
    std::cout << "\nCurrent state of the array:\n";
    for (int i = 0; i < len; i++) {
        std::cout << info[i] << ", ";
        if (i % lineWords == 0)
            std::cout << std::endl;
    }
    std::cout << "\nEnd of test dump.\n\n";
    return;
}

/*
Lists out how to convers relational operators to the compare method
string1 <  string2: string1.compare(string2) < 0
string1 == string2: string1.compare(string2) == 0
string1 >  string2: string1.compart(string2) > 0
string1 != string2: string1.compare(string2) != 0
*/

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
