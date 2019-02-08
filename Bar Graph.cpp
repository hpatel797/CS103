#include "Simple_window.h"
#include "Graph.h"
#include <iostream>
#include <vector>
#include <time.h>
using namespace std;
using namespace Graph_lib;

void EnterGrades(int num, vector<int> & g ) {
	//Ask User if they want to randomize or enter the grades
	vector<int> all_grade;		//Records all the grades
	string yorn;
	srand(time(NULL)); 		//Ensure number is more 'randomized'
	cout << "Would you like to randomize the grades?" << endl;
	do {
		cout << "Please enter yes or no" << endl;
		cin >> yorn;
		for (int i = 0; i < 3; ++i) tolower(yorn[i]);
	} while (yorn != "yes" && yorn != "no");

	if (yorn == "yes") {
		for (int i = 0; i < num; ++i){
			int score;
			score = rand() % 101;
			all_grade.push_back(score);
		}
	}
	if (yorn == "no") {
		cout << "Please proceed to enter the scores. The range is from 0 - 100." << endl;
		for (int i = 0; i < num; ++i) {
			int score;
			do {
			cout << "Student #" << i+1 << ": ";
			cin >> score;
			} while (score < 0 || score > 100);
			all_grade.push_back(score);
		}
	}
	//Check for grade intervals and place it accordingly into vector
	for (int i = 0; i < num; ++i) {
		int interval;
		interval = 0;
		interval = all_grade[i] / 10;
		++g[interval];
		if (interval == 10) {
			++g[9];
		}
	}
}

int main() {
	vector<int> grades (10, 0) ;	//10 spots because 10 intervals
	Vector_ref<Rectangle> rec;
	Vector_ref<Line> lin;
	int input;
	int max;
	int axiscolor;
	int labelcolor;
	int columncolor;
	int linecolor;
	string ytext;
	input = 0;
	max = 0;
	axiscolor = 0;
	labelcolor = 0;
	columncolor = 0;
	//Ask for User Input
	cout << "Number of Students: ";
	cin >> input;
	EnterGrades(input, grades);
	cout << "Enter Color # [0-255]:" << endl;
	cout << "Axis: " ;
	cin >> axiscolor;
	cout << "Label: ";
	cin >> labelcolor;
	cout << "Column: ";
	cin >> columncolor;
	cout << "Line: ";
	cin >> linecolor;

	//Find the maximum value
	for (int i = 0; i < 10; ++i) {
		if (grades[i] > max) max = grades[i];
	}

	//Initialize window
	cout << "Expand window and click next"<< endl;
	Simple_window win(Point(100,100),600,700,"A Plot of Grades");
	win.wait_for_button();

	//Text for y-axis
	ytext += "Number of Students in the grade range; maximum value: ";
	ytext += to_string(max);
	ytext += " students.";

	//Initialize axis, make sure y-axis adjusts accordingly
	if (max <= 9) max = 9;
	Axis xa(Axis::x,Point(30,650),550,10,"Grades from 0 to 100. Each range holds 10 values.");
	xa.set_color(axiscolor);
	xa.label.set_color(labelcolor);
	win.attach(xa);
	Axis ya(Axis::y,Point(30,650),600,max+1, ytext);
	ya.set_color(axiscolor);
	ya.label.set_color(labelcolor);
	win.attach(ya);

	//Rectangles and line
	for (int i = 0; i < 10; ++i) {
		int xcoord;
		int xacoord;
		int ycoord;
		int yacoord;
		xcoord = i * 50 + 50;
		xacoord = (i+1) * 50 + 50;
		ycoord = 650 - grades[i] * (600 / (max+1));
		yacoord = 650 - grades[i+1] * (600 / (max+1));
		rec.push_back(new Rectangle(Point(xcoord , ycoord), 30, 651 - ycoord));
		rec[i].set_fill_color(columncolor);
		win.attach(rec[i]);
	}
	Line l(Point(30,650),Point(65,650 - grades[0] * (600/ (max+1))));
	l.set_style(Line_style(Line_style::dash,2));
	l.set_color(linecolor);
	win.attach(l);
	for (int i = 0; i < 9; ++i){
		int xcoord;
		int xacoord;
		int ycoord;
		int yacoord;
		xcoord = i * 50 + 50;
		xacoord = (i+1) * 50 + 50;
		ycoord = 650 - grades[i] * (600 / (max+1));
		yacoord = 650 - grades[i+1] * (600 / (max+1));
		lin.push_back(new Line(Point(xcoord + 15, ycoord),Point(xacoord + 15, yacoord)));
		lin[i].set_style(Line_style(Line_style::dash,2));
		lin[i].set_color(linecolor);
		win.attach(lin[i]);
	}

	win.set_label("A Plot of Grades");
	win.wait_for_button();
	return 0;
}
