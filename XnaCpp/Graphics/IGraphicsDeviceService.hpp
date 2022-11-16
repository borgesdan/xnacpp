#ifndef _IGRAPHICSDEVICESERVICE_HPP_
#define _IGRAPHICSDEVICESERVICE_HPP_

#include "GraphicsDevice.hpp"

namespace Xna {
	namespace Graphics {
		class IGraphicsDeviceService {
			virtual GraphicsDevice GetGraphicsDevice() const = 0;
			//TODO: criar eventos
			//event EventHandler<EventArgs> DeviceCreated;
			//event EventHandler<EventArgs> DeviceDisposing;
			//event EventHandler<EventArgs> DeviceReset;
			//event EventHandler<EventArgs> DeviceResetting;
		};
	}	
}

#endif