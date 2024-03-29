# DivConquerSorts
This is my work for an assignment in my Analysis of Algorithms class.
The class is at The University of Alabama in Huntsville and taught by professor Beth Allen in the spring of 2024.
# Objectives
The purpose of this program is to sort up to 100,000 strings using C++ arrays.
The user supplies an input and output file, in addition to how much to print per line.
The strings are read in from the input file, which is assumed to have whitespace delimiters only an *no punctuation*.
The first copy is sorted with QuickSort and written into the output file.
The second copy is sorted with MergeSort and written into the output file in reverse ordder.
Both sorts are implemented from scratch in this program to demonstrate their efficiency.
Since relational operators operate on the addresses of the array's base, I use [std::string::compare](https://cplusplus.com/reference/string/string/compare/) instead.
I considered using [_stricmp](https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/stricmp-wcsicmp-mbsicmp-stricmp-l-wcsicmp-l-mbsicmp-l?view=msvc-170) 
since Windows lacks [strcasecmp](https://pubs.opengroup.org/onlinepubs/9699919799/), but this would impair portability significantly.
# Operation
Just compile and run the DivConquerSorts.cpp file, as it has no dependencies or libraries.
Once it starts running, you must supply an input and output file path, as well as formatting direcitons.
No arguments are necessary, simply compile it as follows (on an x86-64 machine):
## POSIX
g++ DivConquerSorts.cpp -o DivConquerSorts
## Windows
You can also just use Visual Studio, which I wrote this in.
cl /EHsc DivConquerSorts.cpp