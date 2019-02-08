//============================================================================
// Name        : Patel5.cpp
// Author      : Harsh Patel
// Version     : 2
// Copyright   : Your copyright notice
// Description : Assignment 5
//============================================================================

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <random>
#include <ctime>
using namespace std;

class Card {
  char m_suit;       // card suit, either 'S', 'C', 'D', 'H'.
  int  m_num;        // 1 through 13.
public:
  Card(const char s = '\0', const int n = 0) : m_suit(s), m_num(n) {}
  char suit() const { return m_suit; }
  int num() const { return m_num; }
  bool operator<(const Card& lhd) const { return m_num < lhd.m_num; }
  friend ostream& operator<<(ostream& o, const Card& c) {
    o << c.m_suit;
    switch(c.m_num) {
    case 0:  o << '*'; break; // used to show wild number.
    case 1:  o << 'A'; break; // Ace.
    case 11: o << 'J'; break; // Jack.
    case 12: o << 'Q'; break; // Queen.
    case 13: o << 'K'; break; // King
    default: o << c.m_num;
    }
    return o;
  }
};

class Player {
  vector<Card> hand; // holding cards.
public:
  Player() {}        // default Ctor.
  void push_back(const Card& c) { hand.push_back(c); }
  int size() const { return hand.size(); }
  Card remove(const int p) { // simply remove the specified position.
    Card c = hand[p];
    hand[p] = hand.back();   // swap with the tail of vector.
    hand.pop_back();         // then remove the tail element.
    return c;                // the one removed will be turned back.
  }
  Card x() const { //used to return card that has most occurring suite in players hand
	  vector <string> v(4); v[0] = "S"; v[1] = "D"; v[2] = "H"; v[3] = "C";
	  for (int i = 0; i < hand.size(); ++i){
		  switch(hand[i].suit()){
		  case 'S': v[0]+=v[0]; break; //add char
		  case 'D': v[1]+=v[1]; break; //for each time
		  case 'H': v[2]+=v[2]; break; //a suit is detected
		  case 'C': v[3]+=v[3]; break;
		  }
	  }
	  sort(v.begin(), v.end(),
	      [](string &a, string &b) { return b.length() < a.length(); }); // sort by string size

	  return Card(v[0][0],0); //returns Card('char mode suit', 0 )
  }
  Card hands(const int n) const { return hand[n];} // return a specific card in hand
  friend ostream& operator<<(ostream& o, const Player& p ){
    for (int i = 0, len = p.hand.size(); i < len; ++i)
      o << setw(3) << '(' << (char)('a' + i) << ") " << p.hand[i];
    return o;
  }
};
int main() {
	const int NumPlayers = 4; const int NumInCards = 6;
	srand(time(0));
	vector<Card> deck; // initialize a standard 52 card deck.
	for (int i = 1; i <= 13; ++i){
		deck.push_back(Card('S', i));
		deck.push_back(Card('C', i));
		deck.push_back(Card('D', i));
		deck.push_back(Card('H', i));
	}
	auto gen = default_random_engine(rand());
	shuffle (deck.begin(), deck.end(), gen); // shuffle them.

	vector<Player> players(NumPlayers); // players altogether in the game.
	for (int i = 0; i < NumPlayers; ++i)
		for (int j = 0; j < NumInCards; ++j) { // each has #cards in the beginning.
			players[i].push_back(deck.back()); deck.pop_back();
		}
	Card pile = deck.back(); deck.pop_back(); // the initial card in the pile.
	char which;
	while (true) {
		if (deck.size() <= 0) goto OUTOFCARDS; // easiest verstion to move out nested loop.
		cout << "Pile has " << pile << " <--- your turn" << endl;

		while (true) {
			char draw = 'a' + players[0].size();
			cout << endl << players[0] << "  (" << draw << ") draw" << endl;
			cout << "\nWhich one to play? "; cin >> which; which = tolower(which);
			if (which == draw) {
				if (deck.size() <= 0) goto OUTOFCARDS;
				players[0].push_back(deck.back()); deck.pop_back();
			}
			if (which < draw && which >= 'a') break;
			if (which == '?') {
				for (int i = 1; i < NumPlayers; ++i) cout << "Player " << i << players[i] << endl;
				continue;
			}
			if (which > draw || which < 'a') {cout << "No such option. Try again..." << endl; continue;}
		}
		Card chosen = players[0].hands(which - 'a'); char suit;
		if (chosen.suit() != pile.suit() && chosen.num() != pile.num() && chosen.num() != 8){
			cout << "Invalid card choice. Try again...\n"; continue; }
		if (chosen.num() == 8){
			RETRY:
				cout << "Which suit do you want?" << endl;
				cin >> suit; suit = toupper (suit);        // suit not case sensitive
				if (suit != 'C' && suit != 'H' && suit != 'S' && suit != 'D'){
					cout << "Invalid suit. Try again..." << endl; goto RETRY; }
		}
		pile = players[0].remove(which - 'a');
		if (players[0].size() == 0) { cout << "\nYou won!\n"; goto END; }
		if (chosen.num() == 8){ pile = Card(suit,0); } // update pile when card is 8
		for (int i = 1; i < NumPlayers; ++i){
			cout << "Pile has " << pile << endl;
			START:
				int found = 0; int handsize = players[i].size(); int found2 = 0,found3 = 0;
				bool foundsuit = false; bool found8 = false;
				for (int j = 0; j < handsize; ++j){
					Card current = players[i].hands(j);
					if (current.num() == pile.num()) {
						found = j; goto FOUNDCARD;
					}
					if (!foundsuit && current.suit() == pile.suit() && current.num()!= 8){
						foundsuit = true;
						found2 = j;    // save j in f2 incase we need to utilize suit card.
					}
					if (!found8 && current.num() == 8){
						found8 = true;
						found3 = j;  // save j in case we need to use 8 card - if no other option
					}
				}
				if (foundsuit) { found = found2; goto FOUNDCARD; }
				if (found8) { found = found3; goto FOUNDCARD; }
				if (deck.size() <= 0) goto OUTOFCARDS; //drawing begins here
				cout << "\t Player " << i << " drawing..." << endl;
				players[i].push_back(deck.back()); deck.pop_back();
				goto START; //repeat until good card appears
			FOUNDCARD:
				cout << "\t Player " << i << " chose " << players[i].hands(found) << endl;
				pile = players[i].hands(found);
				if (players[i].hands(found).num() == 8){
					cout << "\t Player " << i << " declared suite " << players[i].x().suit() << endl;
					pile = players[i].x(); // using most common suit in players hand
				}
				players[i].remove(found);
				if (players[i].size() <= 0) { cout << "\nPlayer " << i << " won!" << endl; goto END;}
				continue;
		}
	}
	OUTOFCARDS:
	  cout << "\nNo more cards, ending game...\n[ DRAW ] No player has reached 0 cards...\n";
	END:
	  cout << "\n[ Final card distributions ]" << endl;
	  for (int i = 0; i < NumPlayers; ++i) cout << "Player " << i << players[i] << endl;
  return 0;
}
