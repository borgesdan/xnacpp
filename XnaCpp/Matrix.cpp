#include "Matrix.hpp"
#include <cmath>
#include <limits>
#include "MathHelper.hpp"
#include "Quaternion.hpp"
#include "Vector4.hpp"
#include "Vector3.hpp"
#include "CSharp/Nullable.hpp"
#include "Rectangle.hpp"

using CSharp::Nullable;
using std::numeric_limits;

//Constructors
namespace Xna {

	Matrix Matrix::Identity = Matrix(
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f);

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
	Matrix Matrix::operator -() {
		return Negate(*this);
	}

	Matrix operator +(Matrix const& matrix1, Matrix const& matrix2) {
		return Matrix::Add(matrix1, matrix2);
	}

	Matrix operator /(Matrix const& matrix1, Matrix const& matrix2) {
		return Matrix::Divide(matrix1, matrix2);
	}

	Matrix operator /(Matrix const& matrix, float divider) {
		return Matrix::Divide(matrix, divider);
	}

	bool operator ==(Matrix const& matrix1, Matrix const& matrix2) {
		return matrix1.Equals(matrix2);
	}

	bool operator !=(Matrix const& matrix1, Matrix const& matrix2) {
		return !matrix1.Equals(matrix2);
	}

	Matrix operator *(Matrix const& matrix1, Matrix const& matrix2) {
		return Matrix::Multiply(matrix1, matrix2);
	}

	Matrix operator *(Matrix const& matrix, float scaleFactor) {
		return Matrix::Multiply(matrix, scaleFactor);
	}

	Matrix operator -(Matrix const& matrix1, Matrix const& matrix2) {
		return Matrix::Subtract(matrix1, matrix2);
	}
}

//Static
namespace Xna {
	Matrix Matrix::Add(Matrix const& matrix1, Matrix const& matrix2) {
		Matrix result;
		result.M11 = matrix1.M11 + matrix2.M11;
		result.M12 = matrix1.M12 + matrix2.M12;
		result.M13 = matrix1.M13 + matrix2.M13;
		result.M14 = matrix1.M14 + matrix2.M14;
		result.M21 = matrix1.M21 + matrix2.M21;
		result.M22 = matrix1.M22 + matrix2.M22;
		result.M23 = matrix1.M23 + matrix2.M23;
		result.M24 = matrix1.M24 + matrix2.M24;
		result.M31 = matrix1.M31 + matrix2.M31;
		result.M32 = matrix1.M32 + matrix2.M32;
		result.M33 = matrix1.M33 + matrix2.M33;
		result.M34 = matrix1.M34 + matrix2.M34;
		result.M41 = matrix1.M41 + matrix2.M41;
		result.M42 = matrix1.M42 + matrix2.M42;
		result.M43 = matrix1.M43 + matrix2.M43;
		result.M44 = matrix1.M44 + matrix2.M44;

		return result;
	}

	Matrix Matrix::CreateBillboard(Vector3 const& objectPosition, Vector3 const& cameraPosition,
		Vector3 const& cameraUpVector, Nullable<Vector3> const& cameraForwardVector) {

		Vector3 vector;
		Vector3 vector2;
		Vector3 vector3;
		vector.X = objectPosition.X - cameraPosition.X;
		vector.Y = objectPosition.Y - cameraPosition.Y;
		vector.Z = objectPosition.Z - cameraPosition.Z;
		auto num = vector.LengthSquared();

		if (num < 0.0001f) {
			vector = cameraForwardVector.HasValue() ? -cameraForwardVector.Value() : Vector3::Forward;
		}
		else {
			vector = Vector3::Multiply(vector, 1.0f / sqrt(num));
		}

		vector3 = Vector3::Cross(cameraUpVector, vector);
		vector3.Normalize();
		vector2 = Vector3::Cross(vector, vector3);

		Matrix result;
		result.M11 = vector3.X;
		result.M12 = vector3.Y;
		result.M13 = vector3.Z;
		result.M14 = 0.F;
		result.M21 = vector2.X;
		result.M22 = vector2.Y;
		result.M23 = vector2.Z;
		result.M24 = 0.F;
		result.M31 = vector.X;
		result.M32 = vector.Y;
		result.M33 = vector.Z;
		result.M34 = 0.F;
		result.M41 = objectPosition.X;
		result.M42 = objectPosition.Y;
		result.M43 = objectPosition.Z;
		result.M44 = 1.F;

		return result;
	}

	Matrix Matrix::CreateConstrainedBillboard(Vector3 const& objectPosition, Vector3 const& cameraPosition,
		Vector3 const& rotateAxis, Nullable<Vector3> const& cameraForwardVector, Nullable<Vector3> const& objectForwardVector) {

		Vector3 vector;
		Vector3 vector3;
		Vector3 vector2;
		vector2.X = objectPosition.X - cameraPosition.X;
		vector2.Y = objectPosition.Y - cameraPosition.Y;
		vector2.Z = objectPosition.Z - cameraPosition.Z;
		auto num2 = vector2.LengthSquared();

		if (num2 < 0.0001f) {
			vector2 = cameraForwardVector.HasValue() ? -cameraForwardVector.Value() : Vector3::Forward;
		}
		else {
			vector2 = Vector3::Multiply(vector2, 1.f / sqrt(num2));
		}

		auto vector4 = rotateAxis;
		auto num = Vector3::Dot(rotateAxis, vector2);

		if (abs(num) > 0.9982547f) {
			if (objectForwardVector.HasValue()) {
				vector = objectForwardVector.Value();
				num = Vector3::Dot(rotateAxis, vector);

				if (abs(num) > 0.9982547f) {
					num = ((rotateAxis.X * Vector3::Forward.X) + (rotateAxis.Y * Vector3::Forward.Y)) + (rotateAxis.Z * Vector3::Forward.Z);
					vector = (abs(num) > 0.9982547f) ? Vector3::Right : Vector3::Forward;
				}
			}
			else {
				num = ((rotateAxis.X * Vector3::Forward.X) + (rotateAxis.Y * Vector3::Forward.Y)) + (rotateAxis.Z * Vector3::Forward.Z);
				vector = (abs(num) > 0.9982547f) ? Vector3::Right : Vector3::Forward;
			}

			vector3 = Vector3::Cross(rotateAxis, vector);
			vector3.Normalize();
			vector = Vector3::Cross(vector3, rotateAxis);
			vector.Normalize();
		}
		else {
			vector3 = Vector3::Cross(rotateAxis, vector2);
			vector3.Normalize();
			vector = Vector3::Cross(vector3, vector4);
			vector.Normalize();
		}

		Matrix result;
		result.M11 = vector3.X;
		result.M12 = vector3.Y;
		result.M13 = vector3.Z;
		result.M14 = 0;
		result.M21 = vector4.X;
		result.M22 = vector4.Y;
		result.M23 = vector4.Z;
		result.M24 = 0;
		result.M31 = vector.X;
		result.M32 = vector.Y;
		result.M33 = vector.Z;
		result.M34 = 0;
		result.M41 = objectPosition.X;
		result.M42 = objectPosition.Y;
		result.M43 = objectPosition.Z;
		result.M44 = 1;

		return result;
	}

	Matrix Matrix::CreateFromAxisAngle(Vector3 const& axis, float angle) {
		auto x = axis.X;
		auto y = axis.Y;
		auto z = axis.Z;
		auto num2 = sin(angle);
		auto num = cos(angle);
		auto num11 = x * x;
		auto num10 = y * y;
		auto num9 = z * z;
		auto num8 = x * y;
		auto num7 = x * z;
		auto num6 = y * z;

		Matrix result;
		result.M11 = num11 + (num * (1.f - num11));
		result.M12 = (num8 - (num * num8)) + (num2 * z);
		result.M13 = (num7 - (num * num7)) - (num2 * y);
		result.M14 = 0;
		result.M21 = (num8 - (num * num8)) - (num2 * z);
		result.M22 = num10 + (num * (1.f - num10));
		result.M23 = (num6 - (num * num6)) + (num2 * x);
		result.M24 = 0;
		result.M31 = (num7 - (num * num7)) + (num2 * y);
		result.M32 = (num6 - (num * num6)) - (num2 * x);
		result.M33 = num9 + (num * (1.f - num9));
		result.M34 = 0;
		result.M41 = 0;
		result.M42 = 0;
		result.M43 = 0;
		result.M44 = 1;

		return result;
	}

	Matrix Matrix::CreateFromQuaternion(Quaternion const& quaternion) {
		auto num9 = quaternion.X * quaternion.X;
		auto num8 = quaternion.Y * quaternion.Y;
		auto num7 = quaternion.Z * quaternion.Z;
		auto num6 = quaternion.X * quaternion.Y;
		auto num5 = quaternion.Z * quaternion.W;
		auto num4 = quaternion.Z * quaternion.X;
		auto num3 = quaternion.Y * quaternion.W;
		auto num2 = quaternion.Y * quaternion.Z;
		auto num = quaternion.X * quaternion.W;

		Matrix result;
		result.M11 = 1.f - (2.f * (num8 + num7));
		result.M12 = 2.f * (num6 + num5);
		result.M13 = 2.f * (num4 - num3);
		result.M14 = 0.f;
		result.M21 = 2.f * (num6 - num5);
		result.M22 = 1.f - (2.f * (num7 + num9));
		result.M23 = 2.f * (num2 + num);
		result.M24 = 0.f;
		result.M31 = 2.f * (num4 + num3);
		result.M32 = 2.f * (num2 - num);
		result.M33 = 1.f - (2.f * (num8 + num9));
		result.M34 = 0.f;
		result.M41 = 0.f;
		result.M42 = 0.f;
		result.M43 = 0.f;
		result.M44 = 1.f;

		return result;
	}

	Matrix Matrix::CreateFromYawPitchRoll(float yaw, float pitch, float roll) {
		auto quaternion = Quaternion::CreateFromYawPitchRoll(yaw, pitch, roll);
		return CreateFromQuaternion(quaternion);
	}

	Matrix Matrix::CreateLookAt(Vector3 const& cameraPosition, Vector3 const& cameraTarget, Vector3 const& cameraUpVector) {
		auto vector = Vector3::Normalize(cameraPosition - cameraTarget);
		auto vector2 = Vector3::Normalize(Vector3::Cross(cameraUpVector, vector));
		auto vector3 = Vector3::Cross(vector, vector2);

		Matrix result;
		result.M11 = vector2.X;
		result.M12 = vector3.X;
		result.M13 = vector.X;
		result.M14 = 0.f;
		result.M21 = vector2.Y;
		result.M22 = vector3.Y;
		result.M23 = vector.Y;
		result.M24 = 0.f;
		result.M31 = vector2.Z;
		result.M32 = vector3.Z;
		result.M33 = vector.Z;
		result.M34 = 0.f;
		result.M41 = -Vector3::Dot(vector2, cameraPosition);
		result.M42 = -Vector3::Dot(vector3, cameraPosition);
		result.M43 = -Vector3::Dot(vector, cameraPosition);
		result.M44 = 1.f;
		return result;
	}

	Matrix Matrix::CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane) {
		Matrix result;
		result.M11 = 2.f / width;
		result.M12 = result.M13 = result.M14 = 0.f;
		result.M22 = 2.f / height;
		result.M21 = result.M23 = result.M24 = 0.f;
		result.M33 = 1.f / (zNearPlane - zFarPlane);
		result.M31 = result.M32 = result.M34 = 0.f;
		result.M41 = result.M42 = 0.f;
		result.M43 = zNearPlane / (zNearPlane - zFarPlane);
		result.M44 = 1.f;

		return result;
	}

	Matrix Matrix::CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane) {

		//TODO: Conferir utilização de double no código original
		Matrix result;
		result.M11 = 2.0f / (right - left);
		result.M12 = 0.0f;
		result.M13 = 0.0f;
		result.M14 = 0.0f;
		result.M21 = 0.0f;
		result.M22 = 2.0f / (top - bottom);
		result.M23 = 0.0f;
		result.M24 = 0.0f;
		result.M31 = 0.0f;
		result.M32 = 0.0f;
		result.M33 = 1.0f / (zNearPlane - zFarPlane);
		result.M34 = 0.0f;
		result.M41 = (left + right) / (left - right);
		result.M42 = (top + bottom) / (bottom - top);
		result.M43 = zNearPlane / (zNearPlane - zFarPlane);
		result.M44 = 1.0f;
		return result;
	}

	Matrix Matrix::CreatePerspective(float width, float height, float nearPlaneDistance, float farPlaneDistance) {

		//TODO: conferir exceções

		auto negFarRange = MathHelper::IsPositiveInfinity(farPlaneDistance) ? -1.0f : farPlaneDistance / (nearPlaneDistance - farPlaneDistance);

		Matrix result;
		result.M11 = (2.0f * nearPlaneDistance) / width;
		result.M12 = result.M13 = result.M14 = 0.0f;
		result.M22 = (2.0f * nearPlaneDistance) / height;
		result.M21 = result.M23 = result.M24 = 0.0f;
		result.M33 = negFarRange;
		result.M31 = result.M32 = 0.0f;
		result.M34 = -1.0f;
		result.M41 = result.M42 = result.M44 = 0.0f;
		result.M43 = nearPlaneDistance * negFarRange;

		return result;
	}

	Matrix Matrix::CreatePerspectiveFieldOfView(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance) {

		//TODO: Conferir exceções

		auto yScale = 1.0f / tan(fieldOfView * 0.5f);
		auto xScale = yScale / aspectRatio;
		auto negFarRange = MathHelper::IsPositiveInfinity(farPlaneDistance) ? -1.0f : farPlaneDistance / (nearPlaneDistance - farPlaneDistance);

		Matrix result;
		result.M11 = xScale;
		result.M12 = result.M13 = result.M14 = 0.0f;
		result.M22 = yScale;
		result.M21 = result.M23 = result.M24 = 0.0f;
		result.M31 = result.M32 = 0.0f;
		result.M33 = negFarRange;
		result.M34 = -1.0f;
		result.M41 = result.M42 = result.M44 = 0.0f;
		result.M43 = nearPlaneDistance * negFarRange;

		return result;
	}

	Matrix Matrix::CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlaneDistance, float farPlaneDistance) {

		//TODO: conferir exceções

		Matrix result;
		result.M11 = (2.f * nearPlaneDistance) / (right - left);
		result.M12 = result.M13 = result.M14 = 0;
		result.M22 = (2.f * nearPlaneDistance) / (top - bottom);
		result.M21 = result.M23 = result.M24 = 0;
		result.M31 = (left + right) / (right - left);
		result.M32 = (top + bottom) / (top - bottom);
		result.M33 = farPlaneDistance / (nearPlaneDistance - farPlaneDistance);
		result.M34 = -1;
		result.M43 = (nearPlaneDistance * farPlaneDistance) / (nearPlaneDistance - farPlaneDistance);
		result.M41 = result.M42 = result.M44 = 0;

		return result;
	}

	Matrix Matrix::CreatePerspectiveOffCenter(Rectangle const& viewingVolume, float nearPlaneDistance, float farPlaneDistance) {
		return CreatePerspectiveOffCenter(
			static_cast<float>(viewingVolume.Left()),
			static_cast<float>(viewingVolume.Right()),
			static_cast<float>(viewingVolume.Bottom()),
			static_cast<float>(viewingVolume.Top()),
			nearPlaneDistance,
			farPlaneDistance);
	}

	Matrix Matrix::CreateRotationX(float radians) {
		Matrix result = Matrix::Identity;

		auto val1 = cos(radians);
		auto val2 = sin(radians);

		result.M22 = val1;
		result.M23 = val2;
		result.M32 = -val2;
		result.M33 = val1;

		return result;
	}

	Matrix Matrix::CreateRotationY(float radians) {
		Matrix result = Matrix::Identity;

		auto val1 = cos(radians);
		auto val2 = sin(radians);

		result.M11 = val1;
		result.M13 = -val2;
		result.M31 = val2;
		result.M33 = val1;

		return result;
	}

	Matrix Matrix::CreateRotationZ(float radians) {
		Matrix result = Matrix::Identity;

		auto val1 = cos(radians);
		auto val2 = sin(radians);

		result.M11 = val1;
		result.M12 = val2;
		result.M21 = -val2;
		result.M22 = val1;

		return result;
	}

	Matrix Matrix::CreateScale(float scale) {
		return CreateScale(scale, scale, scale);
	}

	Matrix Matrix::CreateScale(float xScale, float yScale, float zScale) {
		Matrix result;

		result.M11 = xScale;
		result.M12 = 0;
		result.M13 = 0;
		result.M14 = 0;
		result.M21 = 0;
		result.M22 = yScale;
		result.M23 = 0;
		result.M24 = 0;
		result.M31 = 0;
		result.M32 = 0;
		result.M33 = zScale;
		result.M34 = 0;
		result.M41 = 0;
		result.M42 = 0;
		result.M43 = 0;
		result.M44 = 1;

		return result;
	}

	Matrix Matrix::CreateScale(Vector3 const& scales) {
		return CreateScale(scales.X, scales.Y, scales.Z);
	}

	Matrix Matrix::CreateTranslation(float xPosition, float yPosition, float zPosition) {
		Matrix result;

		result.M11 = 1;
		result.M12 = 0;
		result.M13 = 0;
		result.M14 = 0;
		result.M21 = 0;
		result.M22 = 1;
		result.M23 = 0;
		result.M24 = 0;
		result.M31 = 0;
		result.M32 = 0;
		result.M33 = 1;
		result.M34 = 0;
		result.M41 = xPosition;
		result.M42 = yPosition;
		result.M43 = zPosition;
		result.M44 = 1;

		return result;
	}

	Matrix Matrix::CreateTranslation(Vector3 const& position) {
		return CreateTranslation(position.X, position.Y, position.Z);
	}

	Matrix Matrix::CreateWorld(Vector3 const& position, Vector3 const& forward, Vector3 const& up) {

		auto z = Vector3::Normalize(forward);
		auto x = Vector3::Cross(forward, up);
		auto y = Vector3::Cross(x, forward);

		x.Normalize();
		y.Normalize();

		Matrix result;
		result.Right(x);
		result.Up(y);
		result.Forward(z);
		result.Translation(position);
		result.M44 = 1.f;

		return result;
	}

	Matrix Matrix::Divide(Matrix const& matrix1, Matrix const& matrix2) {
		Matrix result;

		result.M11 = matrix1.M11 / matrix2.M11;
		result.M12 = matrix1.M12 / matrix2.M12;
		result.M13 = matrix1.M13 / matrix2.M13;
		result.M14 = matrix1.M14 / matrix2.M14;
		result.M21 = matrix1.M21 / matrix2.M21;
		result.M22 = matrix1.M22 / matrix2.M22;
		result.M23 = matrix1.M23 / matrix2.M23;
		result.M24 = matrix1.M24 / matrix2.M24;
		result.M31 = matrix1.M31 / matrix2.M31;
		result.M32 = matrix1.M32 / matrix2.M32;
		result.M33 = matrix1.M33 / matrix2.M33;
		result.M34 = matrix1.M34 / matrix2.M34;
		result.M41 = matrix1.M41 / matrix2.M41;
		result.M42 = matrix1.M42 / matrix2.M42;
		result.M43 = matrix1.M43 / matrix2.M43;
		result.M44 = matrix1.M44 / matrix2.M44;

		return result;
	}

	Matrix Matrix::Divide(Matrix const& matrix1, float divider) {
		auto num = 1.f / divider;

		Matrix result;
		result.M11 = matrix1.M11 * num;
		result.M12 = matrix1.M12 * num;
		result.M13 = matrix1.M13 * num;
		result.M14 = matrix1.M14 * num;
		result.M21 = matrix1.M21 * num;
		result.M22 = matrix1.M22 * num;
		result.M23 = matrix1.M23 * num;
		result.M24 = matrix1.M24 * num;
		result.M31 = matrix1.M31 * num;
		result.M32 = matrix1.M32 * num;
		result.M33 = matrix1.M33 * num;
		result.M34 = matrix1.M34 * num;
		result.M41 = matrix1.M41 * num;
		result.M42 = matrix1.M42 * num;
		result.M43 = matrix1.M43 * num;
		result.M44 = matrix1.M44 * num;

		return result;
	}

	Matrix Matrix::Invert(Matrix const& matrix) {

		//TODO: observar conversão para double

		auto num1 = matrix.M11;
		auto num2 = matrix.M12;
		auto num3 = matrix.M13;
		auto num4 = matrix.M14;
		auto num5 = matrix.M21;
		auto num6 = matrix.M22;
		auto num7 = matrix.M23;
		auto num8 = matrix.M24;
		auto num9 = matrix.M31;
		auto num10 = matrix.M32;
		auto num11 = matrix.M33;
		auto num12 = matrix.M34;
		auto num13 = matrix.M41;
		auto num14 = matrix.M42;
		auto num15 = matrix.M43;
		auto num16 = matrix.M44;

		auto num17 = (num11 * num16 - num12 * num15);
		auto num18 = (num10 * num16 - num12 * num14);
		auto num19 = (num10 * num15 - num11 * num14);
		auto num20 = (num9 * num16 - num12 * num13);
		auto num21 = (num9 * num15 - num11 * num13);
		auto num22 = (num9 * num14 - num10 * num13);
		auto num23 = (num6 * num17 - num7 * num18 + num8 * num19);
		auto num24 = -(num5 * num17 - num7 * num20 + num8 * num21);
		auto num25 = (num5 * num18 - num6 * num20 + num8 * num22);
		auto num26 = -(num5 * num19 - num6 * num21 + num7 * num22);
		auto num27 = (1.0F / (num1 * num23 + num2 * num24 + num3 * num25 + num4 * num26));

		Matrix result;
		result.M11 = num23 * num27;
		result.M21 = num24 * num27;
		result.M31 = num25 * num27;
		result.M41 = num26 * num27;
		result.M12 = -(num2 * num17 - num3 * num18 + num4 * num19) * num27;
		result.M22 = (num1 * num17 - num3 * num20 + num4 * num21) * num27;
		result.M32 = -(num1 * num18 - num2 * num20 + num4 * num22) * num27;
		result.M42 = (num1 * num19 - num2 * num21 + num3 * num22) * num27;

		auto num28 = (num7 * num16 - num8 * num15);
		auto num29 = (num6 * num16 - num8 * num14);
		auto num30 = (num6 * num15 - num7 * num14);
		auto num31 = (num5 * num16 - num8 * num13);
		auto num32 = (num5 * num15 - num7 * num13);
		auto num33 = (num5 * num14 - num6 * num13);
		result.M13 = (num2 * num28 - num3 * num29 + num4 * num30) * num27;
		result.M23 = -(num1 * num28 - num3 * num31 + num4 * num32) * num27;
		result.M33 = (num1 * num29 - num2 * num31 + num4 * num33) * num27;
		result.M43 = -(num1 * num30 - num2 * num32 + num3 * num33) * num27;

		auto num34 = (num7 * num12 - num8 * num11);
		auto num35 = (num6 * num12 - num8 * num10);
		auto num36 = (num6 * num11 - num7 * num10);
		auto num37 = (num5 * num12 - num8 * num9);
		auto num38 = (num5 * num11 - num7 * num9);
		auto num39 = (num5 * num10 - num6 * num9);
		result.M14 = -(num2 * num34 - num3 * num35 + num4 * num36) * num27;
		result.M24 = (num1 * num34 - num3 * num37 + num4 * num38) * num27;
		result.M34 = -(num1 * num35 - num2 * num37 + num4 * num39) * num27;
		result.M44 = (num1 * num36 - num2 * num38 + num3 * num39) * num27;

		return result;
	}

	Matrix Matrix::Lerp(Matrix const& matrix1, Matrix const& matrix2, float amount) {
		Matrix result;

		result.M11 = matrix1.M11 + ((matrix2.M11 - matrix1.M11) * amount);
		result.M12 = matrix1.M12 + ((matrix2.M12 - matrix1.M12) * amount);
		result.M13 = matrix1.M13 + ((matrix2.M13 - matrix1.M13) * amount);
		result.M14 = matrix1.M14 + ((matrix2.M14 - matrix1.M14) * amount);
		result.M21 = matrix1.M21 + ((matrix2.M21 - matrix1.M21) * amount);
		result.M22 = matrix1.M22 + ((matrix2.M22 - matrix1.M22) * amount);
		result.M23 = matrix1.M23 + ((matrix2.M23 - matrix1.M23) * amount);
		result.M24 = matrix1.M24 + ((matrix2.M24 - matrix1.M24) * amount);
		result.M31 = matrix1.M31 + ((matrix2.M31 - matrix1.M31) * amount);
		result.M32 = matrix1.M32 + ((matrix2.M32 - matrix1.M32) * amount);
		result.M33 = matrix1.M33 + ((matrix2.M33 - matrix1.M33) * amount);
		result.M34 = matrix1.M34 + ((matrix2.M34 - matrix1.M34) * amount);
		result.M41 = matrix1.M41 + ((matrix2.M41 - matrix1.M41) * amount);
		result.M42 = matrix1.M42 + ((matrix2.M42 - matrix1.M42) * amount);
		result.M43 = matrix1.M43 + ((matrix2.M43 - matrix1.M43) * amount);
		result.M44 = matrix1.M44 + ((matrix2.M44 - matrix1.M44) * amount);

		return result;
	}

	Matrix Matrix::Multiply(Matrix const& matrix1, Matrix const& matrix2) {
		auto m11 = (((matrix1.M11 * matrix2.M11) + (matrix1.M12 * matrix2.M21)) + (matrix1.M13 * matrix2.M31)) + (matrix1.M14 * matrix2.M41);
		auto m12 = (((matrix1.M11 * matrix2.M12) + (matrix1.M12 * matrix2.M22)) + (matrix1.M13 * matrix2.M32)) + (matrix1.M14 * matrix2.M42);
		auto m13 = (((matrix1.M11 * matrix2.M13) + (matrix1.M12 * matrix2.M23)) + (matrix1.M13 * matrix2.M33)) + (matrix1.M14 * matrix2.M43);
		auto m14 = (((matrix1.M11 * matrix2.M14) + (matrix1.M12 * matrix2.M24)) + (matrix1.M13 * matrix2.M34)) + (matrix1.M14 * matrix2.M44);
		auto m21 = (((matrix1.M21 * matrix2.M11) + (matrix1.M22 * matrix2.M21)) + (matrix1.M23 * matrix2.M31)) + (matrix1.M24 * matrix2.M41);
		auto m22 = (((matrix1.M21 * matrix2.M12) + (matrix1.M22 * matrix2.M22)) + (matrix1.M23 * matrix2.M32)) + (matrix1.M24 * matrix2.M42);
		auto m23 = (((matrix1.M21 * matrix2.M13) + (matrix1.M22 * matrix2.M23)) + (matrix1.M23 * matrix2.M33)) + (matrix1.M24 * matrix2.M43);
		auto m24 = (((matrix1.M21 * matrix2.M14) + (matrix1.M22 * matrix2.M24)) + (matrix1.M23 * matrix2.M34)) + (matrix1.M24 * matrix2.M44);
		auto m31 = (((matrix1.M31 * matrix2.M11) + (matrix1.M32 * matrix2.M21)) + (matrix1.M33 * matrix2.M31)) + (matrix1.M34 * matrix2.M41);
		auto m32 = (((matrix1.M31 * matrix2.M12) + (matrix1.M32 * matrix2.M22)) + (matrix1.M33 * matrix2.M32)) + (matrix1.M34 * matrix2.M42);
		auto m33 = (((matrix1.M31 * matrix2.M13) + (matrix1.M32 * matrix2.M23)) + (matrix1.M33 * matrix2.M33)) + (matrix1.M34 * matrix2.M43);
		auto m34 = (((matrix1.M31 * matrix2.M14) + (matrix1.M32 * matrix2.M24)) + (matrix1.M33 * matrix2.M34)) + (matrix1.M34 * matrix2.M44);
		auto m41 = (((matrix1.M41 * matrix2.M11) + (matrix1.M42 * matrix2.M21)) + (matrix1.M43 * matrix2.M31)) + (matrix1.M44 * matrix2.M41);
		auto m42 = (((matrix1.M41 * matrix2.M12) + (matrix1.M42 * matrix2.M22)) + (matrix1.M43 * matrix2.M32)) + (matrix1.M44 * matrix2.M42);
		auto m43 = (((matrix1.M41 * matrix2.M13) + (matrix1.M42 * matrix2.M23)) + (matrix1.M43 * matrix2.M33)) + (matrix1.M44 * matrix2.M43);
		auto m44 = (((matrix1.M41 * matrix2.M14) + (matrix1.M42 * matrix2.M24)) + (matrix1.M43 * matrix2.M34)) + (matrix1.M44 * matrix2.M44);

		Matrix result;
		result.M11 = m11;
		result.M12 = m12;
		result.M13 = m13;
		result.M14 = m14;
		result.M21 = m21;
		result.M22 = m22;
		result.M23 = m23;
		result.M24 = m24;
		result.M31 = m31;
		result.M32 = m32;
		result.M33 = m33;
		result.M34 = m34;
		result.M41 = m41;
		result.M42 = m42;
		result.M43 = m43;
		result.M44 = m44;

		return result;
	}

	Matrix Matrix::Multiply(Matrix const& matrix1, float scaleFactor) {
		Matrix result;

		result.M11 = matrix1.M11 * scaleFactor;
		result.M12 = matrix1.M12 * scaleFactor;
		result.M13 = matrix1.M13 * scaleFactor;
		result.M14 = matrix1.M14 * scaleFactor;
		result.M21 = matrix1.M21 * scaleFactor;
		result.M22 = matrix1.M22 * scaleFactor;
		result.M23 = matrix1.M23 * scaleFactor;
		result.M24 = matrix1.M24 * scaleFactor;
		result.M31 = matrix1.M31 * scaleFactor;
		result.M32 = matrix1.M32 * scaleFactor;
		result.M33 = matrix1.M33 * scaleFactor;
		result.M34 = matrix1.M34 * scaleFactor;
		result.M41 = matrix1.M41 * scaleFactor;
		result.M42 = matrix1.M42 * scaleFactor;
		result.M43 = matrix1.M43 * scaleFactor;
		result.M44 = matrix1.M44 * scaleFactor;

		return result;
	}

	Matrix Matrix::Negate(Matrix const& matrix) {
		Matrix result;
		result.M11 = -matrix.M11;
		result.M12 = -matrix.M12;
		result.M13 = -matrix.M13;
		result.M14 = -matrix.M14;
		result.M21 = -matrix.M21;
		result.M22 = -matrix.M22;
		result.M23 = -matrix.M23;
		result.M24 = -matrix.M24;
		result.M31 = -matrix.M31;
		result.M32 = -matrix.M32;
		result.M33 = -matrix.M33;
		result.M34 = -matrix.M34;
		result.M41 = -matrix.M41;
		result.M42 = -matrix.M42;
		result.M43 = -matrix.M43;
		result.M44 = -matrix.M44;

		return result;
	}

	Matrix Matrix::Subtract(Matrix const& matrix1, Matrix const& matrix2) {
		Matrix result;

		result.M11 = matrix1.M11 - matrix2.M11;
		result.M12 = matrix1.M12 - matrix2.M12;
		result.M13 = matrix1.M13 - matrix2.M13;
		result.M14 = matrix1.M14 - matrix2.M14;
		result.M21 = matrix1.M21 - matrix2.M21;
		result.M22 = matrix1.M22 - matrix2.M22;
		result.M23 = matrix1.M23 - matrix2.M23;
		result.M24 = matrix1.M24 - matrix2.M24;
		result.M31 = matrix1.M31 - matrix2.M31;
		result.M32 = matrix1.M32 - matrix2.M32;
		result.M33 = matrix1.M33 - matrix2.M33;
		result.M34 = matrix1.M34 - matrix2.M34;
		result.M41 = matrix1.M41 - matrix2.M41;
		result.M42 = matrix1.M42 - matrix2.M42;
		result.M43 = matrix1.M43 - matrix2.M43;
		result.M44 = matrix1.M44 - matrix2.M44;

		return result;
	}

	Matrix Matrix::Transpose(Matrix const& matrix) {
		Matrix result;

		result.M11 = matrix.M11;
		result.M12 = matrix.M21;
		result.M13 = matrix.M31;
		result.M14 = matrix.M41;

		result.M21 = matrix.M12;
		result.M22 = matrix.M22;
		result.M23 = matrix.M32;
		result.M24 = matrix.M42;

		result.M31 = matrix.M13;
		result.M32 = matrix.M23;
		result.M33 = matrix.M33;
		result.M34 = matrix.M43;

		result.M41 = matrix.M14;
		result.M42 = matrix.M24;
		result.M43 = matrix.M34;
		result.M44 = matrix.M44;

		return result;
	}

	void Matrix::FindDeterminants(Matrix const& matrix, float& major,
		float& minor1, float& minor2, float& minor3, float& minor4, float& minor5, float& minor6,
		float& minor7, float& minor8, float& minor9, float& minor10, float& minor11, float& minor12) {

		//TODO: observar conversão de valores para double

		auto det1 = matrix.M11 * matrix.M22 - matrix.M12 * matrix.M21;
		auto det2 = matrix.M11 * matrix.M23 - matrix.M13 * matrix.M21;
		auto det3 = matrix.M11 * matrix.M24 - matrix.M14 * matrix.M21;
		auto det4 = matrix.M12 * matrix.M23 - matrix.M13 * matrix.M22;
		auto det5 = matrix.M12 * matrix.M24 - matrix.M14 * matrix.M22;
		auto det6 = matrix.M13 * matrix.M24 - matrix.M14 * matrix.M23;
		auto det7 = matrix.M31 * matrix.M42 - matrix.M32 * matrix.M41;
		auto det8 = matrix.M31 * matrix.M43 - matrix.M33 * matrix.M41;
		auto det9 = matrix.M31 * matrix.M44 - matrix.M34 * matrix.M41;
		auto det10 = matrix.M32 * matrix.M43 - matrix.M33 * matrix.M42;
		auto det11 = matrix.M32 * matrix.M44 - matrix.M34 * matrix.M42;
		auto det12 = matrix.M33 * matrix.M44 - matrix.M34 * matrix.M43;

		major = (det1 * det12 - det2 * det11 + det3 * det10 + det4 * det9 - det5 * det8 + det6 * det7);
		minor1 = det1;
		minor2 = det2;
		minor3 = det3;
		minor4 = det4;
		minor5 = det5;
		minor6 = det6;
		minor7 = det7;
		minor8 = det8;
		minor9 = det9;
		minor10 = det10;
		minor11 = det11;
		minor12 = det12;
	}
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
		default: return M11; //TODO: checar retorno default
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
		return Vector3(-M31, -M32, -M33);
	}

	void Matrix::Forward(Vector3 const& value) {
		M31 = -value.X;
		M32 = -value.Y;
		M33 = -value.Z;
	}

	Vector3 Matrix::Left() const {
		return Vector3(-M11, -M12, -M13);
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

	bool Matrix::Decompose(Vector3& scale, Quaternion& rotation, Vector3& translation) const {
		translation.X = M41;
		translation.Y = M42;
		translation.Z = M43;

		float xs = (MathHelper::Sign(M11 * M12 * M13 * M14) < 0) ? -1.F : 1.F;
		float ys = (MathHelper::Sign(M21 * M22 * M23 * M24) < 0) ? -1.F : 1.F;
		float zs = (MathHelper::Sign(M31 * M32 * M33 * M34) < 0) ? -1.F : 1.F;

		scale.X = xs * sqrt(M11 * M11 + M12 * M12 + M13 * M13);
		scale.Y = ys * sqrt(M21 * M21 + M22 * M22 + M23 * M23);
		scale.Z = zs * sqrt(M31 * M31 + M32 * M32 + M33 * M33);

		if (scale.X == 0.0 || scale.Y == 0.0 || scale.Z == 0.0) {
			rotation = Quaternion::Identity;
			return false;
		}

		Matrix m1 = Matrix(
			M11 / scale.X, M12 / scale.X, M13 / scale.X, 0,
			M21 / scale.Y, M22 / scale.Y, M23 / scale.Y, 0,
			M31 / scale.Z, M32 / scale.Z, M33 / scale.Z, 0,
			0, 0, 0, 1);

		rotation = Quaternion::CreateFromRotationMatrix(m1);
		return true;
	}

	float Matrix::Determinant() const {
		auto num22 = M11;
		auto num21 = M12;
		auto num20 = M13;
		auto num19 = M14;
		auto num12 = M21;
		auto num11 = M22;
		auto num10 = M23;
		auto num9 = M24;
		auto num8 = M31;
		auto num7 = M32;
		auto num6 = M33;
		auto num5 = M34;
		auto num4 = M41;
		auto num3 = M42;
		auto num2 = M43;
		auto num = M44;

		auto num18 = (num6 * num) - (num5 * num2);
		auto num17 = (num7 * num) - (num5 * num3);
		auto num16 = (num7 * num2) - (num6 * num3);
		auto num15 = (num8 * num) - (num5 * num4);
		auto num14 = (num8 * num2) - (num6 * num4);
		auto num13 = (num8 * num3) - (num7 * num4);

		auto expression1 = (((num22 * (((num11 * num18) - (num10 * num17)) + (num9 * num16))) - (num21 * (((num12 * num18) - (num10 * num15)) + (num9 * num14)))));
		auto expression2 = (num20 * (((num12 * num17) - (num11 * num15)) + (num9 * num13)));
		auto expression3 = (num19 * (((num12 * num16) - (num11 * num14)) + (num10 * num13)));

		return((expression1 + expression2) - (expression3));
	}

	bool Matrix::Equals(Matrix const& other) const {
		return M11 == other.M11
			&& M22 == other.M22
			&& M33 == other.M33
			&& M44 == other.M44
			&& M12 == other.M12
			&& M13 == other.M13
			&& M14 == other.M14
			&& M21 == other.M21
			&& M23 == other.M23
			&& M24 == other.M24
			&& M31 == other.M31
			&& M32 == other.M32
			&& M34 == other.M34
			&& M41 == other.M41
			&& M42 == other.M42
			&& M43 == other.M43;
	}
}