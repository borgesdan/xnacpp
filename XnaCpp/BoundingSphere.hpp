#ifndef _BOUNDINGSPHERE_HPP_
#define _BOUNDINGSPHERE_HPP_

#include <vector>
#include "Vector3.hpp"
#include "ContainmentType.hpp"
#include "PlaneIntersectionType.hpp"
#include "CSharp/Nullable.hpp"

namespace Xna {

	struct BoundingBox;
	class BoundingFrustum;
	struct Plane;
	struct Ray;
	struct Matrix;

	struct BoundingSphere {
		Vector3 Center{ Vector3::Zero };
		float Radius{ 0 };

		BoundingSphere();
		BoundingSphere(Vector3 const& center, float radius);

		friend bool operator == (BoundingSphere const& a, BoundingSphere const& b);
		friend bool operator != (BoundingSphere const& a, BoundingSphere const& b);

		static BoundingSphere CreateFromBoundingBox(BoundingBox const& box);
		static BoundingSphere CreateFromFrustum(BoundingFrustum const& frustum);
		static BoundingSphere CreateFromPoints(std::vector<Vector3> const& points);
		static BoundingSphere CreateMerged(BoundingSphere const& original, BoundingSphere const& additional);

		ContainmentType Contains(BoundingBox const& box) const;
		ContainmentType Contains(BoundingFrustum const& frustum) const;
		ContainmentType Contains(BoundingSphere const& sphere) const;
		ContainmentType Contains(Vector3 const& point) const;
		bool Equals(BoundingSphere const& other) const;
		bool Intersects(BoundingBox const& box) const;
		bool Intersects(BoundingSphere const& sphere) const;
		PlaneIntersectionType Intersects(Plane const& plane) const;
		CSharp::Nullable<float> Intersects(Ray const& ray) const;
		BoundingSphere Transform(Matrix const& matrix) const;
		void Deconstruct(Vector3& center, float& radius) const;
	};
}

#endif