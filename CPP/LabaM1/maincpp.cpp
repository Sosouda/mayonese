#include <iostream>
#include <cmath>
using namespace std;

const double Ep = pow(10,-6);
const double pi = 3.14;

double kvdrt(double x) {
	if (x <= 0) {
		cout << "x < 0" << endl;
	}
	else {
		int It = 0;
		double x1 = x;
		double x0;
		do {
			It++;
			x0 = x1;
			x1 = (x0 + x / x0) / 2;
		} while (fabs(x0 - x1) > Ep);
		return x1;
	}
}


double ex(double x) {
	int It = 0;
	double sum = 1;
	double a = 1;
	for (int k = 1; fabs(a) > Ep; k++) {
		It++;
		a = a * x / k;
		sum += a;
	}
	return sum;
}

double cosinus(double x) {
	int It = 0;
	double sum = 1;
	x = fmod(x, 2 * pi);
	if (x > pi) x -= pi;
	if (x > pi / 2)x = pi - x;
	double a = 1;
	//bool neg = false;
	for (int k = 1; fabs(a) > Ep;k++) {
		It++;
		a = -a * (pow(x, 2) / (2 * k * (2 * k - 1)));
		sum += a;
		/*if (a < 0) {
			neg = !neg;
		}*/
	}
	//if (neg) sum = -sum;
	return sum;
}

double sinus(double x) {
	int It = 0;
	double sum = 0;
	x = fmod(x, 2 * pi);
	if (x > pi) {
		x -= pi;
		x *= -1;
	}
	double a = 1;
	for (int k = 1; fabs(a) > Ep;k++) {
		It++;
		a = -a * ((pow(x, 2)) / (2 * k * (2 * k + 1)));
		sum += a;
		

	}
	return sum;
}


int main() {
	//f(x) = (sin(x) + 8cos(x)) * e^(sin(x)*cos(x))
	cout << cosinus(12) << " "<< sinus(12) <<" "<< cos(12) << " " << sin(12) << endl;
	cout << 8 *cosinus(12)<<" "<< 8 * cos(12) << endl;
	cout << 8*cosinus(12) + sinus(12) << " " << 8 * cos(12) + sin(12)<<endl;
	cout << cosinus(12) * sinus(12) << " " << cos(12) * sin(12) << endl;
	double em = cosinus(12) * sinus(12), ec = cos(12) * sin(12);
	cout << ex(em) << " " << exp(ec) << endl;


	long double func = 0 , funm = 0;
	funm = ((sinus(12) + 8 * cosinus(12)) * ex((sinus(12) * cosinus(12))));
	func = ((sin(12) + 8 * cos(12)) * exp((cos(12) * sin(12))));
	cout << func << " "<< funm << endl;


	
}