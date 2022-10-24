#include "Matrix.hpp"

//Constructors
namespace Xna {
	Matrix::Matrix() {}

	Matrix::Matrix(
		float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44) :
		M11(m11), M12(m12), M13(m13), M14(m14),
		M21(m21), M22(m22), M23(m23), M24(m24),
		M31(m31), M32(m32), M33(m33), M34(m34),
		M41(m41), M42(m42), M43(m43), M44(m44) {}

	Matrix::Matrix(Vector4 row1, Vector4 row2, Vector4 row3, Vector4 row4) :
		M11(row1.X), M12(row1.Y), M13(row1.Z), M14(row1.W),
		M21(row2.X), M22(row2.Y), M23(row2.Z), M24(row2.W),
		M31(row3.X), M32(row3.Y), M33(row3.Z), M34(row3.W),
		M41(row4.X), M42(row4.Y), M43(row4.Z), M44(row4.W) {}
}

//Operators
namespace Xna {

}

//Static
namespace Xna {
	Matrix Matrix::Identity = Matrix(
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f);
}

//Functions
namespace Xna {
	float Matrix::Index(int32_t index) const {
		switch (index)
		{
		case 0: return M11;
		case 1: return M12;
		case 2: return M13;
		case 3: return M14;
		case 4: return M21;
		case 5: return M22;
		case 6: return M23;
		case 7: return M24;
		case 8: return M31;
		case 9: return M32;
		case 10: return M33;
		case 11: return M34;
		case 12: return M41;
		case 13: return M42;
		case 14: return M43;
		case 15: return M44;
		}
	}
	
	void Matrix::Index(int32_t index, float value) {
		switch (index)
		{
		case 0: M11 = value; break;
		case 1: M12 = value; break;
		case 2: M13 = value; break;
		case 3: M14 = value; break;
		case 4: M21 = value; break;
		case 5: M22 = value; break;
		case 6: M23 = value; break;
		case 7: M24 = value; break;
		case 8: M31 = value; break;
		case 9: M32 = value; break;
		case 10: M33 = value; break;
		case 11: M34 = value; break;
		case 12: M41 = value; break;
		case 13: M42 = value; break;
		case 14: M43 = value; break;
		case 15: M44 = value; break;
		}
	}

	float Matrix::Index(int32_t row, int32_t column) const {
		return Index((row * 4) + column);
	}
	
	void Matrix::Index(int32_t row, int32_t column, float value) {
		Index((row * 4) + column, value);
	}

	Vector3 Matrix::Backward() const {
		return Vector3(M31, M32, M33);
	}

	void Matrix::Backward(Vector3 const& value) {
		M31 = value.X;
		M32 = value.Y;
		M33 = value.Z;
	}

	Vector3 Matrix::Down() const {
		return Vector3(-M21, -M22, -M23);
	}

	void Matrix::Down(Vector3 const& value) {
		M21 = -value.X;
		M22 = -value.Y;
		M23 = -value.Z;
	}

	Vector3 Matrix::Forward() const {
		Vector3(-M31, -M32, -M33);
	}

	void Matrix::Forward(Vector3 const& value) {
		M31 = -value.X;
		M32 = -value.Y;
		M33 = -value.Z;
	}

	Vector3 Matrix::Left() const {
		new Vector3(-M11, -M12, -M13);
	}

	void Matrix::Left(Vector3 const& value) {
		M11 = -value.X;
		M12 = -value.Y;
		M13 = -value.Z;
	}
	
	Vector3 Matrix::Right() const {
		return Vector3(M11, M12, M13);
	}

	void Matrix::Right(Vector3 const& value) {
		M11 = value.X;
		M12 = value.Y;
		M13 = value.Z;
	}

	Vector3 Matrix::Translation() const {
		return Vector3(M41, M42, M43);
	}

	void Matrix::Translation(Vector3 const& value) {
		M41 = value.X;
		M42 = value.Y;
		M43 = value.Z;
	}

	Vector3 Matrix::Up() const {
		return Vector3(M21, M22, M23);
	}

	void Matrix::Up(Vector3 const& value) {
		M21 = value.X;
		M22 = value.Y;
		M23 = value.Z;
	}
}