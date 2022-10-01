#ifndef _VECTOR2_HPP_
#define _VECTOR2_HPP_

namespace Xna {
	struct Vector2 {
		float X{ 0 };
		float Y{ 0 };

		static const Vector2 Zero;
		static const Vector2 One;
		static const Vector2 UnitX;
		static const Vector2 UnitY;

		Vector2(float x, float y);
		Vector2(float value);

		Vector2 operator -(Vector2 const& value);
		friend Vector2 operator -(Vector2 const& value);
		friend Vector2 operator -(Vector2 const& value1, Vector2 const& value2);
		friend Vector2 operator *(Vector2 const& value1, Vector2 const& value2);
		friend Vector2 operator *(Vector2 const& value, float scaleFactor);
		friend Vector2 operator *(float scaleFactor, Vector2 const& value);
		friend Vector2 operator /(Vector2 const& value1, Vector2 const& value2);
		friend Vector2 operator /(Vector2 const& value1, float divider);
		friend bool operator ==(Vector2 const& value1, Vector2 const& value2);
		friend bool operator !=(Vector2 const& value1, Vector2 const& value2);

		static Vector2 Add(Vector2 const& value1, Vector2 const& value2);
		static Vector2 Barycentric(Vector2 const& value1, Vector2 const& value2,
			Vector2 const& value3, float amount1, float amount2);
	};
}

#endif