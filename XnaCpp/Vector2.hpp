#ifndef _VECTOR2_HPP_
#define _VECTOR2_HPP_

#include <vector>

namespace Xna {	

	struct Point;
	struct Matrix;
	struct Quaternion;

	struct Vector2 {
		float X{ 0 };
		float Y{ 0 };

		static const Vector2 Zero;
		static const Vector2 One;
		static const Vector2 UnitX;
		static const Vector2 UnitY;

		Vector2();
		Vector2(float x, float y);
		Vector2(float value);

		Vector2 operator -() const;
		friend Vector2 operator -(Vector2 const& value1, Vector2 const& value2);
		friend Vector2 operator *(Vector2 const& value1, Vector2 const& value2);
		friend Vector2 operator *(Vector2 const& value, float scaleFactor);
		friend Vector2 operator *(float scaleFactor, Vector2 const& value);
		friend Vector2 operator /(Vector2 const& value1, Vector2 const& value2);
		friend Vector2 operator /(Vector2 const& value1, float divider);
		friend bool operator ==(Vector2 const& value1, Vector2 const& value2);
		friend bool operator !=(Vector2 const& value1, Vector2 const& value2);

		static Vector2 Add(Vector2 const& value1, Vector2 const& value2);
		static Vector2 Barycentric(Vector2 const& value1, Vector2 const& value2,
			Vector2 const& value3, float amount1, float amount2);
		static Vector2 CatmullRom(Vector2 const& value1, Vector2 const& value2,
			Vector2 const& value3, Vector2 const& value4, float amount);
		static Vector2 Ceiling(Vector2 const& value);
		static Vector2 Clamp(Vector2 const& value1, Vector2 const& min, Vector2 const& max);
		static float Distance(Vector2 const& value1, Vector2 const& value2);
		static float DistanceSquared(Vector2 const& value1, Vector2 const& value2);
		static Vector2 Divide(Vector2 const& value1, Vector2 const& value2);
		static Vector2 Divide(Vector2 const& value1, float divider);
		static float Dot(Vector2 const& value1, Vector2 value2);
		static Vector2 Floor(Vector2 const& value);
		static Vector2 Hermite(Vector2 const& value1, Vector2 const& tangent1,
			Vector2 const& value2, Vector2 const& tangent2, float amount);
		static Vector2 Lerp(Vector2 const& value1, Vector2 const& value2, float amount);
		static Vector2 LerpPrecise(Vector2 const& value1, Vector2 const& value2, float amount);
		static Vector2 Max(Vector2 const& value1, Vector2 const& value2);
		static Vector2 Min(Vector2 const& value1, Vector2 const& value2);
		static Vector2 Multiply(Vector2 const& value1, Vector2 const& value2);
		static Vector2 Multiply(Vector2 const& value1, float scaleFactor);
		static Vector2 Negate(Vector2 const& value);
		static Vector2 Normalize(Vector2 const& value);
		static Vector2 Reflect(Vector2 const& vector, Vector2 const& normal);
		static Vector2 Round(Vector2 const& value);
		static Vector2 SmoothStep(Vector2 const& value1, Vector2 const& value2, float amount);
		static Vector2 Subtract(Vector2 const& value1, Vector2 const& value2);
		
		static Vector2 Transform(Vector2 const& position, Matrix const& matrix);
		static Vector2 Transform(Vector2 const& value, Quaternion const& rotation);
		static void Transform(std::vector<Vector2> const& sourceArray, size_t sourceIndex, Matrix const& matrix,
			std::vector<Vector2>& destinationArray, size_t destinationIndex, size_t length);
		static void Transform(std::vector<Vector2> const& sourceArray, size_t sourceIndex, Quaternion const& rotation,
			std::vector<Vector2>& destinationArray, size_t destinationIndex, size_t length);
		static void Transform(std::vector<Vector2> const& sourceArray, Matrix const& matrix, std::vector<Vector2>& destinationArray);
		static void Transform(std::vector<Vector2> const& sourceArray, Quaternion const& rotation, std::vector<Vector2>& destinationArray);
		static Vector2 TransformNormal(Vector2 const& normal, Matrix const& matrix);
		static void TransformNormal(std::vector<Vector2> sourceArray, size_t sourceIndex, Matrix const& matrix,
			std::vector<Vector2>& destinationArray, size_t destinationIndex, size_t length);
		static void TransformNormal(std::vector<Vector2> sourceArray, Matrix const& matrix,	std::vector<Vector2>& destinationArray);

		void Ceiling();
		bool Equals(Vector2 const& other) const;
		void Floor();
		float Length() const;
		float LengthSquared() const;
		void Normalize();
		void Round();
		void Deconstruct(float& x, float& y) const;
	};
}

#endif