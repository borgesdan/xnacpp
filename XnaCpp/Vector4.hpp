#ifndef _VECTOR4_HPP_
#define _VECTOR4_HPP_

#include <vector>

namespace Xna {

	struct Vector2;
	struct Vector3;
	struct Quaternion;
	struct Matrix;

	struct Vector4 {
		float X{ 0 };
		float Y{ 0 };
		float Z{ 0 };
		float W{ 0 };

		static const Vector4 Zero;
		static const Vector4 One;
		static const Vector4 UnitX;
		static const Vector4 UnitY;
		static const Vector4 UnitZ;
		static const Vector4 UnitW;

		Vector4();
		Vector4(float value);
		Vector4(float x, float y, float z, float w);
		Vector4(Vector3 value, float w);
		Vector4(Vector2 value, float z, float w);

		Vector4 operator -() const;
		friend Vector4 operator -(Vector4 const& value1, Vector4 const& value2);
		friend Vector4 operator *(Vector4 const& value1, Vector4 const& value2);
		friend Vector4 operator *(Vector4 const& value, float scaleFactor);
		friend Vector4 operator *(float scaleFactor, Vector4 const& value);
		friend Vector4 operator /(Vector4 const& value1, Vector4 const& value2);
		friend Vector4 operator /(Vector4 const& value1, float divider);
		friend bool operator ==(Vector4 const& value1, Vector4 const& value2);
		friend bool operator !=(Vector4 const& value1, Vector4 const& value2);

		static Vector4 Add(Vector4 const& value1, Vector4 const& value2);
		static Vector4 Barycentric(Vector4 const& value1, Vector4 const& value2, Vector4 const& value3, float amount1, float amount2);
		static Vector4 CatmullRom(Vector4 const& value1, Vector4 const& value2, Vector4 const& value3, Vector4 const& value4, float amount);
		static Vector4 Ceiling(Vector4 const& value);
		static Vector4 Clamp(Vector4 const& value1, Vector4 const& min, Vector4 const& max);
		static float Distance(Vector4 const& value1, Vector4 const& value2);
		static float DistanceSquared(Vector4 const& value1, Vector4 const& value2);;
		static Vector4 Divide(Vector4 const& value1, Vector4 const& value2);
		static Vector4 Divide(Vector4 const& value1, float divider);
		static float Dot(Vector4 const& value1, Vector4 const& value2);
		static Vector4 Floor(Vector4 const& value);
		static Vector4 Hermite(Vector4 const& value1, Vector4 tangent1, Vector4 const& value2, Vector4 tangent2, float amount);
		static Vector4 Lerp(Vector4 const& value1, Vector4 const& value2, float amount);
		static Vector4 LerpPrecise(Vector4 const& value1, Vector4 const& value2, float amount);
		static Vector4 Max(Vector4 const& value1, Vector4 const& value2);
		static Vector4 Min(Vector4 const& value1, Vector4 const& value2);
		static Vector4 Multiply(Vector4 const& value1, Vector4 const& value2);
		static Vector4 Multiply(Vector4 const& value1, float scaleFactor);
		static Vector4 Negate(Vector4 const& value);
		static Vector4 Normalize(Vector4 const& value);
		static Vector4 Round(Vector4 const& value);
		static Vector4 SmoothStep(Vector4 const& value1, Vector4 const& value2, float amount);
		static Vector4 Subtract(Vector4 const& value1, Vector4 const& value2);

		static Vector4 Transform(Vector2 const& value, Matrix const& matrix);
		//TODO: Não implementado - static Vector4 Transform(Vector2 const& value, Quaternion const& rotation);
		static Vector4 Transform(Vector3 const& value, Matrix const& matrix);
		//TODO: Não implementado - static Vector4 Transform(Vector3 const& value, Quaternion const& rotation);
		static Vector4 Transform(Vector4 const& value, Matrix const& matrix);
		//TODO: Não implementado - static Vector4 Transform(Vector4 const& value, Quaternion const& rotation);
		static void Transform(std::vector<Vector4> const& sourceArray, size_t sourceIndex, Matrix const& matrix,
			std::vector<Vector4>& destinationArray, size_t destinationIndex, size_t length);
		//TODO: Não implementado - static void Transform(std::vector<Vector4> const& sourceArray, size_t sourceIndex, Quaternion const& rotation, std::vector<Vector4>& destinationArray, size_t destinationIndex, size_t length);
		static void Transform(std::vector<Vector4> const& sourceArray, Matrix const& matrix, std::vector<Vector4>& destinationArray);
		//TODO: Não impleentado - static void Transform(std::vector<Vector4> const& sourceArray, Quaternion const& rotation, std::vector<Vector4>& destinationArray);

		void Ceiling();
		bool Equals(Vector4 const& other) const;
		void Floor();
		float Length() const;
		float LengthSquared() const;
		void Normalize();
		void Round();
		void Deconstruct(float& x, float& y, float& z, float& w) const;
	};
}

#endif