#ifndef _GRAPHICSDEVICEINFORMATION_HPP_
#define _GRAPHICSDEVICEINFORMATION_HPP_

#include "Graphics/GraphicsAdapter.hpp"
#include "Graphics/GraphicsProfile.hpp"
#include "Graphics/PresentationParameters.hpp"

namespace Xna {
	class GraphicsDeviceInformation {
	public:
		Graphics::GraphicsAdapter Adapter();
		void Adapter(Graphics::GraphicsAdapter const& value);

		Graphics::GraphicsProfile GraphicsProfile();
		void GraphicsProfile(Graphics::GraphicsProfile const& value);

		Graphics::PresentationParameters PresentationParameters();
		void PresentationParameters(Graphics::PresentationParameters value);
	};
}

#endif