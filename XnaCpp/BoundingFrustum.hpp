#ifndef _BOUNDINGFRUSTUM_HPP_
#define _BOUNDINGFRUSTUM_HPP_

#include <vector>
#include <cstdint>
#include "Matrix.hpp"
#include "Vector3.hpp"
#include "ContainmentType.hpp"
#include "PlaneIntersectionType.hpp"
#include "CSharp/Nullable.hpp"

namespace Xna {

	struct Plane;
	struct BoundingBox;
	struct BoundingSphere;
	struct Ray;

	class BoudingFrustum {
	public:
		static constexpr int32_t PlaneCount = 6;
		static constexpr int32_t CornerCount = 8;

		BoundingFrustum(Matrix const& value);

		friend bool operator ==(BoundingFrustum const& a, BoundingFrustum const& b);
		friend bool operator !=(BoundingFrustum const& a, BoundingFrustum const& b);

		Matrix GetMatrix() const;
		Plane Near() const;
		Plane Far() const;
		Plane Left() const;
		Plane Right() const;
		Plane Top() const;
		Plane Bottom() const;
		ContainmentType Contains(BoundingBox const& box) const;
		ContainmentType Contains(BoundingFrustum const& box) const;
		ContainmentType Contains(BoundingSphere const& box) const;
		ContainmentType Contains(Vector3 const& box) const;
		bool Equals(BoundingFrustum const& other) const;
		std::vector<Vector3> GetCorners() const;
		std::vector<Vector3> GetCorners(Vector3 const& corrners) const;
		bool Intersects(BoundingBox const& box) const;
		bool Intersects(BoundingFrustum const& box) const;
		bool Intersects(BoundingSphere const& box) const;
		PlaneIntersectionType Intersects(Plane const& plane);
		CSharp::Nullable<float> Intersects(Ray const& ray) const;

	private:
		Matrix _matrix{ Matrix() };

		static const std::vector<Vector3> _corners = std::vector<Vector3>(CornerCount);
		static const std::vector<Plane> _planes = std::vector<Plane>(PlaneCount);

		static void IntersectionPoint(Plane const& a, Plane const& b,
			Plane const& c, Vector3 const& result);

		void CreateCorners();
		void CreatePlanes();
		void NormalizePlane(Plane& p) const;
	};
}

#endif