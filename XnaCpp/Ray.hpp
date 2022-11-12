#ifndef _RAY_HPP_
#define _RAY_HPP_

#include "Vector3.hpp"
#include "CSharp/Nullable.hpp"

namespace Xna {

	struct BoundingBox;
	struct BoundingSphere;
	struct Plane;

	struct Ray {
		Vector3 Direction{ Vector3::Zero };
		Vector3 Position{ Vector3::Zero };

		friend bool operator !=(Ray const& a, Ray const& b);
		friend bool operator ==(Ray const& a, Ray const& b);

		Ray();
		Ray(Vector3 const& position, Vector3 const& direction);

		bool Equals(Ray const& other) const;
		CSharp::Nullable<float> Intersects(BoundingBox const& box) const;
		CSharp::Nullable<float> Intersects(BoundingSphere const& sphere) const;
		CSharp::Nullable<float> Intersects(Plane const& plane) const;

		void Deconstruct(Vector3& position, Vector3& direction) const;
	};
}

#endif