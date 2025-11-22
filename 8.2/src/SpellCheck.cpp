#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cctype>

using namespace std;

void remove_punctuation(string& word) {
	word.erase(remove_if(word.begin(), word.end(),
		[](unsigned char c) { return ispunct(c); }), word.end());
}
// This function is meant to be run as the code is reading the user text file to remove any punctuation
// so the user text does not come back as a typo due to punctuation.
int main()
{
	vector<string>words;
	// this defines a vector of strings
	ifstream dictfile("words");
	if (!dictfile) {
		cerr << "Error opening file.\n";
			return 1;
	}
	string word;
	while (dictfile >> word) {
		words.push_back(word);
	}
	// this is what adds the words to the end of the vector
	dictfile.close();
	ifstream userfile("Myfile.txt");
	if (!userfile) {
		cerr << "Error opening user file.\n";
		return 1;
	}
	string user_word;
	while (userfile >> user_word) {
		remove_punctuation(user_word);
		// this should remove punctuation so words aren't marked incorrect due to punctuation
		if (find(words.begin(), words.end(), user_word) == words.end()) {
			cout << user_word << endl;
		}
	}
	
}
