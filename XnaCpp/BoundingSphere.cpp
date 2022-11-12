#include <limits>
#include "BoundingSphere.hpp"
#include "BoundingBox.hpp"
#include "BoundingFrustum.hpp"
#include "Plane.hpp"
#include "Ray.hpp"
#include "Matrix.hpp"

using std::numeric_limits;
using std::max;
using CSharp::Nullable;
using CSharp::csnull;

namespace Xna {
	BoundingSphere::BoundingSphere() {}

	BoundingSphere::BoundingSphere(Vector3 const& center, float radius) :
		Center(center), Radius(radius) {}
}

namespace Xna {
	bool operator == (BoundingSphere const& a, BoundingSphere const& b) {
		return a.Equals(b);
	}

	bool operator != (BoundingSphere const& a, BoundingSphere const& b) {
		return !a.Equals(b);
	}
}

namespace Xna {
	BoundingSphere BoundingSphere::CreateFromBoundingBox(BoundingBox const& box) {
		auto center = Vector3(
			(box.Min.X + box.Max.X) / 2.0f,
			(box.Min.Y + box.Max.Y) / 2.0f,
			(box.Min.Z + box.Max.Z) / 2.0f);

		auto radius = Vector3::Distance(center, box.Max);

		return BoundingSphere(center, radius);
	}

	BoundingSphere BoundingSphere::CreateFromFrustum(BoundingFrustum const& frustum) {
		return CreateFromPoints(frustum.GetCorners());
	}

	BoundingSphere BoundingSphere::CreateFromPoints(std::vector<Vector3> const& points) {
		auto minx = Vector3(numeric_limits<float>::max());
		auto maxx = -minx;
		auto miny = minx;
		auto maxy = -minx;
		auto minz = minx;
		auto maxz = -minx;
		auto numPoints = 0;

		for (size_t i = 0; i < points.size(); i++) {
			++numPoints;
			auto pt = points[i];

			if (pt.X < minx.X)
				minx = pt;
			if (pt.X > maxx.X)
				maxx = pt;
			if (pt.Y < miny.Y)
				miny = pt;
			if (pt.Y > maxy.Y)
				maxy = pt;
			if (pt.Z < minz.Z)
				minz = pt;
			if (pt.Z > maxz.Z)
				maxz = pt;
		}

		if (numPoints == 0)
			return BoundingSphere(); //TODO: verificar exceção

		auto sqDistX = Vector3::DistanceSquared(maxx, minx);
		auto sqDistY = Vector3::DistanceSquared(maxy, miny);
		auto sqDistZ = Vector3::DistanceSquared(maxz, minz);

		auto min = minx;
		auto max = maxx;

		if (sqDistY > sqDistX && sqDistY > sqDistZ) {
			max = maxy;
			min = miny;
		}

		if (sqDistZ > sqDistX && sqDistZ > sqDistY) {
			max = maxz;
			min = minz;
		}

		auto center = (min + max) * 0.5f;
		auto radius = Vector3::Distance(max, center);

		auto sqRadius = radius * radius;

		for (size_t i = 0; i < points.size(); i++) {
			auto pt = points[i];
			auto diff = (pt - center);
			auto sqDist = diff.LengthSquared();

			if (sqDist > sqRadius) {
				auto distance = sqrtf(sqDist);
				auto direction = diff / distance;
				auto G = center - radius * direction;
				center = (G + pt) / 2;
				radius = Vector3::Distance(pt, center);
				sqRadius = radius * radius;
			}
		}

		return BoundingSphere(center, radius);
	}

	BoundingSphere BoundingSphere::CreateMerged(BoundingSphere const& original, BoundingSphere const& additional) {
		auto ocenterToaCenter = Vector3::Subtract(additional.Center, original.Center);
		auto distance = ocenterToaCenter.Length();

		if (distance <= original.Radius + additional.Radius) {
			if (distance <= original.Radius - additional.Radius) {
				return original;
			}
			if (distance <= additional.Radius - original.Radius) {
				return additional;
			}
		}

		auto leftRadius = max(original.Radius - distance, additional.Radius);
		auto Rightradius = max(original.Radius + distance, additional.Radius);
		ocenterToaCenter = ocenterToaCenter + (((leftRadius - Rightradius) / (2 * ocenterToaCenter.Length())) * ocenterToaCenter);

		auto result = BoundingSphere();
		result.Center = original.Center + ocenterToaCenter;
		result.Radius = (leftRadius + Rightradius) / 2;

		return result;
	}
}

namespace Xna {
	ContainmentType BoundingSphere::Contains(BoundingBox const& box) const {
		bool inside = true;
		auto corners = box.GetCorners();

		for (size_t i = 0; i < corners.size(); i++) {
			auto corner = corners[i];

			if (Contains(corner) == ContainmentType::Disjoint) {
				inside = false;
				break;
			}
		}

		if (inside)
			return ContainmentType::Contains;

		double dmin = 0;

		if (Center.X < box.Min.X)
			dmin += (Center.X - box.Min.X) * (Center.X - box.Min.X);
		else if (Center.X > box.Max.X)
			dmin += (Center.X - box.Max.X) * (Center.X - box.Max.X);

		if (Center.Y < box.Min.Y)
			dmin += (Center.Y - box.Min.Y) * (Center.Y - box.Min.Y);
		else if (Center.Y > box.Max.Y)
			dmin += (Center.Y - box.Max.Y) * (Center.Y - box.Max.Y);

		if (Center.Z < box.Min.Z)
			dmin += (Center.Z - box.Min.Z) * (Center.Z - box.Min.Z);
		else if (Center.Z > box.Max.Z)
			dmin += (Center.Z - box.Max.Z) * (Center.Z - box.Max.Z);

		if (dmin <= Radius * Radius)
			return ContainmentType::Intersects;

		return ContainmentType::Disjoint;
	}

	ContainmentType BoundingSphere::Contains(BoundingFrustum const& frustum) const {
		bool inside = true;
		auto corners = frustum.GetCorners();

		for (size_t i = 0; i < corners.size(); i++) {
			auto corner = corners[i];

			if (Contains(corner) == ContainmentType::Disjoint) {
				inside = false;
				break;
			}
		}
		if (inside)
			return ContainmentType::Contains;

		double dmin = 0;

		if (dmin <= Radius * Radius)
			return ContainmentType::Intersects;

		return ContainmentType::Disjoint;
	}

	ContainmentType BoundingSphere::Contains(BoundingSphere const& sphere) const {
		auto sqDistance = Vector3::DistanceSquared(sphere.Center, Center);

		if (sqDistance > (sphere.Radius + Radius) * (sphere.Radius + Radius))
			return ContainmentType::Disjoint;
		else if (sqDistance <= (Radius - sphere.Radius) * (Radius - sphere.Radius))
			return ContainmentType::Contains;
		else
			return ContainmentType::Intersects;
	}

	ContainmentType BoundingSphere::Contains(Vector3 const& point) const {
		auto sqRadius = Radius * Radius;
		auto sqDistance = Vector3::DistanceSquared(point, Center);

		if (sqDistance > sqRadius)
			return ContainmentType::Disjoint;
		else if (sqDistance < sqRadius)
			return ContainmentType::Contains;
		else
			return ContainmentType::Intersects;
	}

	bool BoundingSphere::Equals(BoundingSphere const& other) const {
		return Center == other.Center
			&& Radius == other.Radius;
	}

	bool BoundingSphere::Intersects(BoundingBox const& box) const {
		return box.Intersects(*this);
	}

	bool BoundingSphere::Intersects(BoundingSphere const& sphere) const {
		auto sqDistance = Vector3::DistanceSquared(sphere.Center, Center);
		return sqDistance < (sphere.Radius + Radius)* (sphere.Radius + Radius);
	}

	PlaneIntersectionType BoundingSphere::Intersects(Plane const& plane) const {
		auto distance = Vector3::Dot(plane.Normal, Center);
		distance += plane.D;

		if (distance > Radius)
			return PlaneIntersectionType::Front;
		else if (distance < -Radius)
			return PlaneIntersectionType::Back;

		return PlaneIntersectionType::Intersecting;
	}

	CSharp::Nullable<float> BoundingSphere::Intersects(Ray const& ray) const {
		return ray.Intersects(*this);
	}

	BoundingSphere BoundingSphere::Transform(Matrix const& matrix) const {
		BoundingSphere sphere;
		
		sphere.Center = Vector3::Transform(Center, matrix);
		sphere.Radius = Radius * sqrtf(max(((matrix.M11 * matrix.M11) + (matrix.M12 * matrix.M12)) + (matrix.M13 * matrix.M13), 
				max(((matrix.M21 * matrix.M21) + (matrix.M22 * matrix.M22)) + (matrix.M23 * matrix.M23), ((matrix.M31 * matrix.M31) + (matrix.M32 * matrix.M32)) + (matrix.M33 * matrix.M33))));
		
		return sphere;
	}

	void BoundingSphere::Deconstruct(Vector3& center, float& radius) const {
		center = Center;
		radius = Radius;
	}
}