#include<cmath>
#include "Ray.hpp"
#include "BoundingBox.hpp";
#include "BoundingSphere.hpp";
#include "Plane.hpp";

using CSharp::Nullable;
using CSharp::csnull;

namespace Xna {
	Ray::Ray() {}
	Ray::Ray(Vector3 const& position, Vector3 const& direction) :
		Position(position), Direction(direction) {}
}

namespace Xna {
	bool operator !=(Ray const& a, Ray const& b) {
		return !a.Equals(b);
	}

	bool operator ==(Ray const& a, Ray const& b) {
		return a.Equals(b);
	}
}

namespace Xna {
	bool Ray::Equals(Ray const& other) const {
		return Position.Equals(other.Position)
			&& Direction.Equals(other.Direction);
	}

	Nullable<float> Ray::Intersects(BoundingBox const& box) const {
        const float Epsilon = 1e-6f;

        Nullable<float> tMin = csnull;
        Nullable<float> tMax = csnull;

        if (abs(Direction.X) < Epsilon) {
            if (Position.X < box.Min.X || Position.X > box.Max.X)
                return csnull;
        }
        else {
            tMin = (box.Min.X - Position.X) / Direction.X;
            tMax = (box.Max.X - Position.X) / Direction.X;

            if (tMin.Value() > tMax.Value()) {
                auto temp = tMin;
                tMin = tMax;
                tMax = temp;
            }
        }

        if (abs(Direction.Y) < Epsilon) {
            if (Position.Y < box.Min.Y || Position.Y > box.Max.Y)
                return csnull;
        }
        else {
            auto tMinY = (box.Min.Y - Position.Y) / Direction.Y;
            auto tMaxY = (box.Max.Y - Position.Y) / Direction.Y;

            if (tMinY > tMaxY)  {
                auto temp = tMinY;
                tMinY = tMaxY;
                tMaxY = temp;
            }

            if ((tMin.HasValue() && tMin.Value() > tMaxY)
                || (tMax.HasValue() && tMinY > tMax.Value()))
                return csnull;

            if (!tMin.HasValue() || tMinY > tMin.Value())
                tMin = tMinY;
            if (!tMax.HasValue() || tMaxY < tMax.Value())
                tMax = tMaxY;
        }

        if (abs(Direction.Z) < Epsilon)
        {
            if (Position.Z < box.Min.Z || Position.Z > box.Max.Z)
                return csnull;
        }
        else
        {
            auto tMinZ = (box.Min.Z - Position.Z) / Direction.Z;
            auto tMaxZ = (box.Max.Z - Position.Z) / Direction.Z;

            if (tMinZ > tMaxZ)
            {
                auto temp = tMinZ;
                tMinZ = tMaxZ;
                tMaxZ = temp;
            }

            if ((tMin.HasValue() && tMin.Value() > tMaxZ)
                || (tMax.HasValue() && tMinZ > tMax.Value()))
                return csnull;

            if (!tMin.HasValue() || tMinZ > tMin.Value())
                tMin = tMinZ;
            if (!tMax.HasValue() || tMaxZ < tMax.Value())
                tMax = tMaxZ;
        }
        
        if ((tMin.HasValue() && tMin.Value() < 0) && tMax.Value() > 0)
            return 0;
        
        if (tMin.Value() < 0)
            return csnull;

        return tMin;
	}

    Nullable<float> Ray::Intersects(BoundingSphere const& sphere) const {        
        auto difference = sphere.Center - Position;
        auto differenceLengthSquared = difference.LengthSquared();
        auto sphereRadiusSquared = sphere.Radius * sphere.Radius;
        
        if (differenceLengthSquared < sphereRadiusSquared)  {
            return 0.0f;
        }

        auto distanceAlongRay = Vector3::Dot(Direction, difference);
        
        if (distanceAlongRay < 0.F) {
            return csnull;
        }
        
        auto dist = sphereRadiusSquared + distanceAlongRay * distanceAlongRay - differenceLengthSquared;

        return (dist < 0) ? csnull : Nullable<float>(distanceAlongRay - sqrt(dist));
    }

    Nullable<float> Ray::Intersects(Plane const& plane) const {
        auto den = Vector3::Dot(Direction, plane.Normal);

        if (abs(den) < 0.00001f) {
            return csnull;
        }        

        float result = (-plane.D - Vector3::Dot(plane.Normal, Position)) / den;

        if (result < 0.0f) {
            if (result < -0.00001f) {
                return csnull;
            }

            result = 0.0f;
        }

        return result;
    }

    void Ray::Deconstruct(Vector3& position, Vector3& direction) const {
        position = Position;
        direction = Direction;
    }
}