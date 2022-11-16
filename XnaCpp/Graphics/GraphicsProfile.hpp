#ifndef _GRAPHICSPROFILE_HPP_
#define _GRAPHICSPROFILE_HPP_

namespace Xna {
	namespace Graphics {
        enum class GraphicsProfile
        {
            
            // Use a limited set of graphic features and capabilities, allowing the game to support the widest variety of devices.
            Reach,
            
            // Use the largest available set of graphic features and capabilities to target devices, that have more enhanced graphic capabilities.
            HiDef
        };
	}
}

#endif