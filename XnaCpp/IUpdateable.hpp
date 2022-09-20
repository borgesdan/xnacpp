#ifndef _IUPDATEABLE_HPP_
#define _IUPDATEABLE_HPP_

#include <stdint.h>
#include "GameTime.hpp"

namespace Xna {
	class IUpdateable {
	public:		
		virtual void Update(GameTime gameTime) = 0;

		bool Enabled() const = 0;
		int32_t UpdateOrder() const = 0;
	};
}

#endif
