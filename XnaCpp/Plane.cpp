#include <cmath>
#include "Plane.hpp"
#include "Vector4.hpp"
#include "Matrix.hpp"
#include "Quaternion.hpp"
#include "BoundingBox.hpp"
#include "BoundingSphere.hpp"
#include "BoundingFrustum.hpp"

namespace Xna {
	float PlaneHelper::ClassifyPoint(Vector3 const& point, Plane const& plane) {
		return point.X * plane.Normal.X 
			+ point.Y * plane.Normal.Y 
			+ point.Z * plane.Normal.Z
			+ plane.D;
	}
	
	float PlaneHelper::PerpendicularDistance(Vector3 const& point, Plane const& plane) {
		return abs((plane.Normal.X * point.X + plane.Normal.Y * point.Y + plane.Normal.Z * point.Z)
			/ sqrt(plane.Normal.X * plane.Normal.X + plane.Normal.Y * plane.Normal.Y + plane.Normal.Z * plane.Normal.Z));
	}
}

namespace Xna {
	Plane::Plane() {}

	Plane::Plane(Vector4 const& value) :
		Normal(Vector3(value.X, value.Y, value.Z)), D(value.W) {}

	Plane::Plane(Vector3 const& normal, float d) :
		Normal(normal), D(d) {}

	Plane::Plane(Vector3 const& a, Vector3 const& b, Vector3 const& c) {
		auto ab = b - a;
		auto ac = c - a;

		auto cross = Vector3::Cross(ab, ac);
		Normal = Vector3::Normalize(cross);
		D = -(Vector3::Dot(Normal, a));
	}

	Plane::Plane(float a, float b, float c, float d) :
		Normal(Vector3(a, b, c)), D(d) {}

	Plane::Plane(Vector3 const& pointOnPlane, Vector3 const& normal) {
		Normal = normal;
		D = -(
			pointOnPlane.X * normal.X +
			pointOnPlane.Y * normal.Y +
			pointOnPlane.Z * normal.Z);
	}
}	

namespace Xna {
	bool operator ==(Plane const& plane1, Plane const& plane2) {
		return plane1.Equals(plane2);
	}

	bool operator !=(Plane const& plane1, Plane const& plane2) {
		return !plane1.Equals(plane2);
	}
}

namespace Xna {
	Plane Plane::Transform(Plane const& plane, Matrix const& matrix) {
		auto transformedMatrix = Matrix::Invert(matrix);
		transformedMatrix = Matrix::Transpose(transformedMatrix);

		auto vector = Vector4(plane.Normal, plane.D);
		auto transformedVector = Vector4::Transform(vector, transformedMatrix);

		return Plane(transformedVector);
	}

	Plane Plane::Transform(Plane const& plane, Quaternion const& rotation) {
		Plane result;
		result.Normal = Vector3::Transform(plane.Normal, rotation);
		result.D = plane.D;

		return result;
	}

	Plane Plane::Normalize(Plane const& value) {
		auto length = value.Normal.Length();
		auto factor = 1.f / length;

		Plane result;
		result.Normal = Vector3::Multiply(value.Normal, factor);
		result.D = value.D * factor;

		return result;
	}
}

namespace Xna {
	float Plane::Dot(Vector4 const& value) const {
		return ((((Normal.X * value.X) + (Normal.Y * value.Y)) + (Normal.Z * value.Z)) + (D * value.W));
	}

	float Plane::DotCoordinate(Vector3 const& value) const {
		return ((((Normal.X * value.X) + (Normal.Y * value.Y)) + (Normal.Z * value.Z)) + D);
	}

	float Plane::DotNormal(Vector3 const& value) const {
		return (((Normal.X * value.X) + (Normal.Y * value.Y)) + (Normal.Z * value.Z));
	}

	void Plane::Normalize() {
		auto value = Normalize(*this);
		Normal = value.Normal;
		D = value.D;
	}

	bool Plane::Equals(Plane const& other) const {
		return Normal == other.Normal && D == other.D;
	}

	PlaneIntersectionType Plane::Intersects(BoundingBox const& box) const {
		return box.Intersects(*this);
	}

	PlaneIntersectionType Plane::Intersects(BoundingFrustum const& frustum) const {
		return frustum.Intersects(*this);
	}

	PlaneIntersectionType Plane::Intersects(BoundingSphere const& sphere) const {
		return sphere.Intersects(*this);
	}

	PlaneIntersectionType Plane::Intersects(Vector3 const& point) const {
		auto distance = DotCoordinate(point);

		if (distance > 0)
			return PlaneIntersectionType::Front;

		if (distance < 0)
			return PlaneIntersectionType::Back;

		return PlaneIntersectionType::Intersecting;
	}

	void Plane::Deconstruct(Vector3& normal, float& d) const {
		normal = Normal;
		d = D;
	}
}