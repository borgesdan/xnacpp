#include <cmath>
#include "Vector2.hpp"
#include "Point.hpp"
#include "MathHelper.hpp"
#include "Matrix.hpp"
#include "Quaternion.hpp"

using std::vector;

//Constructors
namespace Xna {
	const Vector2 Vector2::Zero = Vector2(0);
	const Vector2 Vector2::One = Vector2(1);
	const Vector2 Vector2::UnitX = Vector2(1, 0);
	const Vector2 Vector2::UnitY = Vector2(0, 1);

	Vector2::Vector2() {}
	Vector2::Vector2(float x, float y) : X(X), Y(y) {}
	Vector2::Vector2(float value) : X(value), Y(value) {}
}

//Operators
namespace Xna {
	Vector2 Vector2::operator -() const {
		return Negate(*this);
	}

	Vector2 operator -(Vector2 const& value1, Vector2 const& value2) {
		return Vector2::Subtract(value1, value2);
	}

	Vector2 operator *(Vector2 const& value1, Vector2 const& value2) {
		return Vector2::Multiply(value1, value2);
	}

	Vector2 operator *(Vector2 const& value, float scaleFactor) {
		return Vector2::Multiply(value, scaleFactor);
	}

	Vector2 operator *(float scaleFactor, Vector2 const& value) {
		return Vector2::Multiply(value, scaleFactor);
	}

	Vector2 operator /(Vector2 const& value1, Vector2 const& value2) {
		return Vector2::Divide(value1, value2);
	}

	Vector2 operator /(Vector2 const& value1, float divider) {
		return Vector2::Multiply(value1, divider);
	}

	bool operator ==(Vector2 const& value1, Vector2 const& value2) {
		return value1.Equals(value2);
	}

	bool operator !=(Vector2 const& value1, Vector2 const& value2) {
		return !value1.Equals(value2);
	}
}

//Static
namespace Xna {
	Vector2 Vector2::Add(Vector2 const& value1, Vector2 const& value2) {
		return Vector2(
			value1.X + value2.X,
			value1.Y + value2.Y);
	}

	Vector2 Vector2::Barycentric(Vector2 const& value1, Vector2 const& value2,
		Vector2 const& value3, float amount1, float amount2) {
		return Vector2(
			MathHelper::Barycentric(value1.X, value2.X, value3.X, amount1, amount2),
			MathHelper::Barycentric(value1.Y, value2.Y, value3.Y, amount1, amount2));
	}

	Vector2 Vector2::CatmullRom(Vector2 const& value1, Vector2 const& value2,
		Vector2 const& value3, Vector2 const& value4, float amount) {
		return Vector2(
			MathHelper::CatmullRom(value1.X, value2.X, value3.X, value4.X, amount),
			MathHelper::CatmullRom(value1.Y, value2.Y, value3.Y, value4.Y, amount));
	}

	Vector2 Vector2::Ceiling(Vector2 const& value) {
		return Vector2(
			ceil(value.X),
			ceil(value.Y));
	}

	Vector2 Vector2::Clamp(Vector2 const& value1, Vector2 const& min, Vector2 const& max) {
		return Vector2(
			MathHelper::Clamp(value1.X, min.X, max.X),
			MathHelper::Clamp(value1.Y, min.Y, max.Y));
	}

	float Vector2::Distance(Vector2 const& value1, Vector2 const& value2) {
		return sqrt(DistanceSquared(value1, value2));
	}

	float Vector2::DistanceSquared(Vector2 const& value1, Vector2 const& value2) {
		auto v1 = value1.X - value2.X;
		auto v2 = value1.Y - value2.Y;
		return (v1 * v1) + (v2 * v2);
	}

	Vector2 Vector2::Divide(Vector2 const& value1, Vector2 const& value2) {
		return Vector2(
			value1.X / value2.X,
			value1.Y / value2.Y);
	}

	Vector2 Vector2::Divide(Vector2 const& value1, float divider) {
		return Vector2(
			value1.X / divider,
			value1.Y / divider);
	}

	float Vector2::Dot(Vector2 const& value1, Vector2 value2) {
		return (value1.X * value2.X) + (value1.Y * value2.Y);
	}

	Vector2 Vector2::Floor(Vector2 const& value) {
		return Vector2(
			floor(value.X),
			floor(value.Y));
	}

	Vector2 Vector2::Hermite(Vector2 const& value1, Vector2 const& tangent1,
		Vector2 const& value2, Vector2 const& tangent2, float amount) {
		return Vector2(
			MathHelper::Hermite(value1.X, tangent1.X, value2.X, tangent2.X, amount),
			MathHelper::Hermite(value1.Y, tangent1.Y, value2.Y, tangent2.Y, amount));
	}

	Vector2 Vector2::Lerp(Vector2 const& value1, Vector2 const& value2, float amount) {
		return Vector2(
			MathHelper::Lerp(value1.X, value2.X, amount),
			MathHelper::Lerp(value1.Y, value2.Y, amount));
	}

	Vector2 Vector2::LerpPrecise(Vector2 const& value1, Vector2 const& value2, float amount) {
		return Vector2(
			MathHelper::LerpPrecise(value1.X, value2.X, amount),
			MathHelper::LerpPrecise(value1.Y, value2.Y, amount));
	}

	Vector2 Vector2::Max(Vector2 const& value1, Vector2 const& value2) {
		return Vector2(
			value1.X > value2.X ? value1.X : value2.X,
			value1.Y > value2.Y ? value1.Y : value2.Y);
	}

	Vector2 Vector2::Min(Vector2 const& value1, Vector2 const& value2) {
		return Vector2(
			value1.X < value2.X ? value1.X : value2.X,
			value1.Y < value2.Y ? value1.Y : value2.Y);
	}

	Vector2 Vector2::Multiply(Vector2 const& value1, Vector2 const& value2) {
		return Vector2(
			value1.X * value2.X,
			value1.Y * value2.Y);
	}

	Vector2 Vector2::Multiply(Vector2 const& value1, float scaleFactor) {
		return Vector2(
			value1.X * scaleFactor,
			value1.Y * scaleFactor);
	}

	Vector2 Vector2::Negate(Vector2 const& value) {
		return Vector2(-value.X, -value.Y);
	}

	Vector2 Vector2::Normalize(Vector2 const& value) {
		auto val = 1.0F / sqrt((value.X * value.X) + (value.Y * value.Y));
		return Vector2(value.X * val, value.Y * val);
	}

	Vector2 Vector2::Reflect(Vector2 const& vector, Vector2 const& normal) {
		auto val = 2.0F * ((vector.X * normal.X) + (vector.Y * normal.Y));

		return Vector2(
			vector.X - (normal.X * val),
			vector.Y - (normal.Y * val)
		);
	}

	Vector2 Vector2::Round(Vector2 const& value) {
		return Vector2(
			round(value.X),
			round(value.Y));
	}

	Vector2 Vector2::SmoothStep(Vector2 const& value1, Vector2 const& value2, float amount) {
		return Vector2(
			MathHelper::SmoothStep(value1.X, value2.X, amount),
			MathHelper::SmoothStep(value1.Y, value2.Y, amount));
	}

	Vector2 Vector2::Subtract(Vector2 const& value1, Vector2 const& value2) {
		return Vector2(
			value1.X - value2.X,
			value1.Y - value2.Y);
	}

	Vector2 Vector2::Transform(Vector2 const& position, Matrix const& matrix) {
		return Vector2(
			(position.X * matrix.M11) + (position.Y * matrix.M21) + matrix.M41,
			(position.X * matrix.M12) + (position.Y * matrix.M22) + matrix.M42);
	}

	Vector2 Vector2::Transform(Vector2 const& value, Quaternion const& rotation) {
		auto rot1 = Vector3(rotation.X + rotation.X, rotation.Y + rotation.Y, rotation.Z + rotation.Z);
		auto rot2 = Vector3(rotation.X, rotation.X, rotation.W);
		auto rot3 = Vector3(1, rotation.Y, rotation.Z);
		auto rot4 = rot1 * rot2;
		auto rot5 = rot1 * rot3;

		//TODO: Verificar utilização de double no código original
		Vector2 v;
		v.X = value.X * (1.0F - rot5.Y - rot5.Z) + value.Y * (rot4.Y - rot4.Z);
		v.Y = value.X * (rot4.Y + rot4.Z) + value.Y * (1.0F - rot4.X - rot5.Z);

		return v;
	}

	void Vector2::Transform(vector<Vector2> const& sourceArray, size_t sourceIndex, Matrix const& matrix,
		vector<Vector2>& destinationArray, size_t destinationIndex, size_t length) {

		//TODO: Verificar exceções

		for (size_t x = 0; x < length; x++)
		{
			Vector2 position = sourceArray[sourceIndex + x];
			Vector2 destination = destinationArray[destinationIndex + x];

			destinationArray[destinationIndex + x] = Vector2(
				(position.X * matrix.M11) + (position.Y * matrix.M21) + matrix.M41,
				(position.X * matrix.M12) + (position.Y * matrix.M22) + matrix.M42);
		}
	}

	void Vector2::Transform(vector<Vector2> const& sourceArray, size_t sourceIndex, Quaternion const& rotation,
		vector<Vector2>& destinationArray, size_t destinationIndex, size_t length) {

		//TODO: Verificar exceções

		for (size_t x = 0; x < length; x++)
		{
			Vector2 position = sourceArray[sourceIndex + x];
			Vector2 destination = destinationArray[destinationIndex + x];

			destinationArray[destinationIndex + x] = Transform(position, rotation);
		}
	}

	void Vector2::Transform(std::vector<Vector2> const& sourceArray, Matrix const& matrix, std::vector<Vector2>& destinationArray) {
		Transform(sourceArray, 0, matrix, destinationArray, 0, sourceArray.size());
	}

	void Vector2::Transform(std::vector<Vector2> const& sourceArray, Quaternion const& rotation, std::vector<Vector2>& destinationArray) {
		Transform(sourceArray, 0, rotation, destinationArray, 0, sourceArray.size());
	}

	Vector2 Vector2::TransformNormal(Vector2 const& normal, Matrix const& matrix) {
		return Vector2(
			(normal.X * matrix.M11) + (normal.Y * matrix.M21),
			(normal.X * matrix.M12) + (normal.Y * matrix.M22));
	}

	void Vector2::TransformNormal(std::vector<Vector2> sourceArray, size_t sourceIndex, Matrix const& matrix,
		std::vector<Vector2>& destinationArray, size_t destinationIndex, size_t length) {
		//TODO: verificar exceções

		for (size_t i = 0; i < length; i++)
		{
			Vector2 normal = sourceArray[sourceIndex + i];

			destinationArray[destinationIndex + i] = Vector2(
				(normal.X * matrix.M11) + (normal.Y * matrix.M21),
				(normal.X * matrix.M12) + (normal.Y * matrix.M22));
		}
	}
	void Vector2::TransformNormal(std::vector<Vector2> sourceArray, Matrix const& matrix, std::vector<Vector2>& destinationArray) {
		TransformNormal(sourceArray, 0, matrix, destinationArray, 0, sourceArray.size());
	}

}

//Functions
namespace Xna {
	void Vector2::Ceiling() {
		auto value = Ceiling(*this);
		X = value.X;
		Y = value.Y;
	}

	bool Vector2::Equals(Vector2 const& other) const {
		return X == other.X && Y == other.Y;
	}

	void Vector2::Floor() {
		auto value = Floor(*this);
		X = value.X;
		Y = value.Y;
	}

	float Vector2::Length() const {
		return sqrt(LengthSquared());
	}

	float Vector2::LengthSquared() const {
		return (X * X) + (Y * Y);
	}

	void Vector2::Normalize() {
		auto value = Normalize(*this);
		X = value.X;
		Y = value.Y;
	}

	void Vector2::Round() {
		auto value = Round(*this);
		X = value.X;
		Y = value.Y;
	}

	void Vector2::Deconstruct(float& x, float& y) const {
		x = X;
		y = Y;
	}
}