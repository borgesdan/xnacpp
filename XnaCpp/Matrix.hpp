#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include "Vector4.hpp"

namespace Xna {
	struct Matrix {
		float M11{ 0 };
		float M12{ 0 };
		float M13{ 0 };
		float M14{ 0 };
		float M21{ 0 };
		float M22{ 0 };
		float M23{ 0 };
		float M24{ 0 };
		float M31{ 0 };
		float M32{ 0 };
		float M33{ 0 };
		float M34{ 0 };
		float M41{ 0 };
		float M42{ 0 };
		float M43{ 0 };
		float M44{ 0 };

		Matrix();
		Matrix(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31,
			float m32, float m33, float m34, float m41, float m42, float m43, float m44);
		Matrix(Vector4 row1, Vector4 row2, Vector4 row3, Vector4 row4);

		static Matrix Identity;

		float Index(int32_t index) const;
		void Index(int32_t index, float value);		
		float Index(int32_t row, int32_t column) const;
		void Index(int32_t row, int32_t column, float value);
		Vector3 Backward() const;
		void Backward(Vector3 const& value);
		Vector3 Down() const;
		void Down(Vector3 const& value);
		Vector3 Forward() const;
		void Forward(Vector3 const& value);
		Vector3 Left() const;
		void Left(Vector3 const& value);
		Vector3 Right() const;
		void Right(Vector3 const& value);
		Vector3 Translation() const;
		void Translation(Vector3 const& value);
		Vector3 Up() const;
		void Up(Vector3 const& value);
	};
}

#endif