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
			"Vector4.cpp" 
			"CurveTangent.cpp" 
			"CurveLoopType.cpp"
			"CurveKey.cpp" 
			"CurveContinuity.cpp"
			"CurveKeyCollection.cpp"
			"Curve.cpp"
			"ICurveEvaluator.cpp"
			"GameWindow.cpp" "Platform/SDL/SdlGameWindow.cpp" "Platform/SDL/SdlGamePlatform.cpp" "GamePlatform.cpp" "GameRunBehavior.cpp" "Game.cpp" "Graphics/PresentationParameters.cpp" "Graphics/States/DepthFormat.cpp" "Graphics/SuurfaceFormat.cpp" "GraphicsDeviceManager.cpp" "Graphics/IGraphicsDeviceService.cpp" "Graphics/GraphicsDevice.cpp" "IGraphicsDeviceManager.cpp" "Graphics/GraphicsProfile.cpp" "GraphicsDeviceInformation.cpp" "Graphics/GraphicsAdapter.cpp" "GameServiceContainer.cpp" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET XnaCpp PROPERTY CXX_STANDARD 20)
endif()

# TODO: Adicione testes e instale destinos, se necessário.
