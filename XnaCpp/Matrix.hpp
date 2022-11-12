#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <memory>
#include "CSharp/Nullable.hpp"

namespace Xna {

	struct Quaternion;
	struct Rectangle;
	struct Vector4;
	struct Vector3;

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

		static Matrix Identity;

		Matrix();
		Matrix(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31,
			float m32, float m33, float m34, float m41, float m42, float m43, float m44);
		Matrix(Vector4 row1, Vector4 row2, Vector4 row3, Vector4 row4);

		Matrix operator -();
		friend Matrix operator +(Matrix const& matrix1, Matrix const& matrix2);
		friend Matrix operator /(Matrix const& matrix1, Matrix const& matrix2);
		friend Matrix operator /(Matrix const& matrix, float divider);
		friend bool operator ==(Matrix const& matrix1, Matrix const& matrix2);
		friend  bool operator !=(Matrix const& matrix1, Matrix const& matrix2);
		friend Matrix operator *(Matrix const& matrix1, Matrix const& matrix2);
		friend Matrix operator *(Matrix const& matrix, float scaleFactor);
		friend Matrix operator -(Matrix const& matrix1, Matrix const& matrix2);						

		static Matrix Add(Matrix const& matrix1, Matrix const& matrix2);				
		static Matrix CreateBillboard(Vector3 const& objectPosition, Vector3 const& cameraPosition,
			Vector3 const& cameraUpVector, CSharp::Nullable<Vector3> const& cameraForwardVector);
		static Matrix CreateConstrainedBillboard(Vector3 const& objectPosition, Vector3 const& cameraPosition,
			Vector3 const& rotateAxis, CSharp::Nullable<Vector3> const& cameraForwardVector, CSharp::Nullable<Vector3> const& objectForwardVector);
		static Matrix CreateFromAxisAngle(Vector3 const& axis, float angle);
		static Matrix CreateFromQuaternion(Quaternion const& quaternion);
		static Matrix CreateFromYawPitchRoll(float yaw, float pitch, float roll);
		static Matrix CreateLookAt(Vector3 const& cameraPosition, Vector3 const& cameraTarget, Vector3 const& cameraUpVector);
		static Matrix CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane);
		static Matrix CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane);
		static Matrix CreatePerspective(float width, float height, float nearPlaneDistance, float farPlaneDistance);
		static Matrix CreatePerspectiveFieldOfView(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance);
		static Matrix CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlaneDistance, float farPlaneDistance);
		static Matrix CreatePerspectiveOffCenter(Rectangle const& viewingVolume, float nearPlaneDistance, float farPlaneDistance);
		static Matrix CreateRotationX(float radians);
		static Matrix CreateRotationY(float radians);
		static Matrix CreateRotationZ(float radians);
		static Matrix CreateScale(float scale);
		static Matrix CreateScale(float xScale, float yScale, float zScale);
		static Matrix CreateScale(Vector3 const& scales);
		//TODO: Implementar após a implementação de Plane - static Matrix CreateShadow(Vector3 lightDirection, Plane plane);
		//TODO: Implementar após a implementação de Plane - static Matrix CreateReflection(Plane value)
		static Matrix CreateTranslation(float xPosition, float yPosition, float zPosition);
		static Matrix CreateTranslation(Vector3 const& position);
		static Matrix CreateWorld(Vector3 const& position, Vector3 const& forward, Vector3 const& up);
		static Matrix Divide(Matrix const& matrix1, Matrix const& matrix2);
		static Matrix Divide(Matrix const& matrix1, float divider);
		static Matrix Invert(Matrix const& matrix);
		static Matrix Lerp(Matrix const& matrix1, Matrix const& matrix2, float amount);
		static Matrix Multiply(Matrix const& matrix1, Matrix const& matrix2);
		static Matrix Multiply(Matrix const& matrix1, float scaleFactor);
		//TODO: Implementar retorno de array - static float[] ToFloatArray(Matrix const& matrix);
		static Matrix Negate(Matrix const& matrix);
		static Matrix Subtract(Matrix const& matrix1, Matrix const& matrix2);
		static Matrix Transpose(Matrix const& matrix);
		static void FindDeterminants(Matrix const& matrix, float& major,
			float& minor1, float& minor2, float& minor3, float& minor4, float& minor5, float& minor6,
			float& minor7, float& minor8, float& minor9, float& minor10, float& minor11, float& minor12);

		float This(int32_t index) const;
		void This(int32_t index, float value);
		float This(int32_t row, int32_t column) const;
		void This(int32_t row, int32_t column, float value);
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
		bool Decompose(Vector3& scale, Quaternion& rotation, Vector3& translation) const;
		float Determinant() const;
		bool Equals(Matrix const& other) const;
	};
}

#endif