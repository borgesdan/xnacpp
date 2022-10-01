#include "Vector2.hpp"
#include "MathHelper.hpp"

namespace Xna {
	const Vector2 Vector2::Zero = Vector2(0);
	const Vector2 Vector2::One = Vector2(1);
	const Vector2 Vector2::UnitX = Vector2(1, 0);
	const Vector2 Vector2::UnitY = Vector2(0, 1);

	Vector2::Vector2(float x, float y) : X(X), Y(y) {}
	Vector2::Vector2(float value) : X(value), Y(value) {}

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
}