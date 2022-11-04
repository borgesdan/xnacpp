# CMakeList.txt: projeto de CMake para XnaCpp, incluir origem e definir
# lógica específica a um projeto aqui.
#
cmake_minimum_required (VERSION 3.8)

# Adicione a origem ao executável deste projeto.
add_executable (XnaCpp 
			"CSharp/TimeSpan.cpp"  
			"CSharp/Nullable.cpp"
			"Main.cpp" 
			"Point.cpp" 
			"Rectangle.cpp" 
			"GameTime.cpp"  
			"Vector2.cpp" 
			"MathHelper.cpp"  
			"Vector3.cpp" 
			"Vector4.cpp"
			"Color.cpp"
			"Quaternion.cpp"
			"Matrix.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET XnaCpp PROPERTY CXX_STANDARD 20)
endif()

# TODO: Adicione testes e instale destinos, se necessário.
