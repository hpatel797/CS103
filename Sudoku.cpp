#include <vector>
#include <iostream>
using namespace std;

//Create and initialize Sudoku Board
struct Board {
	vector<vector<short> > board;

	Board() {
		for(int i = 0; i < 9; ++i) {
			vector<short> row;

			for(int j = 0; j < 9; ++j) {
				short spot;
				spot = 0;

				if (i == 0) spot = j+1;
				if (i > 0 && i != 3 && i != 6) spot = board[i-1][3] + j;
				if (i == 3 || i == 6) spot = board[i-1][3] + j + 4;
				if (spot > 9) spot -= 9;

				row.push_back(spot);
			}
			board.push_back(row);
		}
	};
};

//Swap Function
Board swapping(Board *s){
	int RorC = rand() % 2;  //Row or Column
	int RC1 = rand() % 9;	//Which row or column
	int RC2 = rand() % 9;

	char letter1;
	char letter2;
	while (RC1 == RC2) {	//Make sure random rows and columns are different
		RC1 = rand() % 9;
	}

	if (RorC == 0)	{		//Row [i][RC1]
		letter1 = 'P' + RC1;	//Correct letters
		letter2 = 'P' + RC2;
		bool range1; 			//Check if the range is applicable
		bool range2;

		cout << "Trying to swap rows " << letter1 << " and "<< letter2 <<"..." << endl;

		//Check if numbers are within range
		for (int i = 0; i < 3; ++i) {
			range1 = false;
			range2 = false;
			for (int j = 3 * i, len = (i + 1) * 3; j < len; ++j) {

				if (RC1 == j) range1 = true;
				if (RC2 == j) range2 = true;
				//If numbers are within range, swap
				if (range1 == true && range2 == true) {
					for (int k = 0; k < 9; ++k) {
						int temp;
						temp = s->board[k][RC1];
						s->board[k][RC1] = s->board[k][RC2];
						s->board[k][RC2] = temp;
					}
					cout << "- Rows " << letter1 << " and " << letter2 << " were swapped..." << endl;
				}
			}
		}
		//In the case, numbers are not in range
		if ((range1 == true && range2 == true) == false) {
			bool check1;
			bool check2;
			bool check3;

			check1 = false;
			check2 = false;
			check3 = false;

			char l1;
			char l2;
			//Find out which group the numbers are in
			for (int i = 0; i < 3; ++i) {
				if (RC1 == i || RC2 == i) check1 = true;
			}
			for (int i = 3; i < 6; ++i) {
				if (RC1 == i || RC2 == i) check2 = true;
			}
			for (int i = 6; i < 9; ++i) {
				if (RC1 == i || RC2 == i) check3 = true;
			}
			//Swap the 3 rows accordingly
			if (check1 == true && check2 == true) {
				for (int i = 0; i < 3; ++i) {
					l1 = 'P';
					l2 = 'P';
					for (int k = 0; k < 9; ++k) {
						int temp;
						temp = s->board[k][i];
						s->board[k][i] = s->board[k][i+3];
						s->board[k][i+3] = temp;
					}
					l1 += i;
					l2 += i+3;
					cout << "- Rows " << l1 << " and " << l2 << " were swapped..." << endl;
				}
			}
			if (check2 == true && check3 == true) {
				for (int i = 3; i < 6; ++i) {
					l1 = 'P';
					l2 = 'P';
					for (int k = 0; k < 9; ++k) {
						int temp;
						temp = s->board[k][i];
						s->board[k][i] = s->board[k][i+3];
						s->board[k][i+3] = temp;
					}
					l1 += i;
					l2 += i+3;
					cout << "- Rows " << l1 << " and " << l2 << " were swapped..." << endl;
				}
			}
			if (check1 == true && check3 == true) {
				for (int i = 6; i < 9; ++i) {
					l1 = 'P';
					l2 = 'p';
					for (int k = 0; k < 9; ++k) {
						int temp;
						temp = s->board[k][i];
						s->board[k][i] = s->board[k][i-6];
						s->board[k][i-6] = temp;
					}
					l1 += i-6;
					l2 += i;
					cout << "- Rows " << l1 << " and " << l2 << " were swapped..." << endl;
				}
			}
		}
	}
    if (RorC == 1)	{		//Column [RC1][i]
		letter1 = 'A' + RC1;
		letter2 = 'A' + RC2;
		bool range1; 			//Check if the range is applicable
		bool range2;

		cout << "Trying to swap columns " << letter1 << " and "<< letter2 <<"..." << endl;

		//Check if numbers are within range
		for (int i = 0; i < 3; ++i) {
			range1 = false;
			range2 = false;
			for (int j = 3 * i, len = (i + 1) * 3; j < len; ++j) {

				if (RC1 == j) range1 = true;
				if (RC2 == j) range2 = true;
				//If numbers are within range, swap the columns
				if (range1 == true && range2 == true) {
					for (int k = 0; k < 9; ++k) {
						int temp;
						temp = s->board[RC1][k];
						s->board[RC1][k] = s->board[RC2][k];
						s->board[RC2][k] = temp;
						cout << "- Rows " << letter1 << " and " << letter2 << " were swapped..." << endl;
						break;
					}
				}
			}
		}
		//In the case, numbers are not in range
		if ((range1 == true && range2 == true) == false) {
			bool check1;
			bool check2;
			bool check3;

			check1 = false;
			check2 = false;
			check3 = false;

			char l1;
			char l2;
			//Find out which group the numbers are in
			for (int i = 0; i < 3; ++i) {
				if (RC1 == i || RC2 == i) check1 = true;
			}
			for (int i = 3; i < 6; ++i) {
				if (RC1 == i || RC2 == i) check2 = true;
			}
			for (int i = 6; i < 9; ++i) {
				if (RC1 == i || RC2 == i) check3 = true;
			}
			if (check1 == true && check2 == true) {
				for (int i = 0; i < 3; ++i) {
					l1 = 'A';
					l2 = 'A';
					for (int k = 0; k < 9; ++k) {
						int temp;
						temp = s->board[i][k];
						s->board[i][k] = s->board[i+3][k];
						s->board[i+3][k] = temp;
					}
					l1 += i;
					l2 += i+3;
					cout << "- Rows " << l1 << " and " << l2 << " were swapped..." << endl;
				}
			}
			if (check2 == true && check3 == true) {
				for (int i = 3; i < 6; ++i) {
					l1 = 'A';
					l2 = 'A';
					for (int k = 0; k < 9; ++k) {
						int temp;
						temp = s->board[i][k];
						s->board[i][k] = s->board[i+3][k];
						s->board[i+3][k] = temp;
					}
					l1 += i;
					l2 += i+3;
					cout << "- Rows " << l1 << " and " << l2 << " were swapped..." << endl;
				}
			}
			if (check1 == true && check3 == true) {
				for (int i = 6; i < 9; ++i) {
					l1 = 'A';
					l2 = 'A';
					for (int k = 0; k < 9; ++k) {
						int temp;
						temp = s->board[i][k];
						s->board[i][k] = s->board[i-6][k];
						s->board[i-6][k] = temp;
					}
					l1 += i-6;
					l2 += i;
					cout << "- Rows " << l1 << " and " << l2 << " were swapped..." << endl;
				}
			}
		}
	}
	return *s;
}

//Erase Function
Board erase(Board *e) {
	int row = rand() % 9;	//Randomly pick a spot
	int col = rand() % 9;
	char rowlet;			//Location of spot
	char collet;
	rowlet = 'P' + row;
	collet = 'A' + col;
	e->board[col][row] = '-';    //Stored as '45'
	cout << "Erasing row " << rowlet << " column " << collet << endl;
	return *e;
}

//Verify Function
void verify(Board *v) {
	vector<short> set;		//Vector filled from 1-9 to check for inconsistency
	bool ok;
	ok = true;


	//Check rows for inconsistency
	for (int row = 0; row < 9; ++row ) {
		char rowlet;
		rowlet = 'P' + row;
		for (int i = 1; i < 10; ++i) set.push_back(i);

		for (int col = 0; col < 9; ++col) {
			for (int i = 0, len = set.size(); i < len; ++i) {
				if (set[i] == v->board[col][row]) {
					set.erase(set.begin() + i);
					break;
				}
			}
		}
		if (set.size() != 0) {
			cout << "- Found inconsistency in row " << rowlet << "..." << endl;
			ok = false;
		}
		set.clear();
	}


	//Check cols for inconsistency
	for (int col = 0; col < 9; ++col ) {
		char collet;
		collet = 'A' + col;
		for (int i = 1; i < 10; ++i) set.push_back(i);


		for (int row = 0; row < 9; ++row) {
			for (int i = 0, len = set.size(); i < len; ++i) {
				if (set[i] == v->board[col][row]) {
					set.erase(set.begin() + i);
					break;
				}
			}
		}
		if (set.size() != 0) {
			cout << "- Found inconsistency in column " << collet << "..." << endl;
			ok = false;
		}
		set.clear();
	}
	//Check componenets for inconsistency
	//Broke board down into 9 squares
	for (int i = 0; i < 9; ++i) {
		int multi1;
		int multi2;

		char collet;
		char rowlet;

		for (int i = 1; i < 10; ++i) set.push_back(i);

		if (i == 0 || i == 3 || i == 6) {
			multi1 = 0;
			rowlet = 'P';
		}
		if (i == 1 || i == 4 || i == 7) {
			multi1 = 3;
			rowlet = 'S';
		}
		if (i == 2 || i == 5 || i == 8) {
			multi1 = 6;	rowlet = 'V';
		}

		if (i == 0) {
			multi2 = 0;
			collet = 'A';
		}
		if (i == 3) {
			multi2 = 3;
			collet = 'D';
		}
		if (i == 6) {
			multi2 = 6;
			collet = 'G';
		}

		for (int row = multi1; row < multi1 + 3; ++row) {
			for (int col = multi2; col < multi2 + 3; ++col) {
				for (int k = 0, len = set.size(); k < len; ++k) {
					if (set[k] == v->board[col][row]) {
						set.erase(set.begin() + k);
						break;
					}
				}
			}
		}
		if (set.size() != 0) {
			cout << "- Found inconsistency in component starting at row " << rowlet  << " and column "<< collet <<"..." << endl;
			ok = false;
		}
		set.clear();
	}

	//Nothing is wrong
	if (ok == true) {
		cout << "- All columns, rows, and components are OK..." << endl;
	}

}

//Printing out the Board
ostream& operator<<(ostream& o, const Board& b) {
  o << "   ";
  for (int i = 0; i < 9; ++i) {
  	char top;
  	top = 0;
  	top = i + 65;
  	o << top << ' ';
  }
  o << endl;
  for (int row = 0; row < 9; ++row) {
  	char left;
  	left = 0;
  	left = row + 80;
  	o << left << "  ";

    for (int col = 0; col < 9; ++col) {
      if (b.board[col][row] == 45) o << '-' << ' ';
      if (b.board[col][row] != 45) o << b.board[col][row] << ' ';
    }
    o << endl;
  }
  return o;
}


int main() {
	Board *n;
	Board b;
	n = &b;
	string input;
	cout << "Welcome to Sudoku Initializer!" << endl;

	while (input != "quit") {
		cout << "> ";
		cin >> input;
		if (input == "erase") *n = erase(n);
		else if (input == "show") cout << *n << endl;
		else if (input == "swap") *n = swapping(n);
		else if (input == "verify") verify(n);
		else if (input == "quit") break;
		else cout << "Error: Please enter 'show', 'swap', 'verify', 'erase', or 'quit'. Thank you!" << endl;
	}	return 0;
}
