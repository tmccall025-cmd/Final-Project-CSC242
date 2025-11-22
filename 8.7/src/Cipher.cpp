#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <fstream>

using namespace std;
/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
** 
** Class: 	CSC 242
** Assignment: 	Lesson # 5 Signature Assignment
** File: 	Cipher.cpp
** Description: This code takes a user entered keyword and makes a cipher from that word;
** taking the letters of that word as they first appear and appending the alphabet in reverse
** order to the rest of it, and creating a map with the alphabet in order to correlate the cipher.
** It then encrypts or decrypts a file based on what is requested and writes the encryption
** or decryption in a different file.
** Author: 	Terrance McCall
** Date: 	21 NOV 2025
** -------------------------------------------------------------------------*/
string build_cipher(const string& keyword){
// establishes the cipher from the user's keyword
	string result;
	unordered_set<char> used;
// reads users keyword character by character
	for (char c : keyword) {
		char upper = toupper(c);
// makes all characters upper case
		if (isalpha(upper) && used.find(upper) == used.end()) {
			result += upper;
			used.insert(upper);
// adds characters to the cipher appended to the end of the string
		}
	}
	for (char ch = 'Z'; ch >= 'A'; --ch) {
		if (used.find(ch) == used.end()) {
			result += ch; 
			used.insert(ch);
// Goes through alphabet in reverse order, if character is not present in "result" string, it's appended
// to the end of the string
		} 
	}
	return result;
}

void create_maps(const string& cipher, unordered_map<char, char>& plain_to_cipher,
	unordered_map<char, char>& cipher_to_plain) {
// Using a map is the best way for me to correlate the cipher; so the machine knows what information
// to provide.
	char plain = 'A';
// Set's the starting point for our cypher encryption to be 'A' of the alphabet
	for (char cipher_char : cipher) {
		plain_to_cipher[plain] = cipher_char;
		cipher_to_plain[cipher_char] = plain;
		++plain;
// Starts two maps with 'A' on the plain side and the first letter of the cipher on the opposite side, and
// fills them in all the way down to 'Z' on the plain side. Two maps so we can encrypt and decrypt.
	}
}

void encrypt_file(const string& input_file, const string& output_file, const unordered_map<char,
	char>& plain_to_cipher) {
	ifstream in(input_file);
	ofstream out(output_file);
// Program requires input and output file
	char ch;
	while (in.get(ch)) {
		char upper = toupper(ch);
// Reads input file character by character, translating all lowercase characters to upper case characters
		if (plain_to_cipher.count(upper)) {
			out.put(plain_to_cipher.at(upper));
		}
// Program will run plain_to_cipher map for any alphabetic characters, and will store them in the output
// file. This executes the encryption part of the cipher.
		else {
			out.put(ch);
		}
// Program will print any non-alphabet characters and will not attempt to cipher them.
	}
	in.close();
	out.close();
}
// Closes out files to ensure no improper writing/coding.
	void decrypt_file(const string & input_file, const string & output_file, const unordered_map<char,
		char>&cipher_to_plain) {
		ifstream in(input_file);
		ofstream out(output_file);
// Program requires input and output files
		char ch;
		while (in.get(ch)) {
			char upper = toupper(ch);
// Reads input file one line at a time, translating all lowercase letters to uppercase.
			if (cipher_to_plain.count(upper)) {
				out.put(cipher_to_plain.at(upper));
			}
// If characters are alphabetic, this runs them through the decyption cipher and writes on output file.
			else {
				out.put(ch);
			}
// Ignores all non-alphabet characters.
		}
		in.close();
		out.close();
	}

int main(){
	string mode, keyword, input_file, output_file;
// Defines all strings we'll be using for this project.
	cout << "Enter mode (encrypt/decrypt): ";
	cin >> mode;
	cout << "Enter keyword: ";
	cin >> keyword;
	cout << "Name of input file: ";
	cin >> input_file;
	cout << "Name of output file: ";
	cin >> output_file;
// User is allowed to define their own input and output files. Saves as necessary variables

	string cipher = build_cipher(keyword);
// Calls the "build_cipher" function, and runs it with the keyword as the parameter. initializes string
// named "cipher" and saves it as the result of the build_cipher function.
	unordered_map<char, char> plain_to_cipher, cipher_to_plain;
// initializes maps called "plain_to_cipher" and "cipher_to_plain" for our function.
	create_maps(cipher, plain_to_cipher, cipher_to_plain);
// Calls the "create_maps" function, executes it with our recently initialized maps
	if (mode == "encrypt") {
		encrypt_file(input_file, output_file, plain_to_cipher);
		cout << "Encryption complete.\n";
	}
// Created check to ensure I knew whether encryption failed or not. Runs encrypt_file function.
// Will read input file, run through plain_to_cipher, and write encrypted results on output file.
	else if (mode == "decrypt") {
		decrypt_file(input_file, output_file, cipher_to_plain);
		cout << "Decryption complete.\n";
	}
// Created check to ensure I knew whether decryption failed or not. Runs decrypt_file function.
// Will read input file, run through cipher_to_plain, and write decrypted results on output file.
	else
		cout << "Invalid mode selected." << endl;
// Will return error if proper mode was not selected.
	return 0;
}


