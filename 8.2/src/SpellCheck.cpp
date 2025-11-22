#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cctype>

using namespace std;
/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
** 
** Class: 	CSC 242
** Assignment: 	Lesson #4: Signature Assignment
** File: 	SpellCheck.cpp
** Description: This code will receive a user file, check all words read against Unix list,
** and print any words that are not on the list.
** To do so, it will remove any punctuation to prevent errors. It will not write over file.
** Author: 	Terrance McCall
** Date: 	19 NOV 2025
** -------------------------------------------------------------------------*/
void remove_punctuation(string& word) {
	word.erase(remove_if(word.begin(), word.end(),
		[](unsigned char c) { return ispunct(c); }), word.end());
}
// This function will remove the punctuation from before and after the word, preventing
// words from being printed due to regular punctuation.
int main()
{
	vector<string>words;
	ifstream dictfile("words");
// Opens up the Unix file that I've named "words", containing Unix list of words. Creates
// vector of strings that will be used for storing the Unix words for spell check.
	if (!dictfile) {
		cerr << "Error opening file.\n";
			return 1;
	}
// Checking to ensure that Unix file was opened, so if it was not programmer knows that dictionary	
// file is not included
	string word;
	while (dictfile >> word) {
		words.push_back(word);
	}
// ".push_back() command is what appends the new string to the vector of words. This creates
// the vector needed for spell check.
	dictfile.close();
// Closes Unix file, as is good practice to close files immediately after use.
	ifstream userfile("Myfile.txt");
	if (!userfile) {
		cerr << "Error opening user file.\n";
		return 1;
	}
// Opens file to be checked for spelling, returns an error if file cannot be opened.
// Assumes user file is uploaded and named in accordance with program.
	string user_word;
	cout << "Misspelled words: ";
	while (userfile >> user_word) {
		remove_punctuation(user_word);
// this should remove punctuation so words aren't marked incorrect due to punctuation
		if (find(words.begin(), words.end(), user_word) == words.end()) {
			cout << user_word << endl;
		}
// This is the portion of the function that reads the words in the user file, checks to see if they're
// present in the Unix dict list, and if not then prints out that word.
	}
	
}

