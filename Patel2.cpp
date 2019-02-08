//============================================================================
// Name        : Patel2.cpp
// Author      : Harsh Patel
// Version     :
// Copyright   : Your copyright notice
// Description : Assignment 2
//============================================================================

#include <iostream>
#include <cstdlib>
using namespace std;

string rolling(){ return rand()%2==1? "h" : "c";}

int main() {
	srand(time(0));
	int allow0 = 100 , allow1 = 100, allow2 = 100;

	while (allow0 > 0){
		cout << "You have $" << allow0 << "\nPlayer1 has $" << allow1 << "\nPlayer2 has $" << allow2 << endl;
		cout << "\nEnter 'c' (even) or 'h' (odd) and an amount you bet: "; string odds; int bet;
		cin >> odds >> bet;
		if ( odds != "c" && odds != "h"){
			cout << "\n****Error, invalid bet call. Please try again****\n" << endl; continue;}
		if (bet > allow0 || bet < 0){
			cout << "\n****Error, invalid bet amount. Please try again****\n" << endl; continue;}

		int compbet1 = 1 ,compbet2 = 1;
			if(allow1 > 1){
					compbet1 = allow1<allow0? (rand()%(allow1/2)) + 1 : rand() % allow1 + 1;} //both regular and conservative
			if (allow2 > 1){
				compbet2 = allow2<allow0? (rand()%(allow2/2)) + 1 : rand() % allow2 + 1;} //approach in one statement.


		string result1,result2,result3;

		result1 = odds==rolling()? "won" : "lost";
		result2 = rolling()==rolling()? "won" : "lost";
		result3 = rolling()==rolling()? "won" : "lost";

		cout << "You bet $" << bet << " -> " << result1 << "...\n";
		allow0 += result1 == "won"? bet : -bet;

		if (allow1 > 0 ) { //only print when player isnt broke
			cout << "Player1 bet $" << compbet1 << " -> " << result2 << "...\n";
			allow1 += result2 == "won"? compbet1 : -compbet1;}
		if (allow2 == 0) cout << "\n"; //skips extra line to maintain design when player 2 is broke.
		if (allow2 > 0 ){
			cout << "Player2 bet $" << compbet2 << " -> " << result3 << "...\n\n";
			allow2 += result3 == "won"? compbet2 : -compbet2; }

		if (allow1 == 0 && allow2 == 0) { cout << "Both players are now broke.\n"; break; }
	}

	cout << (allow0 > 0? "Good job.\nYou won.\nBye..." : "Game over. \nYou are broke. \nBye...") << endl;
	return 0;
}
