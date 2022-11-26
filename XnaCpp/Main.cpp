// XnaCpp.cpp: define o ponto de entrada para o aplicativo.
//

#include "Main.hpp"
#include "Vector3.hpp"
#include "Matrix.hpp"
#include "CSharp/Nullable.hpp"
#include <vector>
#include <memory>
#include <typeinfo>
#include <type_traits>

using namespace std;
using namespace Xna;
using namespace CSharp;

int main()
{	
	shared_ptr<void> point = make_shared<int>(5);

	auto ref = static_pointer_cast<string>(point);

	cout << ref << endl;

	return 0;
}
