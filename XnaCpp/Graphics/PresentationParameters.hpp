#ifndef _PRESENTATIONPARAMETERS_HPP_
#define _PRESENTATIONPARAMETERS_HPP_

#include <cstdint>
#include "SurfaceFormat.hpp"
#include "States/DepthFormat.hpp"

namespace Xna {
	namespace Graphics {
		class PresentationParameters {
		private:
			DepthFormat depthStencilFormat;
			SurfaceFormat backBufferFormat;

		public:
			static const int32_t DefaultPresentRate{ 60 };
		};
	}
}

#endif