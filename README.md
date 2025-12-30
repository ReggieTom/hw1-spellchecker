This program comes in 3 parts. You will have two opportunities to check functionality for homework credit.
For the first check, you will only submit Part 1, and for the second check, 
you will submit Part 1 and Part 2. 
The program grade will be based on your submission of all three parts in the end.

Part 1:
You are developing a C++ program that does spell checking on a text file.
The program will take 3 command line parameters which are names for: 
	•	a file with a list of correctly spelled words
	•	a text file to check
	•	an output file for the structure of the dictionary (not relevant to the task,
but important for grading your data structure accuracy).
The program will first build a dictionary from the word list. 
Then it will check the file, 
printing information about each misspelled word and suggestions for possible corrections to standard output. 
Finally, it will print the dictionary structure to the specified output file.

Format of spelling output
For each misspelled word print the word and the line it was found on followed by information about the suggestions found, 
followed by a blank line. Examples:

saed on line 5
Suggested corrections:
    saved     sad

remirmand on line 6
No suggestions found

Note that the first line of the file is line 1, not line 0. 
We want this output to be human-friendly, and most humans start counting at 1,
	rather than 0. Use 4 spaces for the indentation of the suggested words.

How to generate suggestions
As suggested corrections, list any words in the dictionary that are obtainable by applying any of the following rules (one at a time):
	•	Add one letter to the word (at any position)
	•	Remove one letter from the word
	•	Exchange adjacent characters

This won’t find all possible corrections, but will find some. 
You may also find some duplicated suggestions.
Just report all suggestions.

You will be starting with a partial program, which includes a dictionary, implemented as a basic binary search tree, 
and the framework of the actual spell checking program.

You will be filling in the part of the program that reads the word list and builds the dictionary as well as the part that does the actual spell checking.

You will find the starting source code files along with a number of files for testing in 
/home/ad.ilstu.edu/mbhatt1/Public/it279/Program1/. 
The source code files that matter for part 1 are:
	•	Dictionary.h and Dictionary.cpp –
A class that implements the Dictionary ADT storing pointers to strings in a basic binary search tree. 
It does not include deletion, but does include the ability to print the dictionary contents out in order (a useful check on correctness). 
It also has a public function for printing the tree structure in a somewhat understandable format to help us check the correctness of our code.

	•	spellChecker.cpp – the program file with main. 
This is where all of your code for part 1 will be written. 

Make sure you review the provided source code files carefully to make sure that you understand what has been provided and what you are expected do to complete the program.

Simplifying Assumptions:
	•	We don’t care about case; convert everything to lowercase when reading from all files.
	•	Words are strings of letters (a-z).  
Treat everything that isn’t a letter as breaking up words.
Note that this means you may have multiple ”words" on a single line in your word list – both should be entered in the dictionary.
Note that this means that the dictionary files may then have duplicates, which must not be entered into the Dictionary object twice.
	•	Each line ends with a newline character.

Advice: read character-by-character and build the words as you go. 
You can also read line-by-line and go through the line character-by-character, but that will make the logic slightly more complicated.

You will compile the program in the usual way, including both relevant .cpp files:

g++ -g Dictionary.cpp spellChecker.cpp

This program takes three command line parameters: the wordlist file to fill the dictionary, 
the file to check for spelling errors,
and an output file that shows the structure of the dictionary (search tree or hash table). 
Therefore, running it will look something like this:

./a.out smallDict.txt test1.txt dictstructoutfile

For testing purposes, you have been provided with three different-sized dictionary files as well as the correct dictionary structure files for each. There is also a sample input file along with correct output for each dictionary. The spelling output will go to standard output, so you will need to redirect the output to save it into a file.

The working program using the provided Dictionary class is part 1. 
For the functionality check, you will zip and submit only the completed spellChecker.cpp file.

--------------------------------------------
Part 2:
You will now modify the Dictionary class so that it is an AVL tree implementation instead of a basic binary search tree.

Save a copy of the dictionary files in a different folder or with different names (like BST_Dictionary.h and BST_Dictionary.cpp).

Then add code to Dictionary.h and Dictionary.cpp to make it an AVL tree implementation.
There is some sample code in the book that may be helpful, but make sure to improve the clarity of the names in the code if you use it.

Make sure that no changes are made to the public interface (the public method signatures) of the Dictionary class.
You also must not change the name of the class. 
Be careful to ensure that your spell checking program works correctly when compiled with either version of the Dictionary files.

To test your AVL version of the Dictionary class, you have multiple aids.
You have correct dictionary structure output files for each of the provided dictionary input files. 
You also have a test_dictionary.cpp file that can be used to do some simple testing of the AVL tree.
To run it you will compile it with the Dictionary.cpp file. 
Correct output for the AVL tree version of the Dictionary is in test-dictionary-avl.txt.

The second functionality check requires the AVL tree version of the Dictionary files and the working spellChecker.cpp file. 
Submitting this is a little bit tricky. You’ll submit the AVL version of the Dictionary files and the spellChecker.cpp file. 
But before you zip the Dictionary files, change the names of the files 
(and ONLY the names of the files) to AVL_Dictionary.h and AVL_Dictionary.cpp. 
The testing script will rename the files to Dictionary.h and Dictionary.cpp before compiling the program,
so be very careful that you haven’t changed any includes or class names inside the files. 
If you do change anything inside any code file to AVL_Dictionary, your code will not compile when test, 
and that will count as a compile-time error (automatic F), so be very careful.

Once you have renamed the files, zip AVL_Dictionary.h, AVL_Dictionary.cpp, and spellChecker.cpp into a single zip file, 
attach to the second functionality check homework in Canvas, and submit.

Because this is a bit tricky, we have provided a validation script for you to use to check your zip file. 
To use the script, run bash validation_script.sh zipfilename.zip
from a terminal in the directory where your zip is located. 
If there are issues with compilation, it will report them to you.
Make sure to fix them before submission.
------------------------------------------------
Part 3:
For part three, we’re going to revise the Dictionary class to use a hash table implementation instead of search tree implementation. 
You will need to replace pretty much all of the implementation code and data of the Dictionary class.
So start by saving a copy of the AVL version (since you still need to submit that for the program). 

Modify Dictionary.h and Dictionary.cpp to still have the same public interface (same public method signatures), 
but to be a hash table instead. Your program must work with any version of the Dictionary class with no changes.

Hash table details:
You will use double hashing. 
The prime numbers that you will use for your hash table sizes are:
{101, 211, 431, 863, 1733, 3469, 6947, 13901, 27803, 55609, 111227, 222461, 444929, 889871}. 
The prime numbers for your double hashing will be:
{97, 199, 421, 859, 1723, 3467, 6917, 13883, 27799, 55603, 111217, 222437, 444901, 889829}.

Use the hash function from figure 5.4 in section 5.2 of your textbook. 
This is the code for a good approach to turning a string into a hash value. 
Do not change the parameters or types in that function.
Mention secondary hash function formula

Rehash when you are about to add an entry that will push the table above 50% full.

You are required to store your hash table as a dynamic array that you manage, not as a vector.

You will need to modify the dictionary structure printing to be appropriate for a hash table. 
We’ll print all of the indices and then print just the key (the word) at the index it appears on. 
See the example output and make sure to use diff when comparing to ensure that your files have exactly the correct format.

You are also required to implement printing the dictionary in order. This will involve sorting.
You should copy the data from the hash table into a vector and use the STL sort function.
I encourage you to check out documentation on cppreference.com and or cplusplus.com. 
When you sort, make sure you’re comparing the strings and not the pointers, but do not copy the strings, just the pointers.

For comparison purposes, you have hash version of each provided dictionary as well as test-dictionary-hash.txt 
which is the output for the test program for the hash table version. 
You also have files with the correct results of printing each dictionary in sorted order.
I recommend writing a little test program that reads the dictionary in and calls the function to print the content in order 
and compare to the correct output.

Submission requirements:
Just as you renamed the AVL version of the Dictionary files to AVL_Dictionary.h and AVL_Dictionary.cpp,
you will need to rename the hash table version to Hash_Dictionary.h and Hash_Dictionary.cpp.
Again, remember that our testing will copy the files to Dictionary.h and Dictionary.cpp before each version of the program is compiled, 
so you need to be very careful that you make no changes to includes or class names inside the files.

Zip the 5 files, spellChecker.cpp, AVL_Dictionary.h, AVL_Dictionary.cpp, Hash_Dictionary.h, and Hash_Dictionary.cpp, 
into a single zip file with no folders.
You are encouraged to again use the provided validation script to check them to make sure they will compile correctly as described above.
