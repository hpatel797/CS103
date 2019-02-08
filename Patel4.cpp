//============================================================================
// Name        : Patel4.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

void headers(int n) {
	string h; char b = '-';
	for (int i = 0; i < n; ++i) h += b;
	cout << "|" << h << "|" << endl;
}

void justify (vector<string> s, int m){
	int width; vector<string> lines;
	while (true) {
		vector<string> v = s; // when loop restarts, v will be reset to s after all the changes made below to v.
		cout << "\nEnter the width of text, or enter 0 to exit: "; cin >> width;

		if (width == 0) break;
		if (width < m ) { cout << "Shorter than the longest word (" << m << ")...\n"; continue; }

		int space_left,
			widthnow = 0, widthnext = 0,
			found_words = 0,
			totchars = 0,       // total characters
			begin = 0, end = 0,
			space_dis = 0;

		headers(width); // top layout

		for (int i = 0, len = v.size(); i < len; ++i){ // scans every word.
			widthnow += i==begin? v[i].size() : v[i].size() + 1;
			widthnext = widthnow + (v[i+1].size()) + 1;

			if (widthnext > width){ // next word wont fit... enter here.
				cout <<"|";
				end = i; found_words = (end - begin) + 1;
				totchars = widthnow - found_words + 1;    //equation determines the total characters

				if (found_words == 1){ // when only one word is found, simply print that word and add missing spaces if necessary.
					v[begin] += string(width-totchars, ' ');
					cout << v[begin] << "|" << endl;
					widthnow = 0; widthnext = 0; totchars = 0; begin = i+1; //resetting variables and adusting begin.
					continue;
				}
				space_left = width - totchars;
				int temp = begin;	// create an int temp to hold the value of begin.

				while (space_left > 0){             // even adjustment logic:
					if (begin == end) begin = temp; // space distributed for each word. when reach last
					v[begin] += string(" ");        // word, space wont be added, and the loop will
					++begin;						// restart from the value that temp holds (begin)
					--space_left;					// continues until space_left = 0.
				}
				begin = temp;						// re-adjust the value of begin.
				for (int j = begin; j < end + 1  ; ++j) cout << v[j];
				cout << "|" << endl;
				widthnow = 0; widthnext = 0; totchars = 0; begin = i+1; //reset variables and increment begin so next time around, the word printed will be the next word.
				continue;
			} // ends if

			if (i == len - 1){ // last line --> if the if statement didnt fire before this, this has to be the last few words.
				for (int i = begin; i < len; ++i) totchars += v[i].length();
				space_left = width - totchars;
				space_dis = space_left - (len - begin); // space to be distributed.
				if (i == begin) v[i]+=string(space_dis + 1,' '); // if i==begin, this automatically implies loop is on the last word. therefore, just print and increase the spaces.
				cout << "|" << v[begin];
				for (int i = begin + 1; i < len; ++i){
					if (i == len - 1) v[i] += string(space_dis + 1,' '); //loop will never enter when its last word since begin + 1 = len and i < len for condition to be met.
					cout << " " << v[i]; // only one space needed since justification not needed for last line.
				}
				cout << "|" << endl;
			} // ends if
		} // ends main for loop that scans every word.
		headers(width);   	// bottom layout
	}// while loop
	cout << "Bye..." << endl;
}
int main() {
	string text; vector<string> words; int max_length;
	cout << "Enter Text, an empty return will quit the input: ";
	while (true){
		getline(cin, text);
		if (text == "") break;
		string word; bool found = false;
		for (int i = 0, len = text.size(); i < len; ++i){
			if (!isspace(text[i])){
				word += text[i];
				found = true;
				if (word.size() > max_length) max_length = word.size(); continue;
				continue;
			}
			if (!found) continue;
			words.push_back(word);
			word = "";
			found = false;
		}
		if (found) words.push_back(word);
	}
	justify (words, max_length); // take the vector words and max length up to justify.
	return 0;
}
