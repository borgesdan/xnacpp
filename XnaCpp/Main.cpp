// XnaCpp.cpp: define o ponto de entrada para o aplicativo.
//

#include "Main.hpp"

using namespace std;
using namespace Xna;

int main()
{
	Point p1;		

	cout << p1.X << p1.Y << endl;

	p1.X = 30;
	p1.Y = 60;

	Point p2 = Point(p1);

	cout << p2.X << " " << p2.Y << endl;

	auto p3 = p2 + p1;


	return 0;
}
