#include <cmath>
#include "Vector3.hpp"
#include "MathHelper.hpp"

using std::ceil;

namespace Xna {
	const Vector3 Vector3::Zero = Vector3();
	const Vector3 Vector3::One = Vector3(1);
	const Vector3 Vector3::UnitX = Vector3(1,0,0);
	const Vector3 Vector3::UnitY = Vector3(0, 1, 0);
	const Vector3 Vector3::UnitZ = Vector3(0, 0, 1);
	const Vector3 Vector3::Up = UnitY;
	const Vector3 Vector3::Down = Vector3(0, -1, 0);
	const Vector3 Vector3::Right = UnitX;
	const Vector3 Vector3::Left = Vector3(-1, 0, 0);
	const Vector3 Vector3::Forward = Vector3(0, 0, -1);
	const Vector3 Vector3::Backward = UnitZ;

	Vector3::Vector3() {}
	Vector3::Vector3(float value) :
		X(value), Y(value), Z(value) {}
	Vector3::Vector3(float x, float y, float z):
		X(x), Y(y), Z(z) {}
	Vector3::Vector3(Vector2 value, float z):
		X(value.X), Y(value.Y), Z(z) {}

	Vector3 Vector3::operator -(Vector3 const& value) {
		return Negate(value);
	}

	Vector3 operator -(Vector3 const& value1, Vector3 const& value2) {
		return Vector3::Subtract(value1, value2);
	}

	Vector3 operator *(Vector3 const& value1, Vector3 const& value2) {
		return Vector3::Multiply(value1, value2);
	}

	Vector3 operator *(Vector3 const& value, float scaleFactor) {
		return Vector3::Multiply(value, scaleFactor);
	}

	Vector3 operator *(float scaleFactor, Vector3 const& value) {
		return Vector3::Multiply(value, scaleFactor);
	}

	Vector3 operator /(Vector3 const& value1, Vector3 const& value2) {
		return Vector3::Divide(value1, value2);
	}

	Vector3 operator /(Vector3 const& value1, float divider) {
		return Vector3::Multiply(value1, divider);
	}

	bool operator ==(Vector3 const& value1, Vector3 const& value2) {
		return value1.Equals(value2);
	}

	bool operator !=(Vector3 const& value1, Vector3 const& value2) {
		return !value1.Equals(value2);
	}

	Vector3 Vector3::Add(Vector3 const& value1, Vector3 const& value2) {
		return Vector3(
			value1.X + value2.X,
			value1.Y + value2.Y,
			value1.Z + value2.Z);
	}

	Vector3 Vector3::Barycentric(Vector3 const& value1, Vector3 const& value2, Vector3 const& value3, float amount1, float amount2) {
		return Vector3(
			MathHelper::Barycentric(value1.X, value2.X, value3.X, amount1, amount2),
			MathHelper::Barycentric(value1.Y, value2.Y, value3.Y, amount1, amount2),
			MathHelper::Barycentric(value1.Z, value2.Z, value3.Z, amount1, amount2));
	}

	Vector3 Vector3::CatmullRom(Vector3 const& value1, Vector3 const& value2, Vector3 const& value3, Vector3 const& value4, float amount) {
		return Vector3(
			MathHelper::CatmullRom(value1.X, value2.X, value3.X, value4.X, amount),
			MathHelper::CatmullRom(value1.Y, value2.Y, value3.Y, value4.Y, amount),
			MathHelper::CatmullRom(value1.Z, value2.Z, value3.Z, value4.Z, amount));
	}

	Vector3 Vector3::Ceiling(Vector3 const& value) {
		Vector3 result;
		result.X = ceil(value.X);
		result.Y = ceil(value.Y);
		result.Z = ceil(value.Z);

		return result;
	}

	Vector3 Vector3::Clamp(Vector3 const& value1, Vector3 const& min, Vector3 const& max) {
		return Vector3(
			MathHelper::Clamp(value1.X, min.X, max.X),
			MathHelper::Clamp(value1.Y, min.Y, max.Y),
			MathHelper::Clamp(value1.Z, min.Z, max.Z));
	}

	Vector3 Vector3::Cross(Vector3 const& vector1, Vector3 const& vector2) {
		auto x = vector1.Y * vector2.Z - vector2.Y * vector1.Z;
		auto y = -(vector1.X * vector2.Z - vector2.X * vector1.Z);
		auto z = vector1.X * vector2.Y - vector2.X * vector1.Y;

		return Vector3(x, y, z);
	}

	float Vector3::Distance(Vector3 const& value1, Vector3 const& value2) {
		return sqrtf(DistanceSquared(value1, value2));
	}

	float Vector3::DistanceSquared(Vector3 const& value1, Vector3 const& value2) {
		return  
			(value1.X - value2.X) * (value1.X - value2.X) +
			(value1.Y - value2.Y) * (value1.Y - value2.Y) +
			(value1.Z - value2.Z) * (value1.Z - value2.Z);
	}

	Vector3 Vector3::Divide(Vector3 const& value1, Vector3 const& value2) {
		return Vector3(
			value1.X / value2.X,
			value1.Y / value2.Y,
			value1.Z / value2.Z
		);
	}

	Vector3 Vector3::Divide(Vector3 const& value1, float divider) {
		return Vector3(
			value1.X / divider,
			value1.Y / divider,
			value1.Z / divider
		);
	}

	float Vector3::Dot(Vector3 const& value1, Vector3 const& value2) {
		return value1.X * value2.X + value1.Y * value2.Y + value1.Z * value2.Z;
	}

	Vector3 Vector3::Floor(Vector3 const& value) {
		
		auto x = floor(value.X);
		auto y = floor(value.Y);
		auto z = floor(value.Z);
		return Vector3(x, y, z);
	}

	Vector3 Vector3::Hermite(Vector3 const& value1, Vector3 const& tangent1, Vector3 const& value2, Vector3 const& tangent2, float amount) {
		return Vector3(
			MathHelper::Hermite(value1.X, tangent1.X, value2.X, tangent2.X, amount),
			MathHelper::Hermite(value1.Y, tangent1.Y, value2.Y, tangent2.Y, amount),
			MathHelper::Hermite(value1.Z, tangent1.Z, value2.Z, tangent2.Z, amount));
	}

	Vector3 Vector3::Lerp(Vector3 const& value1, Vector3 const& value2, float amount) {
		return Vector3(
			MathHelper::Lerp(value1.X, value2.X, amount),
			MathHelper::Lerp(value1.Y, value2.Y, amount),
			MathHelper::Lerp(value1.Z, value2.Z, amount));
	}

	Vector3 Vector3::LerpPrecise(Vector3 const& value1, Vector3 const& value2, float amount) {
		return Vector3(
			MathHelper::LerpPrecise(value1.X, value2.X, amount),
			MathHelper::LerpPrecise(value1.Y, value2.Y, amount),
			MathHelper::LerpPrecise(value1.Z, value2.Z, amount));
	}

	Vector3 Vector3::Max(Vector3 const& value1, Vector3 const& value2) {
		return Vector3(
			MathHelper::Max(value1.X, value2.X),
			MathHelper::Max(value1.Y, value2.Y),
			MathHelper::Max(value1.Z, value2.Z));
	}

	Vector3 Vector3::Min(Vector3 const& value1, Vector3 const& value2) {
		return Vector3(
			MathHelper::Min(value1.X, value2.X),
			MathHelper::Min(value1.Y, value2.Y),
			MathHelper::Min(value1.Z, value2.Z));
	}

	Vector3 Vector3::Multiply(Vector3 const& value1, Vector3 const& value2) {		
		auto x = value1.X * value2.X;
		auto y = value1.Y * value2.Y;
		auto z = value1.Z * value2.Z;
		return Vector3(x, y, z);
	}

	Vector3 Vector3::Multiply(Vector3 const& value1, float scaleFactor) {
		auto x = value1.X * scaleFactor;
		auto y = value1.Y * scaleFactor;
		auto z = value1.Z * scaleFactor;
		return Vector3(x, y, z);
	}

	Vector3 Vector3::Negate(Vector3 const& value) {
		auto vector3 = Vector3(-value.X, -value.Y, -value.Z);
		return vector3;
	}

	Vector3 Vector3::Normalize(Vector3 const& value) {
		float factor = sqrtf((value.X * value.X) + (value.Y * value.Y) + (value.Z * value.Z));
		factor = 1.0 / factor;
		return Vector3(value.X * factor, value.Y * factor, value.Z * factor);
	}

	Vector3 Vector3::Reflect(Vector3 const& vector, Vector3 const& normal) {
		Vector3 reflectedVector;
		float dotProduct = ((vector.X * normal.X) + (vector.Y * normal.Y)) + (vector.Z * normal.Z);
		reflectedVector.X = vector.X - (2.0f * normal.X) * dotProduct;
		reflectedVector.Y = vector.Y - (2.0f * normal.Y) * dotProduct;
		reflectedVector.Z = vector.Z - (2.0f * normal.Z) * dotProduct;

		return reflectedVector;
	}
	Vector3 Vector3::Round(Vector3 const& value) {
		auto x = round(value.X);
		auto y = round(value.Y);
		auto z = round(value.Z);
		return Vector3(x, y, z);
	}

	Vector3 Vector3::SmoothStep(Vector3 const& value1, Vector3 const& value2, float amount) {
		return Vector3(
			MathHelper::SmoothStep(value1.X, value2.X, amount),
			MathHelper::SmoothStep(value1.Y, value2.Y, amount),
			MathHelper::SmoothStep(value1.Z, value2.Z, amount));
	}

	Vector3 Vector3::Subtract(Vector3 const& value1, Vector3 const& value2) {
		auto x = value1.X - value2.X;
		auto y = value1.Y - value2.Y;
		auto z = value1.Z - value2.Z;
		return Vector3(x, y, z);
	}

	void Vector3::Ceiling() {
		auto value = Ceiling(*this);
		X = value.X;
		Y = value.Y;
		Z = value.Z;
	}

	bool Vector3::Equals(Vector3 const& other) const {
		return  
			X == other.X &&
			Y == other.Y &&
			Z == other.Z;
	}

	void Vector3::Floor() {
		auto value = Floor(*this);
		X = value.X;
		Y = value.Y;
		Z = value.Z;
	}

	float Vector3::Length() const {
		return sqrtf(LengthSquared());
	}

	float Vector3::LengthSquared() const {
		return (X * X) + (Y * Y) + (Z * Z);
	}

	void Vector3::Normalize() {
		auto value = Normalize(*this);
		X = value.X;
		Y = value.Y;
		Z = value.Z;
	}
	
	void Vector3::Round() {
		auto value = Round(*this);
		X = value.X;
		Y = value.Y;
		Z = value.Z;
	}

	void Vector3::Deconstruct(float& x, float& y, float& z) const {
		x = X;
		y = Y;
		z = Z;
	}
}