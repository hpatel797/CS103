//============================================================================
// Name        : Patel3.cpp
// Author      : Harsh Patel
// Version     :
// Copyright   : Your copyright notice
// Description : Assignment 3
//============================================================================

#include <iostream>
#include <chrono>
using namespace std;

string word (){
	string rg;
	for (int i=0; i < 7; ++i){
			rg[i] = rand()%2 == 1? toupper('a' + rand()%26) : 'a' + rand()%26;
			rg += rg[i];
	}
	return rg;    // returns random generation
}

int main() {
	srand(time(0)); int allow = 1000;
	while (allow < 5000 && allow > 0){
		string rand = word() , ans = rand, input;
		for (int i = 0, len = ans.size(); i < len - 1; ++i){ //organize random generation
			int min_pos = i;
			for (int j = i+1; j < len; ++j){
				if (ans[j] < ans[min_pos]) min_pos = j;
			}
			if (min_pos != i){
				char temp = ans[i];
				ans[i] = ans[min_pos];
				ans[min_pos] = temp;
			}
		}
		cout << "Your current points are " << allow << ", type in order -> " << rand << ": ";
		chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		cin >> input;
		chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

		int TD = chrono::duration_cast<chrono::milliseconds>(end - begin).count(),
			offset = 0,
			penalty,
			diff = TD - 12000;

		if (input.length() < ans.length()) input += string(ans.length()-input.length(),' '); //padding when user enters less than 7
		if (input.length() > ans.length()) ans += string(input.length()-ans.length(),' ');   //  "       "   "     "    more than 7

		for (int i=0, len = input.size(); i < len ; ++i){
			if (input[i] != ans[i]) offset += abs(ans[i] - input[i]);
		}
		ans.resize(7); cout << TD; //TD or time difference, is printed here to allow conditional operator in line 62 and 61.
		if ( input != ans ){
			penalty = diff > 0? diff + 2*offset : offset;
			cout << (diff > 0? " milliseconds, you *failed* it within the interval of 12000... " : " milliseconds, You made it within the interval of 12000...");
			cout << "\nAnswer must be '" << ans << "'\nString offset is " << offset << ", your total penalty is " << penalty << " ...\n\n";
			allow -= penalty;
			continue;
		}
		cout << (diff > 0? " milliseconds, you *failed* it within the interval of 12000...\n\n" : " milliseconds, you made it within the interval of 12000...\n\n");
		allow += diff > 0? -diff : 500;
	}
	cout << (allow > 0? "You won. \nBye..." : "You lost. \nBye..." );
	return 0;
}
