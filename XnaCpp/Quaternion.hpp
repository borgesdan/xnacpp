#ifndef _QUATERNION_HPP_
#define _QUATERNION_HPP_

#include "Vector3.hpp"
#include "Vector4.hpp"

namespace Xna {
	struct Quaternion {
		float X{ 0 };
		float Y{ 0 };
		float Z{ 0 };
		float W{ 0 };

		static const Quaternion Identity;

		Quaternion();
		Quaternion(float x, float y, float z, float w);
		Quaternion(Vector3 const& value, float w);
		Quaternion(Vector4 const& value);

		
		Quaternion operator -();
		friend Quaternion operator +(Quaternion const& quaternion1, Quaternion const& quaternion2);
		friend Quaternion operator /(Quaternion const& quaternion1, Quaternion const& quaternion2);
		friend bool operator ==(Quaternion const& quaternion1, Quaternion const& quaternion2);
		friend bool operator !=(Quaternion const& quaternion1, Quaternion const& quaternion2);
		friend Quaternion operator *(Quaternion const& quaternion1, Quaternion const& quaternion2);
		friend Quaternion operator *(Quaternion const& quaternion1, float scaleFactor);
		friend Quaternion operator -(Quaternion const& quaternion1, Quaternion const& quaternion2);

		static Quaternion Add(Quaternion const& quaternion1, Quaternion const& quaternion2);
		static Quaternion Concatenate(Quaternion const& value1, Quaternion const& value2);
		static Quaternion Conjugate(Quaternion const& value);
		static Quaternion CreateFromAxisAngle(Vector3 const& axis, float angle);
		//static Quaternion CreateFromRotationMatrix(Matrix matrix);
		static Quaternion CreateFromYawPitchRoll(float yaw, float pitch, float roll);
		static Quaternion Divide(Quaternion const& quaternion1, Quaternion const& quaternion2);
		static float Dot(Quaternion const& quaternion1, Quaternion const& quaternion2);
		static Quaternion Inverse(Quaternion const& quaternion);
		static Quaternion Lerp(Quaternion const& quaternion1, Quaternion const& quaternion2, float amount);
		static Quaternion Slerp(Quaternion const& quaternion1, Quaternion const& quaternion2, float amount);
		static Quaternion Subtract(Quaternion const& quaternion1, Quaternion const& quaternion2);
		static Quaternion Multiply(Quaternion const& quaternion1, Quaternion const& quaternion2);
		static Quaternion Multiply(Quaternion const& quaternion1, float scaleFactor);
		static Quaternion Negate(Quaternion const& quaternion);
		static Quaternion Normalize(Quaternion const& quaternion);

		void Conjugate();
		bool Equals(Quaternion const& other) const;
		float Length() const;
		float LengthSquared() const;
		void Normalize();
		Vector4 ToVector4() const;
		void Deconstruct(float& x, float& y, float& z, float& w) const;
	};
}

#endif