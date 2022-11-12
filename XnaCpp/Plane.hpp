#ifndef _PLANE_HPP_
#define _PLANE_HPP_

#include "Vector3.hpp"
#include "PlaneIntersectionType.hpp"

namespace Xna {

	struct Vector4;
	struct Matrix;
	struct Quaternion;
	struct BoundingBox;
	struct BoundingSphere;
	class BoundingFrustum;

	struct Plane {
		float D{ 0 };
		Vector3 Normal{ Vector3::Zero };

		Plane();
		Plane(Vector4 const& value);
		Plane(Vector3 const& normal, float d);
		Plane(Vector3 const& a, Vector3 const& b, Vector3 const& c);
		Plane(float a, float b, float c, float d);
		Plane(Vector3 const& pointOnPlane, Vector3 const& normal);

		friend bool operator ==(Plane const& plane1, Plane const& plane2);
		friend bool operator !=(Plane const& plane1, Plane const& plane2);

		static Plane Transform(Plane const& plane, Matrix const& matrix);
		static Plane Transform(Plane const& plane, Quaternion const& rotation);
		static Plane Normalize(Plane const& value);

		float Dot(Vector4 const& value) const;
		float DotCoordinate(Vector3 const& value) const;
		float DotNormal(Vector3 const& value) const;
		void Normalize();
		bool Equals(Plane const& other) const;
		PlaneIntersectionType Intersects(BoundingBox const& box) const;
		PlaneIntersectionType Intersects(BoundingFrustum const& frustum) const;
		PlaneIntersectionType Intersects(BoundingSphere const& sphere) const;
		PlaneIntersectionType Intersects(Vector3 const& point) const;
		void Deconstruct(Vector3& normal, float& d) const;
	};

	class PlaneHelper {
	public:
		static float ClassifyPoint(Vector3 const& point, Plane const& plane);
		static float PerpendicularDistance(Vector3 const& point, Plane const& plane);
	};
}

#endif