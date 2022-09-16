// XnaCpp.cpp: define o ponto de entrada para o aplicativo.
//

#include "Main.hpp"

using namespace std;
using namespace Xna;

int main()
{
	Point point;	

	cout << point.X << point.Y << endl;

	point.X = 30;
	point.Y = 60;

	cout << point.X << " " << point.Y << endl;
	return 0;
}
