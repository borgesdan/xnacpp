#include <cmath>
#include "Vector2.hpp"
#include "MathHelper.hpp"

namespace Xna {
	const Vector2 Vector2::Zero = Vector2(0);
	const Vector2 Vector2::One = Vector2(1);
	const Vector2 Vector2::UnitX = Vector2(1, 0);
	const Vector2 Vector2::UnitY = Vector2(0, 1);

	Vector2::Vector2() {}
	Vector2::Vector2(float x, float y) : X(X), Y(y) {}
	Vector2::Vector2(float value) : X(value), Y(value) {}

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
		float val = 1.0F / sqrt((value.X * value.X) + (value.Y * value.Y));		
		return Vector2(value.X * val, value.Y * val);
	}

	Vector2 Vector2::Reflect(Vector2 const& vector, Vector2 const& normal) {		
		float val = 2.0F * ((vector.X * normal.X) + (vector.Y * normal.Y));
		
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

	void Vector2::Ceiling() {
		auto value = Ceiling(*this);
		X = value.X;
		Y = value.Y;
	}

	bool Vector2::Equals(Vector2 const& other) const {
		return (X == other.X) && (Y == other.Y);
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

	Point Vector2::ToPoint() const {
		return Point(
			static_cast<int32_t>(X),
			static_cast<int32_t>(Y));
	}

	void Vector2::Deconstruct(float& x, float& y) const {
		x = X;
		y = Y;
	}
}