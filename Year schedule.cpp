#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
#include <ctime>
#include <string>
using namespace std;
//Randomize day and get the string
string Getday (int x) {
	string day;
	switch (x) {
	case 0 : day = "Mon"; break;
	case 1 : day = "Tue"; break;
	case 2 : day = "Wed"; break;
	case 3 : day = "Thu"; break;
	case 4 : day = "Fri"; break;
	case 5 : day = "Sat"; break;
	case 6 : day = "Sun";
	}
	return day;
}
//Randomize month and get the string
string Getmonth (int x) {
	string month;
	switch(x) {
	case 0 : month = "Jan"; break;
	case 1 : month = "Feb"; break;
	case 2 : month = "Mar"; break;
	case 3 : month = "Apr"; break;
	case 4 : month = "May"; break;
	case 5 : month = "Jun"; break;
	case 6 : month = "Jul"; break;
	case 7 : month = "Aug"; break;
	case 8 : month = "Sep"; break;
	case 9 : month = "Oct"; break;
	case 10 : month = "Nov"; break;
	case 11 : month = "Dec";
	}
	return month;
}
//Randomize appointment and get the string
string Getappoint (int x) {
	string appoint;
	switch(x) {
	case 0 : appoint = "EVENT"; break;
	case 1 : appoint = "DUTY";
	}
	return appoint;
}
//Get the type of appointment
string Get_type (string x, int y) {
	string type;
	if (x == "EVENT") {
		switch(y) {
			case 0 : type = "PARTY"; break;
			case 1 : type = "ANNIV";
			}
	}
	if (x == "DUTY") {
		switch(y) {
			case 0 : type = "SCHOOL"; break;
			case 1 : type = "FAMILY";
		}
	}
	return type;
}

//event class will hold all relevant information
class event {
public:
	string app;
	string apptype;
	string wday;
	string mon;
	int mday;
	int hour;
	int min;
	int sec;
	int year;
	int num_mon;
	event (const string& a = "", const string& b = "", const string& c = "", const string& d = "",const int& e = 0, const int& f = 0, const int& g = 0, const int& h = 0, const int& i = 0, const int& j = 0) {
		app = a;
		apptype = b;
		wday = c;
		mon = d;
		mday = e;
		hour = f;
		min = g;
		sec = h;
		year = i;
		num_mon = j;
	}
};

//Inherit event
class Scheduler {
private:
	//vector<event> store;

public:
	vector<event> store;
	Scheduler(int n) {
		srand(time(0));
		for (int i = 0; i < n; ++i) {
			int sec = 0;
			int min = 15 * (rand() % 3);
			int hour = rand() % 10 + 7;
			int mday = rand() % 30 + 1;
			int num_mon = rand() % 12;
			string mon = Getmonth(num_mon);
			int year = 2014;
			string wday = Getday(rand() % 7);
			string app = Getappoint(rand() % 2);
			string apptype = Get_type(app,rand() % 2);
			store.push_back(event(app,apptype,wday,mon,mday,hour,min,sec,year,num_mon));
		}
	}

	friend ostream& operator<<(ostream& o, Scheduler& a) {
		for (int i = 0, len = a.store.size(); i < len; ++i) {
			o << a.store[i].app << ": " << a.store[i].apptype << " " << a.store[i].wday << " " << a.store[i].mon << " "<< a.store[i].mday << " " << a.store[i].hour << ":" << a.store[i].min << ":" << a.store[i].sec  << " " << a.store[i].year << endl;
		}
		return o;
	}

	friend istream& operator>>(istream& i, event& a) {
		return i >> a.app >> a.apptype >> a.wday >> a.mon >> a.mday >> a.hour >> a.min >> a.sec >> a.year;
	}

	void write(string x){
		ofstream myschedule(x);
		assert(myschedule);
			for (int i = 0, len = store.size(); i < len; ++i) {
				myschedule << store[i].app << " " << store[i].apptype << " " << store[i].wday << " " << store[i].mon << " "<< store[i].mday << " " << store[i].hour << " " << store[i].min << " " << store[i].sec << "0" << " " << store[i].year << endl;

		}
		myschedule.close();
		cout << "Writing to '"<< x << "' completed!" << endl << endl;
	}

	void order(){
		bool swap;
		do {
			swap = false;
			for (int i = 0, len = store.size() - 1; i < len; ++i) {
				if (store[i].num_mon > store[i+1].num_mon) {
					event temp;
					temp = store[i];
					store[i] = store[i+1];
					store[i+1] = temp;
					swap = true;
				}

				if (store[i].num_mon == store[i+1].num_mon) {
					if (store[i].mday > store[i+1].mday) {
						event temp;
						temp = store[i];
						store[i] = store[i+1];
						store[i+1] = temp;
						swap = true;
					}

					if (store[i].mday == store[i+1].mday) {
						if (store[i].hour > store[i+1].hour) {
							event temp;
							temp = store[i];
							store[i] = store[i+1];
							store[i+1] = temp;
							swap = true;
						}

						if (store[i].hour == store[i+1].hour) {
							if (store[i].min > store[i+1].min) {
								event temp;
								temp = store[i];
								store[i] = store[i+1];
								store[i+1] = temp;
								swap = true;
							}
						}
					}
				}
			}
		} while (swap == true);
	}

	void read(string x){
		ifstream myschedule(x);
		assert(myschedule);
		store.clear();
		event a;
		while(true) {
			myschedule >> a.app >> a.apptype >> a.wday >> a.mon >> a.mday >> a.hour >> a.min >> a.sec >> a.year;
			store.push_back(a);

			if (myschedule.eof()) break;
		}
		myschedule.close();
		cout << "Reading from '"<< x << "' completed!" << endl;
	}


};


int main () {
	Scheduler s(20);
	cout << s;

	s.write("scheduler.data");
	s.order();

	cout << "AFTER SORTING..." << endl << endl;

	cout << s;

	s.read("scheduler.data");


	cout << endl << "Current contents of scheduler.data:" << endl;
	cout << s;
	return 0;
}
