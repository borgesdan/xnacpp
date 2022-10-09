#include "Vector4.hpp"

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

	Vector4 Vector4::operator -(Vector4 const& value) {
		return Negate(value);
	}

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