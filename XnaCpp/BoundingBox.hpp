#ifndef _BOUNDINGBOX_HPP_
#define _BOUNDINGBOX_HPP_

#include <cstdint>
#include <vector>
#include "Vector3.hpp"
#include "ContainmentType.hpp"
#include "PlaneIntersectionType.hpp"
#include "CSharp/Nullable.hpp"

namespace Xna {

	class BoundingFrustum;
	struct BoundingSphere;
	struct Plane;
	struct Ray;

	struct BoundingBox {
		Vector3 Min{ Vector3::Zero };
		Vector3 Max{ Vector3::Zero };

		static constexpr int32_t CornerCount = 8;

		BoundingBox();
		BoundingBox(Vector3 const& min, Vector3 const& max);
		
		friend bool operator ==(BoundingBox const& a, BoundingBox const& b);
		friend bool operator !=(BoundingBox const& a, BoundingBox const& b);

		static BoundingBox CreateFromPoints(std::vector<Vector3> points,
			int32_t index = 0, int32_t count = -1);
		static BoundingBox CreateFromSphere(BoundingSphere const& sphere);
		static BoundingBox CreateMerged(BoundingBox const& original, BoundingBox const& additional);

		ContainmentType Contains(BoundingBox const& box) const;
		ContainmentType Contains(BoundingFrustum const& frustum) const;
		ContainmentType Contains(BoundingSphere const& sphere) const;
		ContainmentType Contains(Vector3 const& point) const;

		bool Equals(BoundingBox const& other) const;
		std::vector<Vector3> GetCorners() const;
		void GetCorners(std::vector<Vector3>& corners) const;
		bool Intersects(BoundingBox const& box) const;
		bool Intersects(BoundingFrustum const& frustum) const;
		bool Intersects(BoundingSphere const& sphere) const;
		PlaneIntersectionType Intersects(Plane const& plane) const;
		CSharp::Nullable<float> Intersects(Ray const& ray) const;
		void Deconstruct(Vector3& min, Vector3& max) const;
	};
}

#endif