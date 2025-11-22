#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <fstream>

using namespace std;

string build_cipher(const string& keyword){ // establishes the cipher from the user's keyword
	string result;
	unordered_set<char> used; // reads users keyword character by character
	for (char c : keyword) {
		char upper = toupper(c); // only reads upper case characters
		if (isalpha(upper) && used.find(upper) == used.end()) {
			result += upper;
			used.insert(upper); // adds characters to the cipher appended to the end of the string
		}
	}
	for (char ch = 'Z'; ch >= 'A'; --ch) {
		if (used.find(ch) == used.end()) {
			result += ch; 
			used.insert(ch); // goes through the remainder of the alphabet and appends unused letters
		} // to the end of the cipher in reverse alphabetical order
	}
	return result;
}

void create_maps(const string& cipher, unordered_map<char, char>& plain_to_cipher,
	unordered_map<char, char>& cipher_to_plain) {
	char plain = 'A';
	for (char cipher_char : cipher) {
		plain_to_cipher[plain] = cipher_char;
		cipher_to_plain[cipher_char] = plain;
		++plain;
	}
}

void encrypt_file(const string& input_file, const string& output_file, const unordered_map<char,
	char>& plain_to_cipher) {
	ifstream in(input_file);
	ofstream out(output_file);
	char ch;
	while (in.get(ch)) {
		char upper = toupper(ch);
		if (plain_to_cipher.count(upper)) {
			out.put(plain_to_cipher.at(upper));
		}
		else {
			out.put(ch);
		}
	}
	in.close();
	out.close();
}
	void decrypt_file(const string & input_file, const string & output_file, const unordered_map<char,
		char>&cipher_to_plain) {
		ifstream in(input_file);
		ofstream out(output_file);
		char ch;
		while (in.get(ch)) {
			char upper = toupper(ch);
			if (cipher_to_plain.count(upper)) {
				out.put(cipher_to_plain.at(upper));
			}
			else {
				out.put(ch);
			}
		}
		in.close();
		out.close();
	}

int main(){
	string mode, keyword, input_file, output_file;
	cout << "Enter mode (encrypt/decrypt): ";
	cin >> mode;
	cout << "Enter keyword: ";
	cin >> keyword;
	cout << "Name of input file: ";
	cin >> input_file;
	cout << "Name of output file: ";
	cin >> output_file;

	string cipher = build_cipher(keyword);
	unordered_map<char, char> plain_to_cipher, cipher_to_plain;
	create_maps(cipher, plain_to_cipher, cipher_to_plain);

	if (mode == "encrypt") {
		encrypt_file(input_file, output_file, plain_to_cipher);
		cout << "Encryption complete.\n";
	}
	else if (mode == "decrypt") {
		decrypt_file(input_file, output_file, cipher_to_plain);
		cout << "Decryption complete.\n";
	}
	else
		cout << "Invalid mode selected." << endl;

	return 0;
}
