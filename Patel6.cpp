// Harsh Patel
// Assignment 6
#include <cstdlib>
#include <cassert>
#include <random>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>
#include <algorithm>
#include <regex>
#include <sstream>
using namespace std;

enum class Kind { COMP, HUMN, GONE, LIVE }; // global enumerator.

class Position { // class to hold board position.
  int m_row;
  int m_col;
public:
  Position(const int r = 0, const int c = 0) : m_row(r), m_col(c) {}
  int row() const { return m_row; }
  int col() const { return m_col; }
};

class Ice {   // class to hold each ice float on game board.
  Kind m_knd; // who is occuplied now, human (HUMN) computer (CMP)?
  int  m_num; // number of fish
public:
  Ice() : m_knd(Kind::LIVE), m_num(rand() % 3 + 1) {}
  void set_comp() { m_knd = Kind::COMP; }
  void set_humn() { m_knd = Kind::HUMN; }
  void set_gone() { m_knd = Kind::GONE; }
  int  get_fish() const { return m_num; }
  bool is_good()  const { // can reach this float?
    return m_knd != Kind::COMP && m_knd != Kind::HUMN && m_knd != Kind::GONE;
  }
  friend ostream& operator<<(ostream&, const Ice&);
};

ostream& operator<<(ostream& o, const Ice& i) {
  switch (i.m_knd) {
  case Kind::COMP: o << " (" << i.m_num << ')'; break; // computer.
  case Kind::HUMN: o << " =" << i.m_num << '='; break; // human.
  case Kind::GONE: o << "  . " ; break;
  case Kind::LIVE: o << "  " << i.m_num << ' '; break;
  default: cerr << "Unknown switch at operator<<(ostream&, const Ice&)...";
    abort();
  }
  return o;
}
double dist (const int p1, const int p2, const int q1, const int q2){
	  int diff = q1 - p1;
	  int diff2 = q2 - p2;
	  double dis = sqrt(diff*diff + diff2*diff2);
	  return dis;
 }
class Board { // class to hold board situation.
  int m_size;
  vector<vector<Ice> > m_board;       // 2D ice floe.
  int m_num_comp, m_num_humn;         // fish count for human and computer.
  Position m_pos_comp, m_pos_humn;    // current position.
  bool m_comp_passed, m_humn_passed;  // is player passed the turn?
public:
  Board(const int s = 8) : m_size(s), m_num_comp(0), m_num_humn(0),
			   m_comp_passed(false), m_humn_passed(false) {
    for (int row = 0; row < s; ++row) {
      vector<Ice> arow;
      for (int col = 0; col < s; ++col) arow.push_back(Ice());
      m_board.push_back(arow);
    }
  }
  Position currentcomp() const { return m_pos_comp; }
  Position currenthumn() const { return m_pos_humn; }
  void init() {
    vector<int> row(m_size), col(m_size); auto gen = default_random_engine(rand());
    iota(row.begin(), row.end(), 0); shuffle(row.begin(), row.end(), gen);
    iota(col.begin(), col.end(), 0); shuffle(col.begin(), col.end(), gen);
    m_pos_comp = Position(row[0], col[0]);
    m_pos_humn = Position(row[1], col[1]);
    m_board[m_pos_comp.row()][m_pos_comp.col()].set_comp(); // place computer.
    m_board[m_pos_humn.row()][m_pos_humn.col()].set_humn(); // place human.
  }
  int get_fish_num(const Kind& k) const {
    return k == Kind::COMP? m_num_comp : m_num_humn;
  }
  void passed(const Kind& k) {
    switch(k) {
    case Kind::COMP: m_comp_passed = true; break;
    case Kind::HUMN: m_humn_passed = true; break;
    default: cerr << "Unknown switch at Board::passed ()..."; abort();
    }
  }
  bool is_game_over() const { return m_comp_passed && m_humn_passed; }
  bool is_valid_move(const Position& p, const Kind& k) const {
    if (!m_board[p.row()][p.col()].is_good()) return false;
    const Position& s = k == Kind::COMP? m_pos_comp : m_pos_humn;
    return true;
  }
  bool move(const Position& p, const Kind k) {
    if (!is_valid_move(p, k)) return false;
    switch(k) {
    case Kind::COMP:
      m_num_comp += m_board[m_pos_comp.row()][m_pos_comp.col()].get_fish();
      m_board[m_pos_comp.row()][m_pos_comp.col()].set_gone();
      m_pos_comp = p;
      m_board[m_pos_comp.row()][m_pos_comp.col()].set_comp();
      break;
    case Kind::HUMN:
      m_num_humn += m_board[m_pos_humn.row()][m_pos_humn.col()].get_fish();
      m_board[m_pos_humn.row()][m_pos_humn.col()].set_gone();
      m_pos_humn = p;
      m_board[m_pos_humn.row()][m_pos_humn.col()].set_humn();
      break;
    default: cerr << "Unknown switch at Board::move()..."; abort();
    }
    return true;
  }
  Position find_best_move(const int sz) const {
    int current_row = currentcomp().row(), current_col = currentcomp().col();
	double max_distance = 0, dis = 0; int max_row = 99, max_col = 99, cr = current_row, cc = current_col;
	if (current_row % 2 == 0){
			while ((cr >= 0 && cr <= sz - 1 ) && (cc >= 0 && cc <= sz - 1 ) ){ // case 1, even
				if (cr <= 0) break;     // if 0, break
				--cr;
				if (!is_valid_move(Position(cr,cc), Kind::COMP)) break; // if invalid, break
				dis = dist(current_row, current_col, cr, cc);
				if (dis > max_distance) { max_distance = dis; max_row = cr; max_col = cc;}
				if (cr == 0 || cc == 0) break;  // if 0 break
				--cr; --cc;
				if (!is_valid_move(Position(cr,cc), Kind::COMP)) break; // break if invalid
				dis = dist(current_row, current_col, cr, cc);
				if (dis > max_distance) { max_distance = dis; max_row = cr; max_col = cc; }
			}
			cr = current_row; cc = current_col; // reset variables
			while ((cr >= 0 && cr <= sz - 1 ) && (cc >= 0 && cc <= sz - 1 ) ){ // case 2, even
				if (cr >= sz - 1) break; // if reach sz - 1 (size), break
				++cr;
				if (!is_valid_move(Position(cr,cc), Kind::COMP)) break;
				dis = dist(current_row, current_col, cr, cc);
				if (dis > max_distance) { max_distance = dis; max_row = cr; max_col = cc;}
				if (cr >= sz - 1 || cc <= 0) break;
				++cr; --cc;
				if (!is_valid_move(Position(cr,cc), Kind::COMP)) break;
				dis = dist(current_row, current_col, cr, cc);
				if (dis > max_distance) { max_distance = dis; max_row = cr; max_col = cc;}
			}
			cr = current_row; cc = current_col;
			while ((cr >= 0 && cr <= sz - 1 ) && (cc >= 0 && cc <= sz - 1 )){ // case 3, even
				if (cr == 0 || cc >= sz - 1) break; // similar logic as above, but for 0 and sz - 1
				--cr; ++cc;
				if (!is_valid_move(Position(cr,cc), Kind::COMP)) break;
				dis = dist(current_row, current_col, cr, cc);
				if (dis > max_distance) { max_distance = dis; max_row = cr; max_col = cc;}
				if (cr <= 0) break; // break if 0
				--cr;
				if (!is_valid_move(Position(cr,cc), Kind::COMP)) break;
				dis = dist(current_row, current_col, cr, cc);
				if (dis > max_distance) { max_distance = dis; max_row = cr; max_col = cc;}

			}
			cr = current_row; cc = current_col;
			while ((cr >= 0 && cr <= sz - 1 ) && (cc >= 0 && cc <= sz - 1 )){ // case 4
				if (cr >= sz - 1 || cc >= sz - 1) break;
				++cr; ++cc;
				if (!is_valid_move(Position(cr,cc), Kind::COMP)) break;
				dis = dist(current_row, current_col, cr, cc);
				if (dis > max_distance) { max_distance = dis; max_row = cr; max_col = cc;}
				if (cr >= sz - 1 ) break;
				++cr;
				if (!is_valid_move(Position(cr,cc), Kind::COMP)) break;
				dis = dist(current_row, current_col, cr, cc);
				if (dis > max_distance) { max_distance = dis; max_row = cr; max_col = cc;}
			}
			cr = current_row; cc = current_col;
			while (cc >= 0){ // case 5 - left
				if (cc <= 0) break;
				--cc;
				if (!is_valid_move(Position(cr,cc), Kind::COMP)) break;
				dis = dist(current_row, current_col, cr, cc);
				if (dis > max_distance) { max_distance = dis; max_row = cr; max_col = cc;}
			}
			cr = current_row; cc = current_col;
			while (cc <= sz - 1){ // case 6 - right
				if (cc >= sz - 1) break;
				++cc;
				if (!is_valid_move(Position(cr,cc), Kind::COMP)) break;
				dis = dist(current_row, current_col, cr, cc);
				if (dis > max_distance) { max_distance = dis; max_row = cr; max_col = cc;}
			}
		}
		if (current_row % 2 == 1){ // case 1 but for starting row position odd
			while ((cr >= 0 && cr <= sz - 1 ) && (cc >= 0 && cc <= sz - 1 )){
				if (cr <= 0 || cc <= 0 ) break;  // break when 0
				--cr; --cc;
				if (!is_valid_move(Position(cr,cc), Kind::COMP)) break;
				dis = dist(current_row, current_col, cr, cc);
				if (dis > max_distance) { max_distance = dis; max_row = cr; max_col = cc;}
				if (cr <= 0) break;
				--cr;
				if (!is_valid_move(Position(cr,cc), Kind::COMP)) break;
				dis = dist(current_row, current_col, cr, cc);
				if (dis > max_distance) { max_distance = dis; max_row = cr; max_col = cc;}
				if (cr <= 0 || cr >= sz - 1 || cc <= 0 || cc >= sz -1 ) break;

			}
			cr = current_row; cc = current_col; // reset variables
			while ((cr >= 0 && cr <= sz - 1 ) && (cc >= 0 && cc <= sz - 1 )){ // case 2
				if (cr >= sz - 1 || cc <= 0) break;
				++cr; --cc;
				if (!is_valid_move(Position(cr,cc), Kind::COMP)) break;
				dis = dist(current_row, current_col, cr, cc);
				if (dis > max_distance) { max_distance = dis; max_row = cr; max_col = cc;}
				if (cr >= sz - 1 ) break;
				++cr;
				if (!is_valid_move(Position(cr,cc), Kind::COMP)) break;
				dis = dist(current_row, current_col, cr, cc);
				if (dis > max_distance) { max_distance = dis; max_row = cr; max_col = cc;}

			}
			cr = current_row; cc = current_col;
			while ((cr >= 0 && cr <= sz - 1 ) && (cc >= 0 && cc <= sz - 1 )){ // case 3
				if (cr <= 0 ) break;
				--cr;
				if (!is_valid_move(Position(cr,cc), Kind::COMP)) break;
				dis = dist(current_row, current_col, cr, cc);
				if (dis > max_distance) { max_distance = dis; max_row = cr; max_col = cc;}
				if (cr <= 0 || cc >= sz - 1) break;
				--cr; ++cc;
				if (!is_valid_move(Position(cr,cc), Kind::COMP)) break;
				dis = dist(current_row, current_col, cr, cc);
				if (dis > max_distance) { max_distance = dis; max_row = cr; max_col = cc;}
			}
			cr = current_row; cc = current_col;
			while ((cr >= 0 && cr <= sz - 1 ) && (cc >= 0 && cc <= sz - 1 )){ // case 4
				if (cr >= sz - 1) break;
				++cr;
				if (!is_valid_move(Position(cr,cc), Kind::COMP)) break;
				dis = dist(current_row, current_col, cr, cc);
				if (dis > max_distance) { max_distance = dis; max_row = cr; max_col = cc;}
				if (cr >= sz - 1 || cc >= sz - 1) break;
				++cr; ++cc;
				if (!is_valid_move(Position(cr,cc), Kind::COMP)) break;
				dis = dist(current_row, current_col, cr, cc);
				if (dis > max_distance) { max_distance = dis; max_row = cr; max_col = cc;}
			}
			cr = current_row; cc = current_col;
			while (cc >= 0){ // case 5 - left
				if (cc <= 0) break;
				--cc;
				if (!is_valid_move(Position(cr,cc), Kind::COMP)) break;
				dis = dist(current_row, current_col, cr, cc);
				if (dis > max_distance) { max_distance = dis; max_row = cr; max_col = cc;}
			}
			cr = current_row; cc = current_col;
			while (cc <= sz - 1){ // case 6 - right
				if (cc >= sz - 1) break;
				++cc;
				if (!is_valid_move(Position(cr,cc), Kind::COMP)) break;
				dis = dist(current_row, current_col, cr, cc);
				if (dis > max_distance) { max_distance = dis; max_row = cr; max_col = cc;}
			}
		}
    return Position(max_row,max_col); // just random position.
  }
  friend ostream& operator<<(ostream&, const Board&);
};

ostream& operator<<(ostream& o, const Board& b) {
  char c = 'Z' - b.m_size * 2 + 1;
  o << "  ";
  for (int col = 0, len = b.m_size * 2; col < len; ++col)
    o << setw(2) << char(c + col);
  o << endl;
  for (int row = 0; row < b.m_size; ++row) {
    cout << char('A' + row);
    if (!(row % 2)) o << setw(2) << ' ';
    for (int col = 0; col < b.m_size; ++col) o << b.m_board[row][col];
    o << endl;
  }
  return o;
}

Position parse(const int size = 1) {    // study this but do not change logic.
  cout << "Enter " << (size == 1? "board size (4 - 8): " : "your move: ");
  string line, token;
  char ce = 'a' + size - 1, cs = 'z' - size * 2 + 1, row, col;
  regex pattern0("[[:space:]]*[4-8][[:space:]]*");
  regex pattern1("quit|pass");
  regex pattern2("[a-" + string(1, ce) + "][[:space:]]*[" + string(1, cs) + "-z][[:space:]]*");
  while (getline(cin, line)) { // read a whole line and convert to lower cases.
    transform(line.begin(), line.end(), line.begin(), ::tolower);
    if (size <= 1 && regex_match(line, pattern0)) {
      istringstream iss(line);          // then read into 2 parts.
      int num; iss >> num;              // stringstream is the one to use!
      return Position(num, 0);
    }
    else if (regex_match(line, pattern1)) {  // match reset or quit?
      if (line.find("quit") != string::npos) return Position(-1, -1);
      if (line.find("pass") != string::npos) return Position(99, 99);
    }
    else if (regex_match(line, pattern2)) {  // match 2 word input?
      istringstream iss(line);          // then read into 2 parts.
      iss >> row >> col;                // stringstream is the one to use!
      int r = row - 'a', c = col - cs;  // obtain row and column indexes.
      if (r % 2 == 0) {
    	  c -= 1;         // the first trick for this game.
      	  if (c < 0) { cout << "Value error, try again: "; continue; }
      }
      if (c % 2 != 0) { cout << "Value error, try again: "; continue; }
      return Position(r, c / 2);        // c/2 is the second trick.
    }
    assert(!cin.fail());                // placed for debugging purpose.
    cout << "Syntax error, try again: ";
  }
  abort(); // should not reach here, placed debugging purpose.
}
bool validity (const int nr, const int nc, int cr, int cc, const int sz, const Board bn){
	int x = 0; int currentrow = cr, currentcol = cc;
	if (currentrow == nr) goto SAMEROW; // if same row, go to bottom
	if (currentrow % 2 == 0){
		while ((cr >= 0 && cr <= sz - 1 ) && (cc >= 0 && cc <= sz - 1 ) && x==0){ // case 1, even
			if (cr <= 0) break; // if this is 0, break
			--cr;
			if (!bn.is_valid_move(Position(cr,cc), Kind::HUMN)) break; // if hit "gone" or "comp", break
			if (cr == nr && cc == nc) x = 1;
			if (cr <= 0 || cc <= 0) break;
			--cr; --cc;
			if (!bn.is_valid_move(Position(cr,cc), Kind::HUMN)) break;
			if (cr == nr && cc == nc) x = 1;
		}
		cr = currentrow; cc = currentcol;
		while ((cr >= 0 && cr <= sz - 1 ) && (cc >= 0 && cc <= sz - 1 ) && x == 0){ // case 2
			if (cr >= sz - 1) break;
			++cr;
			if (!bn.is_valid_move(Position(cr,cc), Kind::HUMN)) break;
			if (cr == nr && cc == nc)  x = 1;
			if (cr >= sz - 1 || cc <= 0) break;
			++cr; --cc;
			if (!bn.is_valid_move(Position(cr,cc), Kind::HUMN)) break;
			if (cr == nr && cc == nc)  x = 1;
		}
		cr = currentrow; cc = currentcol;
		while ((cr >= 0 && cr <= sz - 1 ) && (cc >= 0 && cc <= sz - 1 ) && x==0){ // case 3
			if (cr <= 0 || cc >= sz - 1) break;
			--cr; ++cc;
			if (!bn.is_valid_move(Position(cr,cc), Kind::HUMN)) break;
			if (cr == nr && cc == nc)  x = 1;
			if (cr <= 0) break;
			--cr;
			if (!bn.is_valid_move(Position(cr,cc), Kind::HUMN)) break;
			if (cr == nr && cc == nc)  x = 1;
		}
		cr = currentrow; cc = currentcol;
		while ((cr >= 0 && cr <= sz - 1 ) && (cc >= 0 && cc <= sz - 1 ) && x==0){ // case 4
			if (cr >= sz - 1 || cc >= sz - 1) break;
			++cr; ++cc;
			if (!bn.is_valid_move(Position(cr,cc), Kind::HUMN)) break;
			if (cr == nr && cc == nc)  x = 1;
			if (cr >= sz - 1) break;
			++cr;
			if (!bn.is_valid_move(Position(cr,cc), Kind::HUMN)) break;
			if (cr == nr && cc == nc)  x = 1;
		}
	}
	if (currentrow % 2 == 1){
		while ((cr >= 0 && cr <= sz - 1 ) && (cc >= 0 && cc <= sz - 1 ) && x==0){ // case 1, for odd
			if (cr <= 0 || cc <= 0) break; // if cr or cc 0, break
			--cr; --cc;
			if (!bn.is_valid_move(Position(cr,cc), Kind::HUMN)) break; // check for validity
			if (cr == nr && cc == nc)  x = 1;
			if (cr <= 0) break;
			--cr;
			if (!bn.is_valid_move(Position(cr,cc), Kind::HUMN)) break;
			if (cr == nr && cc == nc)  x = 1;
		}
		cr = currentrow; cc = currentcol;
		while ((cr >= 0 && cr <= sz - 1 ) && (cc >= 0 && cc <= sz - 1 ) && x==0){ // case 2
			if (cr >= sz - 1 || cc <= 0) break;
			++cr; --cc;
			if (!bn.is_valid_move(Position(cr,cc), Kind::HUMN)) break;
			if (cr == nr && cc == nc)  x = 1;
			if (cr >= sz - 1)  break;
			++cr;
			if (!bn.is_valid_move(Position(cr,cc), Kind::HUMN)) break;
			if (cr == nr && cc == nc)  x = 1;
		}
		cr = currentrow; cc = currentcol;
		while ((cr >= 0 && cr <= sz - 1 ) && (cc >= 0 && cc <= sz - 1 ) && x==0){ // case 3
			if (cr <= 0) break;
			--cr;
			if (!bn.is_valid_move(Position(cr,cc), Kind::HUMN)) break;
			if (cr == nr && cc == nc)  x = 1;
			if (cr <= 0 || cc >= sz -1) break;
			--cr; ++cc;
			if (!bn.is_valid_move(Position(cr,cc), Kind::HUMN)) break;
			if (cr == nr && cc == nc)  x = 1;
		}
		cr = currentrow; cc = currentcol;
		while ((cr >= 0 && cr <= sz - 1 ) && (cc >= 0 && cc <= sz - 1 ) && x==0){ // case 4
			if (cr >= sz - 1) break;
			++cr;
			if (!bn.is_valid_move(Position(cr,cc), Kind::HUMN)) break;
			if (cr == nr && cc == nc)  x = 1;
			if (cr >= sz - 1 || cc >= sz - 1) break;
			++cr; ++cc;
			if (!bn.is_valid_move(Position(cr,cc), Kind::HUMN)) break;
			if (cr == nr && cc == nc)  x = 1;
		}
	}
	SAMEROW: // sweeps left and right.
	while (cc >= 0 && x==0){ // for going left
		if (cc <= 0 ) break;
		--cc;
		if (!bn.is_valid_move(Position(cr,cc), Kind::HUMN)) break;
		if (cr == nr && cc == nc)  x = 1;
	}
	cr = currentrow; cc = currentcol;
	while (cc <= sz - 1 && x==0){ // for going right
		if (cc >= sz - 1) break;
		++cc;
		if (!bn.is_valid_move(Position(cr,cc), Kind::HUMN)) break;
		if (cr == nr && cc == nc)  x = 1;
	}
	return x==1? true: false;
}

int main() {
  srand(time(0));  // activate randomized effect at product delivery.
  cout << "Hey, That's My Fish, Akira's Version!" << endl;
  Position next = parse(); Position next2; int size = next.row();
  Board b(size); b.init();

  while(!b.is_game_over()) { // game over is both players passed their turn.
    cout << endl <<  b;
    cout << endl << "Your fish count is " << b.get_fish_num(Kind::HUMN)
	 << ", and computer's fish count is " << b.get_fish_num(Kind::COMP)
	 << "..." << endl;
    bool valid_move;
    do {
      bool isvalid = true;
      next = parse(size);                             // read your turn.
      if (next.row() < 0 && next.col() < 0) goto end; // you quit the game.
      if (next.row() > 90 && next.col() > 90) {       // you passed your turn.
    	  b.passed(Kind::HUMN);
    	  cout << "You passed..." << endl;
    	  break;
      }
      isvalid = validity(next.row(), next.col(), b.currenthumn().row(), b.currenthumn().col(), size, b);
      // ^ checks for validitty, v--- if valid, does the move.
      valid_move = (isvalid? b.move(next, Kind::HUMN) : false );
      if (!valid_move) 	cout << "You can't move there..." << endl;
    } while (!valid_move);
    next2 = b.find_best_move(size);						// find computer's move.
    if (next2.row() == 99 && next2.col() == 99 ){  // if passed
    	cout << "Computer passed...\n"; b.passed(Kind::COMP); continue;}
    b.move(next2, Kind::COMP);                         // place the chosen move.
  }
 end:  // goto usage is generally bad, but convenient for this kind of case.
  if (b.get_fish_num(Kind::HUMN) == b.get_fish_num(Kind::COMP)) cout << "[ TIE GAME ]\n";
  else cout << (b.get_fish_num(Kind::HUMN) > b.get_fish_num(Kind::COMP)?
		  "[ Game ended. YOU WON! ]\n" : "[ Game ended. YOU LOST! ]\n");
  cout << "Bye..." << endl;
  return 0;
}
