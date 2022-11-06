#ifndef _PLANEINTERSECTIONTYPE_HPP_
#define _PLANEINTERSECTIONTYPE_HPP_

namespace Xna {
    enum class PlaneIntersectionType
    {

        // There is no intersection, the bounding volume is in the negative half space of the plane.
        Front,

        // There is no intersection, the bounding volume is in the positive half space of the plane.
        Back,

        // The plane is intersected.
        Intersecting
    };
}

#endif