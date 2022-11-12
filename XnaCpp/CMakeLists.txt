# CMakeList.txt: projeto de CMake para XnaCpp, incluir origem e definir
# lógica específica a um projeto aqui.
#
cmake_minimum_required (VERSION 3.8)

# Adicione a origem ao executável deste projeto.
add_executable (XnaCpp 
			"CSharp/Nullable.cpp"
			"CSharp/TimeSpan.cpp"  
			"BoundingBox.cpp"
			"BoundingFrustum.cpp"
			"BoundingSphere.cpp"
			"Color.cpp"
			"ContainmentType.cpp"
			"GameTime.cpp"  
			"Main.cpp" 
			"MathHelper.cpp"  
			"Matrix.cpp"
			"Plane.cpp"
			"PlaneIntersectionType.cpp"
			"Point.cpp" 
			"Ray.cpp"
			"Rectangle.cpp" 
			"Quaternion.cpp"
			"Vector2.cpp" 
			"Vector3.cpp" 
			"Vector4.cpp" "CurveTangent.cpp" "CurveLoopType.cpp" "CurveKey.cpp" "CurveContinuity.cpp" "CurveKeyCollection.cpp" "Curve.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET XnaCpp PROPERTY CXX_STANDARD 20)
endif()

# TODO: Adicione testes e instale destinos, se necessário.
