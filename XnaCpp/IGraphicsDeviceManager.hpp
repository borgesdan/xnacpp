#ifndef _IGRAPHICSDEVICEMANAGER_HPP_
#define _IGRAPHICSDEVICEMANAGER_HPP_

namespace Xna {
	class IGraphicsDeviceManager {
		virtual bool BeginDraw() = 0;
		virtual void CreateDevice() = 0;
		virtual void EndDraw() = 0;
	};
}

#endif