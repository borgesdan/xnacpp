#include <cmath>
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "MathHelper.hpp"
#include "Matrix.hpp"
#include "Quaternion.hpp"

using std::ceil;

namespace Xna {
	const Vector3 Vector3::Zero = Vector3(0);
	const Vector3 Vector3::One = Vector3(1);
	const Vector3 Vector3::UnitX = Vector3(1, 0, 0);
	const Vector3 Vector3::UnitY = Vector3(0, 1, 0);
	const Vector3 Vector3::UnitZ = Vector3(0, 0, 1);
	const Vector3 Vector3::Up = UnitY;
	const Vector3 Vector3::Down = -UnitY;
	const Vector3 Vector3::Right = UnitX;
	const Vector3 Vector3::Left = -UnitX;
	const Vector3 Vector3::Forward = -UnitZ;
	const Vector3 Vector3::Backward = UnitZ;

	Vector3::Vector3() {}
	Vector3::Vector3(float value) :
		X(value), Y(value), Z(value) {}
	Vector3::Vector3(float x, float y, float z) :
		X(x), Y(y), Z(z) {}
	Vector3::Vector3(Vector2 value, float z) :
		X(value.X), Y(value.Y), Z(z) {}
}

namespace Xna {
	Vector3 Vector3::operator -() const {
		return Negate(*this);
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
}

namespace Xna {
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
		return Vector3(
			ceil(value.X),
			ceil(value.Y),
			ceil(value.Z));
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
		return sqrt(DistanceSquared(value1, value2));
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
		return Vector3(
			floor(value.X),
			floor(value.Y),
			floor(value.Z)
		);
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
		return Vector3(
			value1.X * value2.X,
			value1.Y * value2.Y,
			value1.Z * value2.Z);
	}

	Vector3 Vector3::Multiply(Vector3 const& value1, float scaleFactor) {
		return Vector3(
			value1.X * scaleFactor,
			value1.Y * scaleFactor,
			value1.Z * scaleFactor);
	}

	Vector3 Vector3::Negate(Vector3 const& value) {
		return Vector3(-value.X, -value.Y, -value.Z);
	}

	Vector3 Vector3::Normalize(Vector3 const& value) {
		float factor = sqrt((value.X * value.X) + (value.Y * value.Y) + (value.Z * value.Z));
		factor = 1.0F / factor;
		return Vector3(value.X * factor, value.Y * factor, value.Z * factor);
	}

	Vector3 Vector3::Reflect(Vector3 const& vector, Vector3 const& normal) {
		float dotProduct = ((vector.X * normal.X) + (vector.Y * normal.Y)) + (vector.Z * normal.Z);
		auto x = vector.X - (2.0f * normal.X) * dotProduct;
		auto y = vector.Y - (2.0f * normal.Y) * dotProduct;
		auto z = vector.Z - (2.0f * normal.Z) * dotProduct;

		return Vector3(x, y, z);
	}

	Vector3 Vector3::Round(Vector3 const& value) {
		return Vector3(
			round(value.X),
			round(value.Y),
			round(value.Z));
	}

	Vector3 Vector3::SmoothStep(Vector3 const& value1, Vector3 const& value2, float amount) {
		return Vector3(
			MathHelper::SmoothStep(value1.X, value2.X, amount),
			MathHelper::SmoothStep(value1.Y, value2.Y, amount),
			MathHelper::SmoothStep(value1.Z, value2.Z, amount));
	}

	Vector3 Vector3::Subtract(Vector3 const& value1, Vector3 const& value2) {
		return Vector3(
			value1.X - value2.X,
			value1.Y - value2.Y,
			value1.Z - value2.Z);
	}

	Vector3 Vector3::Transform(Vector3 const& position, Matrix const& matrix) {
		auto x = (position.X * matrix.M11) + (position.Y * matrix.M21) + (position.Z * matrix.M31) + matrix.M41;
		auto y = (position.X * matrix.M12) + (position.Y * matrix.M22) + (position.Z * matrix.M32) + matrix.M42;
		auto z = (position.X * matrix.M13) + (position.Y * matrix.M23) + (position.Z * matrix.M33) + matrix.M43;

		return Vector3(x, y, z);
	}

	Vector3 Vector3::Transform(Vector3 const& value, Quaternion const& rotation) {
		auto x = 2 * (rotation.Y * value.Z - rotation.Z * value.Y);
		auto y = 2 * (rotation.Z * value.X - rotation.X * value.Z);
		auto z = 2 * (rotation.X * value.Y - rotation.Y * value.X);

		return Vector3(
			value.X + x * rotation.W + (rotation.Y * z - rotation.Z * y),
			value.Y + y * rotation.W + (rotation.Z * x - rotation.X * z),
			value.Z + z * rotation.W + (rotation.X * y - rotation.Y * x)
		);
	}

	void Vector3::Transform(std::vector<Vector3> const& sourceArray, size_t sourceIndex, Matrix const& matrix,
		std::vector<Vector3>& destinationArray, size_t destinationIndex, size_t length) {

		//TODO: verificar exceções

		for (size_t i = 0; i < length; i++)
		{
			Vector3 position = sourceArray[sourceIndex + i];

			destinationArray[destinationIndex + i] = Vector3(
				(position.X * matrix.M11) + (position.Y * matrix.M21) + (position.Z * matrix.M31) + matrix.M41,
				(position.X * matrix.M12) + (position.Y * matrix.M22) + (position.Z * matrix.M32) + matrix.M42,
				(position.X * matrix.M13) + (position.Y * matrix.M23) + (position.Z * matrix.M33) + matrix.M43);
		}
	}

	void Vector3::Transform(std::vector<Vector3> const& sourceArray, size_t sourceIndex, Quaternion const& rotation,
		std::vector<Vector3>& destinationArray, size_t destinationIndex, size_t length) {

		//TODO: verificar exceções

		for (size_t i = 0; i < length; i++) {
			Vector3 position = sourceArray[sourceIndex + i];

			auto x = 2 * (rotation.Y * position.Z - rotation.Z * position.Y);
			auto y = 2 * (rotation.Z * position.X - rotation.X * position.Z);
			auto z = 2 * (rotation.X * position.Y - rotation.Y * position.X);

			destinationArray[destinationIndex + i] = Vector3(
				position.X + x * rotation.W + (rotation.Y * z - rotation.Z * y),
				position.Y + y * rotation.W + (rotation.Z * x - rotation.X * z),
				position.Z + z * rotation.W + (rotation.X * y - rotation.Y * x));
		}
	}

	void Vector3::Transform(std::vector<Vector3> const& sourceArray, Matrix const& matrix, std::vector<Vector3>& destinationArray) {
		Transform(sourceArray, 0, matrix, destinationArray, 0, destinationArray.size());
	}

	void Vector3::Transform(std::vector<Vector3> const& sourceArray, Quaternion const& rotation, std::vector<Vector3>& destinationArray) {
		Transform(sourceArray, 0, rotation, destinationArray, 0, destinationArray.size());
	}

	Vector3 Vector3::TransformNormal(Vector3 const& normal, Matrix const& matrix) {
		auto x = (normal.X * matrix.M11) + (normal.Y * matrix.M21) + (normal.Z * matrix.M31);
		auto y = (normal.X * matrix.M12) + (normal.Y * matrix.M22) + (normal.Z * matrix.M32);
		auto z = (normal.X * matrix.M13) + (normal.Y * matrix.M23) + (normal.Z * matrix.M33);

		return Vector3(x, y, z);
	}

	void Vector3::TransformNormal(std::vector<Vector3> sourceArray, size_t sourceIndex, Matrix const& matrix,
		std::vector<Vector3>& destinationArray, size_t destinationIndex, size_t length) {
		//TODO: verificar exceções

		for (size_t x = 0; x < length; x++)
		{
			Vector3 normal = sourceArray[sourceIndex + x];

			destinationArray[destinationIndex + x] = Vector3(
				(normal.X * matrix.M11) + (normal.Y * matrix.M21) + (normal.Z * matrix.M31),
				(normal.X * matrix.M12) + (normal.Y * matrix.M22) + (normal.Z * matrix.M32),
				(normal.X * matrix.M13) + (normal.Y * matrix.M23) + (normal.Z * matrix.M33));
		}
	}

	void Vector3::TransformNormal(std::vector<Vector3> sourceArray, Matrix const& matrix, std::vector<Vector3>& destinationArray) {
		TransformNormal(sourceArray, 0, matrix, destinationArray, 0, destinationArray.size());
	}
}

namespace Xna {
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
		return sqrt(LengthSquared());
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