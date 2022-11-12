#ifndef _BOUNDINGFRUSTUM_HPP_
#define _BOUNDINGFRUSTUM_HPP_

#include <vector>
#include <cstdint>
#include "Matrix.hpp"
#include "Vector3.hpp"
#include "ContainmentType.hpp"
#include "PlaneIntersectionType.hpp"
#include "CSharp/Nullable.hpp"
#include "Plane.hpp"

namespace Xna {

	struct BoundingBox;
	struct BoundingSphere;
	struct Ray;

	class BoundingFrustum {
	public:
		static constexpr int32_t PlaneCount = 6;
		static constexpr int32_t CornerCount = 8;

		BoundingFrustum(Matrix const& value);

		friend bool operator ==(BoundingFrustum const& a, BoundingFrustum const& b);
		friend bool operator !=(BoundingFrustum const& a, BoundingFrustum const& b);

		Matrix GetMatrix() const;
		void SetMatrix(Matrix value);
		Plane Near() const;
		Plane Far() const;
		Plane Left() const;
		Plane Right() const;
		Plane Top() const;
		Plane Bottom() const;
		ContainmentType Contains(BoundingBox const& box) const;
		ContainmentType Contains(BoundingFrustum const& frustum) const;
		ContainmentType Contains(BoundingSphere const& sphere) const;
		ContainmentType Contains(Vector3 const& point) const;
		bool Equals(BoundingFrustum const& other) const;
		std::vector<Vector3> GetCorners() const;
		void GetCorners(std::vector<Vector3>& corners) const;
		bool Intersects(BoundingBox const& box) const;
		bool Intersects(BoundingFrustum const& frustum) const;
		bool Intersects(BoundingSphere const& sphere) const;	
		PlaneIntersectionType Intersects(Plane const& plane) const;
		CSharp::Nullable<float> Intersects(Ray const& ray) const;

	private:
		Matrix _matrix{ Matrix() };

		std::vector<Vector3> _corners = std::vector<Vector3>(CornerCount);
		std::vector<Plane> _planes = std::vector<Plane>(PlaneCount);

		static Vector3 IntersectionPoint(Plane const& a, Plane const& b, Plane const& c);

		void CreateCorners();
		void CreatePlanes();
		void NormalizePlane(Plane& p) const;
	};
}

#endif