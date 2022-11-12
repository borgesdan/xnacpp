#include <algorithm>
#include "BoundingBox.hpp"
#include "BoundingFrustum.hpp"
#include "BoundingSphere.hpp"
#include "Plane.hpp"
#include "Ray.hpp"

using std::max;
using std::min;

namespace Xna {
	BoundingBox::BoundingBox() {}

	BoundingBox::BoundingBox(Vector3 const& min, Vector3 const& max) :
		Min(min), Max(max) {}
}

namespace Xna {
	bool operator ==(BoundingBox const& a, BoundingBox const& b) {
		return a.Equals(b);
	}

	bool operator !=(BoundingBox const& a, BoundingBox const& b) {
		return !a.Equals(b);
	}
}

namespace Xna {
	BoundingBox BoundingBox::CreateFromPoints(std::vector<Vector3> points, int32_t index, size_t count) {
		//TODO: Verificar exceções

		if (count == -1)
			count = points.size();

		auto minVec = Vector3::MaxVector3;
		auto maxVec = Vector3::MinVector3;
		
		for (size_t i = index; i < count; i++)	{
			minVec.X = (minVec.X < points[i].X) ? minVec.X : points[i].X;
			minVec.Y = (minVec.Y < points[i].Y) ? minVec.Y : points[i].Y;
			minVec.Z = (minVec.Z < points[i].Z) ? minVec.Z : points[i].Z;

			maxVec.X = (maxVec.X > points[i].X) ? maxVec.X : points[i].X;
			maxVec.Y = (maxVec.Y > points[i].Y) ? maxVec.Y : points[i].Y;
			maxVec.Z = (maxVec.Z > points[i].Z) ? maxVec.Z : points[i].Z;
		}

		return BoundingBox(minVec, maxVec);
	}

	BoundingBox BoundingBox::CreateFromSphere(BoundingSphere const& sphere) {
		auto corner = Vector3(sphere.Radius);
		
		BoundingBox result;
		result.Min = sphere.Center - corner;
		result.Max = sphere.Center + corner;

		return result;
	}

	BoundingBox BoundingBox::CreateMerged(BoundingBox const& original, BoundingBox const& additional) {
		
		BoundingBox result;
		result.Min.X = min(original.Min.X, additional.Min.X);
		result.Min.Y = min(original.Min.Y, additional.Min.Y);
		result.Min.Z = min(original.Min.Z, additional.Min.Z);
		result.Max.X = max(original.Max.X, additional.Max.X);
		result.Max.Y = max(original.Max.Y, additional.Max.Y);
		result.Max.Z = max(original.Max.Z, additional.Max.Z);

		return result;
	}
}

namespace Xna {
	ContainmentType BoundingBox::Contains(BoundingBox const& box) const {
		if (box.Max.X < Min.X
			|| box.Min.X > Max.X
			|| box.Max.Y < Min.Y
			|| box.Min.Y > Max.Y
			|| box.Max.Z < Min.Z
			|| box.Min.Z > Max.Z)
			return ContainmentType::Disjoint;

		if (box.Min.X >= Min.X
			&& box.Max.X <= Max.X
			&& box.Min.Y >= Min.Y
			&& box.Max.Y <= Max.Y
			&& box.Min.Z >= Min.Z
			&& box.Max.Z <= Max.Z)
			return ContainmentType::Contains;

		return ContainmentType::Intersects;
	}

	ContainmentType BoundingBox::Contains(BoundingFrustum const& frustum) const {		
		size_t i;
		ContainmentType contained;
		auto corners = frustum.GetCorners();
		
		for (i = 0; i < corners.size(); i++)
		{
			contained = Contains(corners[i]);
			
			if (contained == ContainmentType::Disjoint)
				break;
		}

		if (i == corners.size())
			return ContainmentType::Contains;

		if (i != 0)
			return ContainmentType::Intersects;
		
		i++;
		for (; i < corners.size(); i++)
		{
			contained = Contains(corners[i]);
			
			if (contained != ContainmentType::Contains)
				return ContainmentType::Intersects;

		}

		return ContainmentType::Contains;
	}

	ContainmentType BoundingBox::Contains(BoundingSphere const& sphere) const {
		if (sphere.Center.X - Min.X >= sphere.Radius
			&& sphere.Center.Y - Min.Y >= sphere.Radius
			&& sphere.Center.Z - Min.Z >= sphere.Radius
			&& Max.X - sphere.Center.X >= sphere.Radius
			&& Max.Y - sphere.Center.Y >= sphere.Radius
			&& Max.Z - sphere.Center.Z >= sphere.Radius)
			return ContainmentType::Contains;

		//TODO: verificar uso de double
		float dmin = 0;
		float e = sphere.Center.X - Min.X;

		if (e < 0) {
			if (e < -sphere.Radius) {
				return ContainmentType::Disjoint;
			}

			dmin += e * e;
		}
		else {
			e = sphere.Center.X - Max.X;
			
			if (e > 0) {
				if (e > sphere.Radius) {
					return ContainmentType::Disjoint;
				}
				dmin += e * e;
			}
		}

		e = sphere.Center.Y - Min.Y;
		if (e < 0) {
			if (e < -sphere.Radius)	{
				return ContainmentType::Disjoint;
			}
			dmin += e * e;
		}
		else {
			e = sphere.Center.Y - Max.Y;
			if (e > 0) {
				if (e > sphere.Radius) {
					return ContainmentType::Disjoint;
				}
				dmin += e * e;
			}
		}

		e = sphere.Center.Z - Min.Z;
		if (e < 0) {
			if (e < -sphere.Radius) {
				return ContainmentType::Disjoint;
			}
			dmin += e * e;
		}
		else {
			e = sphere.Center.Z - Max.Z;
			if (e > 0) {
				if (e > sphere.Radius) {
					return ContainmentType::Disjoint;
				}
				dmin += e * e;
			}
		}

		if (dmin <= sphere.Radius * sphere.Radius)
			return ContainmentType::Intersects;

		return ContainmentType::Disjoint;
	}

	ContainmentType BoundingBox::Contains(Vector3 const& point) const {
		if (point.X < Min.X
			|| point.X > Max.X
			|| point.Y < Min.Y
			|| point.Y > Max.Y
			|| point.Z < Min.Z
			|| point.Z > Max.Z)
		{
			return ContainmentType::Disjoint;
		}

		return ContainmentType::Contains;
	}
}

namespace Xna {
	bool BoundingBox::Equals(BoundingBox const& other) const {
		return Min == other.Min && Max == other.Max;
	}

	std::vector<Vector3> BoundingBox::GetCorners() const {
		return std::vector<Vector3>{
				Vector3(Min.X, Max.Y, Max.Z),
				Vector3(Max.X, Max.Y, Max.Z),
				Vector3(Max.X, Min.Y, Max.Z),
				Vector3(Min.X, Min.Y, Max.Z),
				Vector3(Min.X, Max.Y, Min.Z),
				Vector3(Max.X, Max.Y, Min.Z),
				Vector3(Max.X, Min.Y, Min.Z),
				Vector3(Min.X, Min.Y, Min.Z)
		};
	}

	void BoundingBox::GetCorners(std::vector<Vector3>& corners) const {
		//TODO: verificar exceções

		corners[0].X = Min.X;
		corners[0].Y = Max.Y;
		corners[0].Z = Max.Z;
		corners[1].X = Max.X;
		corners[1].Y = Max.Y;
		corners[1].Z = Max.Z;
		corners[2].X = Max.X;
		corners[2].Y = Min.Y;
		corners[2].Z = Max.Z;
		corners[3].X = Min.X;
		corners[3].Y = Min.Y;
		corners[3].Z = Max.Z;
		corners[4].X = Min.X;
		corners[4].Y = Max.Y;
		corners[4].Z = Min.Z;
		corners[5].X = Max.X;
		corners[5].Y = Max.Y;
		corners[5].Z = Min.Z;
		corners[6].X = Max.X;
		corners[6].Y = Min.Y;
		corners[6].Z = Min.Z;
		corners[7].X = Min.X;
		corners[7].Y = Min.Y;
		corners[7].Z = Min.Z;
	}

	bool BoundingBox::Intersects(BoundingBox const& box) const {
		
		if ((Max.X >= box.Min.X) && (Min.X <= box.Max.X))	{
			if ((Max.Y < box.Min.Y) || (Min.Y > box.Max.Y)) {
				return false;
			}

			return (Max.Z >= box.Min.Z) && (Min.Z <= box.Max.Z);
		}

		return false;
	}

	bool BoundingBox::Intersects(BoundingFrustum const& frustum) const {
		return frustum.Intersects(*this);
	}
	
	bool BoundingBox::Intersects(BoundingSphere const& sphere) const {
		auto squareDistance = 0.0f;
		auto point = sphere.Center;

		if (point.X < Min.X) 
			squareDistance += (Min.X - point.X) * (Min.X - point.X);
		if (point.X > Max.X)
			squareDistance += (point.X - Max.X) * (point.X - Max.X);
		if (point.Y < Min.Y)
			squareDistance += (Min.Y - point.Y) * (Min.Y - point.Y);
		if (point.Y > Max.Y)
			squareDistance += (point.Y - Max.Y) * (point.Y - Max.Y);
		if (point.Z < Min.Z)
			squareDistance += (Min.Z - point.Z) * (Min.Z - point.Z);
		if (point.Z > Max.Z)
			squareDistance += (point.Z - Max.Z) * (point.Z - Max.Z);
		
		return squareDistance <= sphere.Radius * sphere.Radius;
	}

	PlaneIntersectionType BoundingBox::Intersects(Plane const& plane) const {
		Vector3 positiveVertex;
		Vector3 negativeVertex;

		if (plane.Normal.X >= 0) {
			positiveVertex.X = Max.X;
			negativeVertex.X = Min.X;
		}
		else {
			positiveVertex.X = Min.X;
			negativeVertex.X = Max.X;
		}

		if (plane.Normal.Y >= 0) {
			positiveVertex.Y = Max.Y;
			negativeVertex.Y = Min.Y;
		}
		else {
			positiveVertex.Y = Min.Y;
			negativeVertex.Y = Max.Y;
		}

		if (plane.Normal.Z >= 0) {
			positiveVertex.Z = Max.Z;
			negativeVertex.Z = Min.Z;
		}
		else {
			positiveVertex.Z = Min.Z;
			negativeVertex.Z = Max.Z;
		}
		
		auto distance = Vector3::Dot(plane.Normal, negativeVertex) + plane.D;
				
		if (distance > 0) {
			return PlaneIntersectionType::Front;			
		}
		
		distance = Vector3::Dot(plane.Normal, positiveVertex) + plane.D;
		
		if (distance < 0) {
			return PlaneIntersectionType::Back;			
		}

		return PlaneIntersectionType::Intersecting;
	}

	CSharp::Nullable<float> BoundingBox::Intersects(Ray const& ray) const {
		return ray.Intersects(*this);
	}

	void BoundingBox::Deconstruct(Vector3& min, Vector3& max) const {
		min = Min;
		max = Max;
	}
}