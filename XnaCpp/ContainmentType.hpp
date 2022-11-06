#ifndef _CONTAINMENTTYPE_HPP_
#define _CONTAINMENTTYPE_HPP_

namespace Xna {
	enum class ContainmentType {
		// Indicates that there is no overlap between two bounding volumes.
		Disjoint,
		// Indicates that one bounding volume completely contains another volume.
		Contains,
		// Indicates that bounding volumes partially overlap one another.
		Intersects
	};
}

#endif