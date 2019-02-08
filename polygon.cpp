#include "Simple_window.h"
#include "Graph.h"
#include <iostream>
#include <math.h>
#include <vector>

#define PI 3.14159265

using namespace std;
using namespace Graph_lib;

int main()
{
    int num;
    string pointnum;
    //Take and Check Number
    while (true){
    	cout << "Enter a number of points greater than 2, to quit enter 0" << endl;
    	cin >> num;
		while (num <= 2 && num != 0){
			cout << "Error. Please enter a number greater than 2." << endl;
			cin >> num;
		}
		if (num == 0) break;
		cout << "Expand window and click 'Next'."<< endl;
		pointnum = to_string(num);
		pointnum +=" points generated";

		Simple_window win(Point(100,100),600,600,"Polygon Generator#1");
		win.wait_for_button();

		//Creating Axis, all points must be multiplied by 6
		Axis xa(Axis::x,Point(30,550),480,8,"x axis");
		win.set_label("Polygon Generator#2");
		win.attach(xa);
		Axis ya(Axis::y,Point(30,550),480,8,"y axis");
		win.attach(ya);

		//Create text on top
		Text t(Point(150,25),"Random Polygon Generation");
		t.set_font_size(20);
		t.set_color(Color::blue);
		win.attach(t);
		Text k(Point(225,45), pointnum);
		win.attach(k);

		//Create the polygon, center is (240,240) ; (270,310)
		Polygon poly;
		int length;
		double x;
		double y;
		double add;
		double signedArea;
		double a;
		double xcent;
		double ycent;
		vector<double>xcord;
		vector<double>ycord;

		a = 0;
		signedArea = 0;
		xcent = 0;
		ycent = 0;

		for (int i = 0; i < num; ++i){
			add = (2 * PI) / num;
			length = 6*(rand() % 39 + 1);
			add *= i;
			x = length*cos(add) + 270;
			y = length*sin(add) + 310;
			poly.add(Point(x,y));
			poly.set_color(Color::red);
			win.attach(poly);
			xcord.push_back(x);
			ycord.push_back(y);
		}

		//Calculate location of centroid
		int i = 0;
		for (i = 0; i < num - 1; ++i){
			a = (xcord[i] * ycord[i+1] - xcord[i+1] * ycord[i]);
			signedArea += a;
			xcent += ((xcord[i] + xcord[i+1]) * a);
			ycent += ((ycord[i] + ycord[i+1]) * a);
		}
		//Last vertex
		a = (xcord[i] * ycord[0] - xcord[0] * ycord[i]);
		signedArea += a;
		xcent += ((xcord[i] + xcord[0]) * a);
		ycent += ((ycord[i] + ycord[0]) * a);
		xcord.clear();
		ycord.clear();
		signedArea *= 0.5;
		xcent /= (signedArea * 6);
		ycent /= (signedArea * 6);

		//Create centroid with circle and text
		Circle c(Point(xcent,ycent),7);
		c.set_color(Color::blue);
		Mark m(Point(xcent,ycent),'c');
		m.set_color(Color::blue);
		win.attach(c);
		win.attach(m);

		win.wait_for_button();
    }
    return 0; //added in after submition
