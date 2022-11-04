// XnaCpp.cpp: define o ponto de entrada para o aplicativo.
//

#include "Main.hpp"
#include "Vector3.hpp"
#include "Matrix.hpp"
#include "CSharp/Nullable.hpp"
#include <vector>
#include <memory>

using namespace std;
using namespace Xna;
using namespace CSharp;

int Teste(Nullable<Vector3> const& vector3) {
	return vector3.HasValue() ? 0 : 1;
}

int main()
{
	Nullable<Vector3> _nullable;
	cout << Teste(csnull);

	return 0;
}
