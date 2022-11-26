#ifndef _GRAPHICSRESOURCE_HPP_
#define _GRAPHICSRESOURCE_HPP_

#include <string>

namespace Xna {
	namespace Graphics {
		class GraphicsResource {
		public:
			std::string Name() const;
			void Name(std::string const& value);
		};
	}
}

#endif