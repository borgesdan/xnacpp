#ifndef _VECTOR3_HPP_
#define _VECTOR3_HPP_

#include <vector>

namespace Xna {

	struct Vector2;
	struct Matrix;
	struct Quaternion;

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

		Vector3 operator -() const;
		friend Vector3 operator -(Vector3 const& value1, Vector3 const& value2);
		friend Vector3 operator *(Vector3 const& value1, Vector3 const& value2);
		friend Vector3 operator *(Vector3 const& value, float scaleFactor);
		friend Vector3 operator *(float scaleFactor, Vector3 const& value);
		friend Vector3 operator /(Vector3 const& value1, Vector3 const& value2);
		friend Vector3 operator /(Vector3 const& value1, float divider);
		friend bool operator ==(Vector3 const& value1, Vector3 const& value2);
		friend bool operator !=(Vector3 const& value1, Vector3 const& value2);

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
		static Vector3 Floor(Vector3 const& value);
		static Vector3 Hermite(Vector3 const& value1, Vector3 const& tangent1, Vector3 const& value2, Vector3 const& tangent2, float amount);
		static Vector3 Lerp(Vector3 const& value1, Vector3 const& value2, float amount);
		static Vector3 LerpPrecise(Vector3 const& value1, Vector3 const& value2, float amount);
		static Vector3 Max(Vector3 const& value1, Vector3 const& value2);
		static Vector3 Min(Vector3 const& value1, Vector3 const& value2);
		static Vector3 Multiply(Vector3 const& value1, Vector3 const& value2);
		static Vector3 Multiply(Vector3 const& value1, float scaleFactor);
		static Vector3 Negate(Vector3 const& value);
		static Vector3 Normalize(Vector3 const& value);
		static Vector3 Reflect(Vector3 const& vector, Vector3 const& normal);
		static Vector3 Round(Vector3 const& value);
		static Vector3 SmoothStep(Vector3 const& value1, Vector3 const& value2, float amount);
		static Vector3 Subtract(Vector3 const& value1, Vector3 const& value2);

		static Vector3 Transform(Vector3 const& position, Matrix const& matrix);
		static Vector3 Transform(Vector3 const& value, Quaternion const& rotation);
		static void Transform(std::vector<Vector3> const& sourceArray, size_t sourceIndex, Matrix const& matrix,
			std::vector<Vector3>& destinationArray, size_t destinationIndex, size_t length);
		static void Transform(std::vector<Vector3> const& sourceArray, size_t sourceIndex, Quaternion const& rotation,
			std::vector<Vector3>& destinationArray, size_t destinationIndex, size_t length);
		static void Transform(std::vector<Vector3> const& sourceArray, Matrix const& matrix, std::vector<Vector3>& destinationArray);
		static void Transform(std::vector<Vector3> const& sourceArray, Quaternion const& rotation, std::vector<Vector3>& destinationArray);
		static Vector3 TransformNormal(Vector3 const& normal, Matrix const& matrix);
		static void TransformNormal(std::vector<Vector3> sourceArray, size_t sourceIndex, Matrix const& matrix,
			std::vector<Vector3>& destinationArray, size_t destinationIndex, size_t length);
		static void TransformNormal(std::vector<Vector3> sourceArray, Matrix const& matrix, std::vector<Vector3>& destinationArray);


		void Ceiling();
		bool Equals(Vector3 const& other) const;
		void Floor();
		float Length() const;
		float LengthSquared() const;
		void Normalize();
		void Round();
		void Deconstruct(float& x, float& y, float& z) const;
	};
}

#endif