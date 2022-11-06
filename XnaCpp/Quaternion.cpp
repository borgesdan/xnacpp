#include <cmath>
#include "Quaternion.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Matrix.hpp"

//Constructors
namespace Xna {
	const Quaternion Quaternion::Identity = Quaternion(0, 0, 0, 1);

	Quaternion::Quaternion() {}

	Quaternion::Quaternion(float x, float y, float z, float w) :
		X(x), Y(y), Z(z), W(w) {}

	Quaternion::Quaternion(Vector3 const& value, float w) :
		X(value.X), Y(value.Y), Z(value.Z), W(w) {}

	Quaternion::Quaternion(Vector4 const& value) :
		X(value.X), Y(value.Y), Z(value.Z), W(value.W) {}
}

//Operators
namespace Xna {
	Quaternion Quaternion::operator -() {
		return Quaternion::Negate(*this);
	}

	Quaternion operator +(Quaternion const& quaternion1, Quaternion const& quaternion2) {
		return Quaternion::Add(quaternion1, quaternion2);
	}

	Quaternion operator /(Quaternion const& quaternion1, Quaternion const& quaternion2) {
		return Quaternion::Divide(quaternion1, quaternion2);
	}

	bool operator ==(Quaternion const& quaternion1, Quaternion const& quaternion2) {
		return quaternion1.Equals(quaternion2);
	}

	bool operator !=(Quaternion const& quaternion1, Quaternion const& quaternion2) {
		return !quaternion1.Equals(quaternion2);
	}

	Quaternion operator *(Quaternion const& quaternion1, Quaternion const& quaternion2) {
		return Quaternion::Multiply(quaternion1, quaternion2);
	}

	Quaternion operator *(Quaternion const& quaternion1, float scaleFactor) {
		return Quaternion::Multiply(quaternion1, scaleFactor);
	}

	Quaternion operator -(Quaternion const& quaternion1, Quaternion const& quaternion2) {
		return Quaternion::Subtract(quaternion1, quaternion2);
	}
}

//Static
namespace Xna {
	Quaternion Quaternion::Add(Quaternion const& quaternion1, Quaternion const& quaternion2) {
		return Quaternion(
			quaternion1.X + quaternion2.X,
			quaternion1.Y + quaternion2.Y,
			quaternion1.Z + quaternion2.Z,
			quaternion1.W + quaternion2.W);
	}

	Quaternion Quaternion::Concatenate(Quaternion const& value1, Quaternion const& value2) {
		auto x1 = value1.X;
		auto y1 = value1.Y;
		auto z1 = value1.Z;
		auto w1 = value1.W;

		auto x2 = value2.X;
		auto y2 = value2.Y;
		auto z2 = value2.Z;
		auto w2 = value2.W;

		return Quaternion(
			((x2 * w1) + (x1 * w2)) + ((y2 * z1) - (z2 * y1)),
			((y2 * w1) + (y1 * w2)) + ((z2 * x1) - (x2 * z1)),
			((z2 * w1) + (z1 * w2)) + ((x2 * y1) - (y2 * x1)),
			(w2 * w1) - (((x2 * x1) + (y2 * y1)) + (z2 * z1)));
	}

	Quaternion Quaternion::Conjugate(Quaternion const& value) {
		return Quaternion(-value.X, -value.Y, -value.Z, value.W);
	}

	Quaternion Quaternion::CreateFromAxisAngle(Vector3 const& axis, float angle) {
		auto half = angle * 0.5f;
		auto _sin = sin(half);
		auto _cos = cos(half);

		return Quaternion(
			axis.X * _sin,
			axis.Y * _sin,
			axis.Z * _sin,
			_cos);
	}

	Quaternion Quaternion::CreateFromYawPitchRoll(float yaw, float pitch, float roll) {
		auto halfRoll = roll * 0.5f;
		auto halfPitch = pitch * 0.5f;
		auto halfYaw = yaw * 0.5f;

		auto sinRoll = sin(halfRoll);
		auto cosRoll = cos(halfRoll);
		auto sinPitch = sin(halfPitch);
		auto cosPitch = cos(halfPitch);
		auto sinYaw = sin(halfYaw);
		auto cosYaw = cos(halfYaw);

		return Quaternion(
			(cosYaw * sinPitch * cosRoll) + (sinYaw * cosPitch * sinRoll),
			(sinYaw * cosPitch * cosRoll) - (cosYaw * sinPitch * sinRoll),
			(cosYaw * cosPitch * sinRoll) - (sinYaw * sinPitch * cosRoll),
			(cosYaw * cosPitch * cosRoll) + (sinYaw * sinPitch * sinRoll));
	}

	Quaternion Quaternion::CreateFromRotationMatrix(Matrix const& matrix) {
		Quaternion quaternion;
		float _sqrt;
		float half;
		auto scale = matrix.M11 + matrix.M22 + matrix.M33;

		if (scale > 0.0f) {
			_sqrt = sqrt(scale + 1.0f);
			quaternion.W = _sqrt * 0.5f;
			_sqrt = 0.5f / _sqrt;

			quaternion.X = (matrix.M23 - matrix.M32) * _sqrt;
			quaternion.Y = (matrix.M31 - matrix.M13) * _sqrt;
			quaternion.Z = (matrix.M12 - matrix.M21) * _sqrt;

			return quaternion;
		}
		if ((matrix.M11 >= matrix.M22) && (matrix.M11 >= matrix.M33)) {
			_sqrt = sqrt(1.0f + matrix.M11 - matrix.M22 - matrix.M33);
			half = 0.5f / _sqrt;

			quaternion.X = 0.5f * _sqrt;
			quaternion.Y = (matrix.M12 + matrix.M21) * half;
			quaternion.Z = (matrix.M13 + matrix.M31) * half;
			quaternion.W = (matrix.M23 - matrix.M32) * half;

			return quaternion;
		}
		if (matrix.M22 > matrix.M33) {
			_sqrt = sqrt(1.0f + matrix.M22 - matrix.M11 - matrix.M33);
			half = 0.5f / _sqrt;

			quaternion.X = (matrix.M21 + matrix.M12) * half;
			quaternion.Y = 0.5f * _sqrt;
			quaternion.Z = (matrix.M32 + matrix.M23) * half;
			quaternion.W = (matrix.M31 - matrix.M13) * half;

			return quaternion;
		}

		_sqrt = sqrt(1.0f + matrix.M33 - matrix.M11 - matrix.M22);
		half = 0.5f / _sqrt;

		quaternion.X = (matrix.M31 + matrix.M13) * half;
		quaternion.Y = (matrix.M32 + matrix.M23) * half;
		quaternion.Z = 0.5f * _sqrt;
		quaternion.W = (matrix.M12 - matrix.M21) * half;

		return quaternion;
	}

	Quaternion Quaternion::Divide(Quaternion const& quaternion1, Quaternion const& quaternion2) {
		auto x = quaternion1.X;
		auto y = quaternion1.Y;
		auto z = quaternion1.Z;
		auto w = quaternion1.W;
		auto num14 = (((quaternion2.X * quaternion2.X) + (quaternion2.Y * quaternion2.Y)) + (quaternion2.Z * quaternion2.Z)) + (quaternion2.W * quaternion2.W);
		auto num5 = 1.0f / num14;
		auto num4 = -quaternion2.X * num5;
		auto num3 = -quaternion2.Y * num5;
		auto num2 = -quaternion2.Z * num5;
		auto num = quaternion2.W * num5;
		auto num13 = (y * num2) - (z * num3);
		auto num12 = (z * num4) - (x * num2);
		auto num11 = (x * num3) - (y * num4);
		auto num10 = ((x * num4) + (y * num3)) + (z * num2);

		return Quaternion(
			((x * num) + (num4 * w)) + num13,
			((y * num) + (num3 * w)) + num12,
			((z * num) + (num2 * w)) + num11,
			(w * num) - num10);
	}

	float Quaternion::Dot(Quaternion const& quaternion1, Quaternion const& quaternion2) {
		return ((((quaternion1.X * quaternion2.X) + (quaternion1.Y * quaternion2.Y)) + (quaternion1.Z * quaternion2.Z)) + (quaternion1.W * quaternion2.W));
	}

	Quaternion Quaternion::Inverse(Quaternion const& quaternion) {
		auto num2 = (((quaternion.X * quaternion.X) + (quaternion.Y * quaternion.Y)) + (quaternion.Z * quaternion.Z)) + (quaternion.W * quaternion.W);
		auto num = 1.0F / num2;

		return Quaternion(
			-quaternion.X * num,
			-quaternion.Y * num,
			-quaternion.Z * num,
			quaternion.W * num);
	}

	Quaternion Quaternion::Lerp(Quaternion const& quaternion1, Quaternion const& quaternion2, float amount) {
		auto num = amount;
		auto num2 = 1.0F - num;
		Quaternion quaternion;

		auto num5 = (((quaternion1.X * quaternion2.X) + (quaternion1.Y * quaternion2.Y)) + (quaternion1.Z * quaternion2.Z)) + (quaternion1.W * quaternion2.W);

		if (num5 >= 0.0F) {
			quaternion.X = (num2 * quaternion1.X) + (num * quaternion2.X);
			quaternion.Y = (num2 * quaternion1.Y) + (num * quaternion2.Y);
			quaternion.Z = (num2 * quaternion1.Z) + (num * quaternion2.Z);
			quaternion.W = (num2 * quaternion1.W) + (num * quaternion2.W);
		}
		else {
			quaternion.X = (num2 * quaternion1.X) - (num * quaternion2.X);
			quaternion.Y = (num2 * quaternion1.Y) - (num * quaternion2.Y);
			quaternion.Z = (num2 * quaternion1.Z) - (num * quaternion2.Z);
			quaternion.W = (num2 * quaternion1.W) - (num * quaternion2.W);
		}

		auto num4 = (((quaternion.X * quaternion.X) + (quaternion.Y * quaternion.Y)) + (quaternion.Z * quaternion.Z)) + (quaternion.W * quaternion.W);
		auto num3 = 1.0F / sqrt(num4);

		quaternion.X *= num3;
		quaternion.Y *= num3;
		quaternion.Z *= num3;
		quaternion.W *= num3;

		return quaternion;
	}

	Quaternion Quaternion::Slerp(Quaternion const& quaternion1, Quaternion const& quaternion2, float amount) {
		float num2;
		float num3;		
		auto num = amount;
		auto num4 = (((quaternion1.X * quaternion2.X) + (quaternion1.Y * quaternion2.Y)) + (quaternion1.Z * quaternion2.Z)) + (quaternion1.W * quaternion2.W);
		auto flag = false;

		if (num4 < 0.0F) {
			flag = true;
			num4 = -num4;
		}
		if (num4 > 0.999999F) {
			num3 = 1.0F - num;
			num2 = flag ? -num : num;
		}
		else {
			auto num5 = acos(num4);
			//TODO: verificar uso de double
			auto num6 = 1.0F / sin(num5);
			num3 = sin((1.0F - num) * num5) * num6;
			num2 = flag ? (-sin(num * num5) * num6) : (sin(num * num5) * num6);
		}

		Quaternion quaternion;
		quaternion.X = (num3 * quaternion1.X) + (num2 * quaternion2.X);
		quaternion.Y = (num3 * quaternion1.Y) + (num2 * quaternion2.Y);
		quaternion.Z = (num3 * quaternion1.Z) + (num2 * quaternion2.Z);
		quaternion.W = (num3 * quaternion1.W) + (num2 * quaternion2.W);

		return quaternion;
	}

	Quaternion Quaternion::Subtract(Quaternion const& quaternion1, Quaternion const& quaternion2) {
		return Quaternion(
			quaternion1.X - quaternion2.X,
			quaternion1.Y - quaternion2.Y,
			quaternion1.Z - quaternion2.Z,
			quaternion1.W - quaternion2.W
		);
	}

	Quaternion Quaternion::Multiply(Quaternion const& quaternion1, Quaternion const& quaternion2) {
		auto x = quaternion1.X;
		auto y = quaternion1.Y;
		auto z = quaternion1.Z;
		auto w = quaternion1.W;
		auto num4 = quaternion2.X;
		auto num3 = quaternion2.Y;
		auto num2 = quaternion2.Z;
		auto num = quaternion2.W;
		auto num12 = (y * num2) - (z * num3);
		auto num11 = (z * num4) - (x * num2);
		auto num10 = (x * num3) - (y * num4);
		auto num9 = ((x * num4) + (y * num3)) + (z * num2);
		
		Quaternion quaternion;
		quaternion.X = ((x * num) + (num4 * w)) + num12;
		quaternion.Y = ((y * num) + (num3 * w)) + num11;
		quaternion.Z = ((z * num) + (num2 * w)) + num10;
		quaternion.W = (w * num) - num9;
		
		return quaternion;
	}
	
	Quaternion Quaternion::Multiply(Quaternion const& quaternion1, float scaleFactor) {
		return Quaternion(
			quaternion1.X * scaleFactor,
			quaternion1.Y * scaleFactor,
			quaternion1.Z * scaleFactor,
			quaternion1.W * scaleFactor);
	}
	
	Quaternion Quaternion::Negate(Quaternion const& quaternion) {
		return Quaternion(-quaternion.X, -quaternion.Y, -quaternion.Z, -quaternion.W);
	}

	Quaternion Quaternion::Normalize(Quaternion const& quaternion) {
		auto num = 1.0F / sqrt((quaternion.X * quaternion.X) + (quaternion.Y * quaternion.Y) + (quaternion.Z * quaternion.Z) + (quaternion.W * quaternion.W));
		
		return Quaternion(
			quaternion.X * num,
			quaternion.Y * num,
			quaternion.Z * num,
			quaternion.W * num);
	}
}

//Functions
namespace Xna {
	void Quaternion::Conjugate() {
		auto value = Conjugate(*this);
		X = value.X;
		Y = value.Y;
		Z = value.Z;
		W = value.W;
	}

	bool Quaternion::Equals(Quaternion const& other) const {
		return X == other.X
			&& Y == other.Y
			&& Z == other.Z
			&& W == other.W;
	}

	float Quaternion::Length() const {
		return sqrt(LengthSquared());
	}

	float Quaternion::LengthSquared() const {
		return (X * X) + (Y * Y) + (Z * Z) + (W * W);
	}

	void Quaternion::Normalize() {
		auto value = Normalize(*this);
		X = value.X;
		Y = value.Y;
		Z = value.Z;
		W = value.W;
	}

	Vector4 Quaternion::ToVector4() const {
		return Vector4(X, Y, Z, W);
	}

	void Quaternion::Deconstruct(float& x, float& y, float& z, float& w) const {
		x = X;
		y = Y;
		z = Z;
		w = W;
	}
}