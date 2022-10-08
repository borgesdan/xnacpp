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
}