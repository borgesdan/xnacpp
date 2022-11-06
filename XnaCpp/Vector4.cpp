#include <cmath>
#include "Vector4.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "MathHelper.hpp"
#include "Matrix.hpp"
#include "Quaternion.hpp"

namespace Xna {
	const Vector4 Vector4::Zero = Vector4();
	const Vector4 Vector4::One = Vector4(1);
	const Vector4 Vector4::UnitX = Vector4(1, 0, 0, 0);
	const Vector4 Vector4::UnitY = Vector4(0, 1, 0, 0);
	const Vector4 Vector4::UnitZ = Vector4(0, 0, 1, 0);
	const Vector4 Vector4::UnitW = Vector4(0, 0, 0, 1);

	Vector4::Vector4() {}

	Vector4::Vector4(float value) :
		X(value), Y(value), Z(value), W(value) {}

	Vector4::Vector4(float x, float y, float z, float w) :
		X(x), Y(y), Z(z), W(w) {}

	Vector4::Vector4(Vector3 value, float w) :
		X(value.X), Y(value.Y), Z(value.Z), W(w) {}

	Vector4::Vector4(Vector2 value, float z, float w) :
		X(value.X), Y(value.Y), Z(z), W(w) {}

	Vector4 Vector4::operator -() const {
		return Negate(*this);
	}	
}

namespace Xna {
	Vector4 operator -(Vector4 const& value1, Vector4 const& value2) {
		return Vector4::Subtract(value1, value2);
	}

	Vector4 operator *(Vector4 const& value1, Vector4 const& value2) {
		return Vector4::Multiply(value1, value2);
	}

	Vector4 operator *(Vector4 const& value, float scaleFactor) {
		return Vector4::Multiply(value, scaleFactor);
	}

	Vector4 operator *(float scaleFactor, Vector4 const& value) {
		return Vector4::Multiply(value, scaleFactor);
	}

	Vector4 operator /(Vector4 const& value1, Vector4 const& value2) {
		return Vector4::Divide(value1, value2);
	}

	Vector4 operator /(Vector4 const& value1, float divider) {
		return Vector4::Multiply(value1, divider);
	}

	bool operator ==(Vector4 const& value1, Vector4 const& value2) {
		return value1.Equals(value2);
	}

	bool operator !=(Vector4 const& value1, Vector4 const& value2) {
		return !value1.Equals(value2);
	}
}

namespace Xna {
	Vector4 Vector4::Add(Vector4 const& value1, Vector4 const& value2) {
		return Vector4(
			value1.X + value2.X,
			value1.Y + value2.Y,
			value1.Z + value2.Z,
			value1.W + value2.W);
	}

	Vector4 Vector4::Barycentric(Vector4 const& value1, Vector4 const& value2, Vector4 const& value3, float amount1, float amount2) {
		return Vector4(
			MathHelper::Barycentric(value1.X, value2.X, value3.X, amount1, amount2),
			MathHelper::Barycentric(value1.Y, value2.Y, value3.Y, amount1, amount2),
			MathHelper::Barycentric(value1.Z, value2.Z, value3.Z, amount1, amount2),
			MathHelper::Barycentric(value1.W, value2.W, value3.W, amount1, amount2));
	}

	Vector4 Vector4::CatmullRom(Vector4 const& value1, Vector4 const& value2, Vector4 const& value3, Vector4 const& value4, float amount) {
		return Vector4(
			MathHelper::CatmullRom(value1.X, value2.X, value3.X, value4.X, amount),
			MathHelper::CatmullRom(value1.Y, value2.Y, value3.Y, value4.Y, amount),
			MathHelper::CatmullRom(value1.Z, value2.Z, value3.Z, value4.Z, amount),
			MathHelper::CatmullRom(value1.W, value2.W, value3.W, value4.W, amount));
	}

	Vector4 Vector4::Ceiling(Vector4 const& value) {
		return Vector4(
			ceil(value.X),
			ceil(value.Y),
			ceil(value.Z),
			ceil(value.W));
	}

	Vector4 Vector4::Clamp(Vector4 const& value1, Vector4 const& min, Vector4 const& max) {
		return Vector4(
			MathHelper::Clamp(value1.X, min.X, max.X),
			MathHelper::Clamp(value1.Y, min.Y, max.Y),
			MathHelper::Clamp(value1.Z, min.Z, max.Z),
			MathHelper::Clamp(value1.W, min.W, max.W));
	}

	float Vector4::Distance(Vector4 const& value1, Vector4 const& value2) {
		return sqrt(DistanceSquared(value1, value2));
	}

	float Vector4::DistanceSquared(Vector4 const& value1, Vector4 const& value2) {
		return
			(value1.W - value2.W) * (value1.W - value2.W) +
			(value1.X - value2.X) * (value1.X - value2.X) +
			(value1.Y - value2.Y) * (value1.Y - value2.Y) +
			(value1.Z - value2.Z) * (value1.Z - value2.Z);
	}

	Vector4 Vector4::Divide(Vector4 const& value1, Vector4 const& value2) {
		return Vector4(
			value1.W / value2.W,
			value1.X / value2.X,
			value1.Y / value2.Y,
			value1.Z / value2.Z);
	}

	Vector4 Vector4::Divide(Vector4 const& value1, float divider) {
		return Vector4(
			value1.W / divider,
			value1.X / divider,
			value1.Y / divider,
			value1.Z / divider);
	}

	float Vector4::Dot(Vector4 const& value1, Vector4 const& value2) {
		return
			value1.X * value2.X +
			value1.Y * value2.Y +
			value1.Z * value2.Z +
			value1.W * value2.W;
	}

	Vector4 Vector4::Floor(Vector4 const& value) {
		return Vector4(
			floor(value.X),
			floor(value.Y),
			floor(value.Z),
			floor(value.W)
		);
	}

	Vector4 Vector4::Hermite(Vector4 const& value1, Vector4 tangent1, Vector4 const& value2, Vector4 tangent2, float amount) {
		return Vector4(
			MathHelper::Hermite(value1.X, tangent1.X, value2.X, tangent2.X, amount),
			MathHelper::Hermite(value1.Y, tangent1.Y, value2.Y, tangent2.Y, amount),
			MathHelper::Hermite(value1.Z, tangent1.Z, value2.Z, tangent2.Z, amount),
			MathHelper::Hermite(value1.W, tangent1.W, value2.W, tangent2.W, amount));
	}

	Vector4 Vector4::Lerp(Vector4 const& value1, Vector4 const& value2, float amount) {
		return Vector4(
			MathHelper::Lerp(value1.X, value2.X, amount),
			MathHelper::Lerp(value1.Y, value2.Y, amount),
			MathHelper::Lerp(value1.Z, value2.Z, amount),
			MathHelper::Lerp(value1.W, value2.W, amount));
	}

	Vector4 Vector4::LerpPrecise(Vector4 const& value1, Vector4 const& value2, float amount) {
		return Vector4(
			MathHelper::LerpPrecise(value1.X, value2.X, amount),
			MathHelper::LerpPrecise(value1.Y, value2.Y, amount),
			MathHelper::LerpPrecise(value1.Z, value2.Z, amount),
			MathHelper::LerpPrecise(value1.W, value2.W, amount));
	}

	Vector4 Vector4::Max(Vector4 const& value1, Vector4 const& value2) {
		return Vector4(
			MathHelper::Max(value1.X, value2.X),
			MathHelper::Max(value1.Y, value2.Y),
			MathHelper::Max(value1.Z, value2.Z),
			MathHelper::Max(value1.W, value2.W));
	}

	Vector4 Vector4::Min(Vector4 const& value1, Vector4 const& value2) {
		return Vector4(
			MathHelper::Min(value1.X, value2.X),
			MathHelper::Min(value1.Y, value2.Y),
			MathHelper::Min(value1.Z, value2.Z),
			MathHelper::Min(value1.W, value2.W));
	}

	Vector4 Vector4::Multiply(Vector4 const& value1, Vector4 const& value2) {
		return Vector4(
			value1.W * value2.W,
			value1.X * value2.X,
			value1.Y * value2.Y,
			value1.Z * value2.Z
		);
	}

	Vector4 Vector4::Multiply(Vector4 const& value1, float scaleFactor) {
		return Vector4(
			value1.W * scaleFactor,
			value1.X * scaleFactor,
			value1.Y * scaleFactor,
			value1.Z * scaleFactor
		);
	}

	Vector4 Vector4::Negate(Vector4 const& value) {
		return Vector4(-value.X, -value.Y, -value.Z, -value.W);
	}

	Vector4 Vector4::Normalize(Vector4 const& value) {
		auto factor = sqrt(
			(value.X * value.X) +
			(value.Y * value.Y) +
			(value.Z * value.Z) +
			(value.W * value.W));

		factor = 1.0F / factor;

		return Vector4(value.X * factor, value.Y * factor, value.Z * factor, value.W * factor);
	}

	Vector4 Vector4::Round(Vector4 const& value) {
		return Vector4(
			round(value.X),
			round(value.Y),
			round(value.Z),
			round(value.W)
		);
	}

	Vector4 Vector4::SmoothStep(Vector4 const& value1, Vector4 const& value2, float amount) {
		return Vector4(
			MathHelper::SmoothStep(value1.X, value2.X, amount),
			MathHelper::SmoothStep(value1.Y, value2.Y, amount),
			MathHelper::SmoothStep(value1.Z, value2.Z, amount),
			MathHelper::SmoothStep(value1.W, value2.W, amount));
	}

	Vector4 Vector4::Subtract(Vector4 const& value1, Vector4 const& value2) {
		return Vector4(
			value1.X - value2.X,
			value1.Y - value2.Y,
			value1.Z - value2.Z,
			value1.W - value2.W);
	}

	Vector4 Vector4::Transform(Vector2 const& value, Matrix const& matrix) {
		Vector4 result;
		result.X = (value.X * matrix.M11) + (value.Y * matrix.M21) + matrix.M41;
		result.Y = (value.X * matrix.M12) + (value.Y * matrix.M22) + matrix.M42;
		result.Z = (value.X * matrix.M13) + (value.Y * matrix.M23) + matrix.M43;
		result.W = (value.X * matrix.M14) + (value.Y * matrix.M24) + matrix.M44;

		return result;
	}

	Vector4 Vector4::Transform(Vector3 const& value, Matrix const& matrix) {
		Vector4 result;
		result.X = (value.X * matrix.M11) + (value.Y * matrix.M21) + (value.Z * matrix.M31) + matrix.M41;
		result.Y = (value.X * matrix.M12) + (value.Y * matrix.M22) + (value.Z * matrix.M32) + matrix.M42;
		result.Z = (value.X * matrix.M13) + (value.Y * matrix.M23) + (value.Z * matrix.M33) + matrix.M43;
		result.W = (value.X * matrix.M14) + (value.Y * matrix.M24) + (value.Z * matrix.M34) + matrix.M44;

		return result;
	}

	Vector4 Vector4::Transform(Vector4 const& value, Matrix const& matrix) {
		Vector4 result;
		result.X = (value.X * matrix.M11) + (value.Y * matrix.M21) + (value.Z * matrix.M31) + (value.W * matrix.M41);
		result.Y = (value.X * matrix.M12) + (value.Y * matrix.M22) + (value.Z * matrix.M32) + (value.W * matrix.M42);
		result.Z = (value.X * matrix.M13) + (value.Y * matrix.M23) + (value.Z * matrix.M33) + (value.W * matrix.M43);
		result.W = (value.X * matrix.M14) + (value.Y * matrix.M24) + (value.Z * matrix.M34) + (value.W * matrix.M44);
		
		return result;
	}

	void Vector4::Transform(std::vector<Vector4> const& sourceArray, size_t sourceIndex, Matrix const& matrix,
		std::vector<Vector4>& destinationArray, size_t destinationIndex, size_t length) {
		//TODO: Verificar exceçoes

		for (size_t i = 0; i < length; i++)
		{
			Vector4 value = sourceArray[sourceIndex + i];
			destinationArray[destinationIndex + i] = Transform(value, matrix);
		}
	}

	void Vector4::Transform(std::vector<Vector4> const& sourceArray, Matrix const& matrix, std::vector<Vector4>& destinationArray) {
		Transform(sourceArray, 0, matrix, destinationArray, 0, destinationArray.size());
	}
}

namespace Xna {
	void Vector4::Ceiling() {
		auto value = Ceiling(*this);
		X = value.X;
		Y = value.Y;
		Z = value.Z;
		W = value.W;
	}

	bool Vector4::Equals(Vector4 const& other) const {
		return W == other.W
			&& X == other.X
			&& Y == other.Y
			&& Z == other.Z;
	}

	void Vector4::Floor() {
		auto value = Floor(*this);
		X = value.X;
		Y = value.Y;
		Z = value.Z;
		W = value.W;
	}

	float Vector4::Length() const {
		return sqrt(LengthSquared());
	}

	float Vector4::LengthSquared() const {
		return (X * X) + (Y * Y) + (Z * Z) + (W * W);
	}

	void Vector4::Normalize() {
		auto value = Normalize(*this);
		X = value.X;
		Y = value.Y;
		Z = value.Z;
		W = value.W;
	}

	void Vector4::Round() {
		auto value = Round(*this);
		X = value.X;
		Y = value.Y;
		Z = value.Z;
		W = value.W;
	}

	void Vector4::Deconstruct(float& x, float& y, float& z, float& w) const {
		x = X;
		y = Y;
		z = Z;
		w = W;
	}
}