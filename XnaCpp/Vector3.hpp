#ifndef _VECTOR3_HPP_
#define _VECTOR3_HPP_

#include "Vector2.hpp"

namespace Xna {
	struct Vector3 {
		float X{ 0 };
		float Y{ 0 };
		float Z{ 0 };

		static const Vector3 Zero;
		static const Vector3 One;
		static const Vector3 UnitX;
		static const Vector3 UnitY;
		static const Vector3 UnitZ;
		static const Vector3 Up;
		static const Vector3 Down;
		static const Vector3 Left;
		static const Vector3 Right;
		static const Vector3 Forward;
		static const Vector3 Backward;

		Vector3();
		Vector3(float value);
		Vector3(float x, float y, float z);
		Vector3(Vector2 value, float z);

		static Vector3 Add(Vector3 const& value1, Vector3 const& value2);
		static Vector3 Barycentric(Vector3 const& value1, Vector3 const& value2, Vector3 const& value3, float amount1, float amount2);
		static Vector3 CatmullRom(Vector3 const& value1, Vector3 const& value2, Vector3 const& value3, Vector3 const& value4, float amount);
		static Vector3 Ceiling(Vector3 const& value);
		static Vector3 Clamp(Vector3 const& value1, Vector3 const& min, Vector3 const& max);
		static Vector3 Cross(Vector3 const& vector1, Vector3 const& vector2);
		static float Distance(Vector3 const& value1, Vector3 const& value2);
		static float DistanceSquared(Vector3 const& value1, Vector3 const& value2);
		static Vector3 Divide(Vector3 const& value1, Vector3 const& value2);
		static Vector3 Divide(Vector3 const& value1, float divider);
		static float Dot(Vector3 const& value1, Vector3 const& value2);

		void Ceiling();
		bool Equals(Vector3 const& other) const;
	};
}

#endif