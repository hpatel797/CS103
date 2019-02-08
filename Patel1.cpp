//============================================================================
// Name        : Patel1.cpp
// Author      : Harsh Patel
// Version     :
// Copyright   : Your copyright notice
// Description : Programming Assignment 1
//============================================================================

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main(){

	/*double pi_val = (4./sqrt(522))*log((pow((5.+sqrt(29)/sqrt(2)),3))*(5.*sqrt(29)+11.*sqrt(6))*pow(sqrt((9.+3*sqrt(6))/4)+sqrt((5.+3*sqrt(6)/4))),6);
	I broke up the Srinivasa equation into terms such as a,b,c,d,e,f to not mess up parenthesis in the long equation as attempted above ^^ */

	double a = 4./sqrt(522),
		   b = pow((5.+sqrt(29))/sqrt(2),3),
		   g = sqrt(6)
		   c = 5*sqrt(29) + 11*g,
		   d = sqrt((9.+3*g)/4),
		   e = sqrt((5.+3*)/4),
		   f = pow(d+e,6);
    double pi_val = a*log(b*c*f); // the main equation after substituting the above terms
	cout << setprecision(30) <<"The value of Pi using  Srinivasa Ramanujan's equation is: "<< pi_val << endl;

	int n=1; double pi_val2; //pi_val2 is the value after using the polygon method.

	while (M_PI != pi_val2 || pi_val2 != pi_val) { //while loop will break as soon as pi_val2 equals either M_PI (defined in cmath) or pi_val (calculated using srinivasa equation above).

		pi_val2 = n*sin(M_PI/n); //deg_to_rad = (180/n) * (M_PI/180);, can be written as simply (M_PI/n)
		n++;

	} //ends while loop
	cout << "The value of n-polygon is: " << n << "\nAnd the value of pi at that point is: " << pi_val2 <<endl;
	return 0;
}
